//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_DEFINITION_H__
#define __FLA_DEFINITION_H__

#include <string>
#include "clover/light_string.h"
#include "libra/libra_bits.h"
#include "fla_DefinitionType.h"
#include "fla_FlaDataInfo.h"
#include "../base/fla_Ref.h"

namespace fla
{
    /*
     每个定义，都会有一个Id, 这个Id是唯一的, 程序可以由Id找到定义
     */
    class Definition : public fla::Ref<Definition>
    {
    public:
        virtual ~Definition()
        {
        }

        Definition(DefinitionType type) : _Id(0), _flags(0), _type(type)
        {
        }

        bool isRoleState() const
        {
            return libra::bit_test(_flags, Bit_isRoleState);
        }

        void setIsRoleState(bool flag)
        {
            libra::bit_set(&_flags, Bit_isRoleState, flag);
        }

        // fixHscreen 这个标记，用来优化固定背景的绘画
        bool isFixHscreen() const
        {
            return libra::bit_test(_flags, Bit_FixHscreen);
        }

        void setFixHscreen(bool flag)
        {
            libra::bit_set(&_flags, Bit_FixHscreen, flag);
        }

        // ID
        void setId(uint16_t Id)
        {
            _Id = Id;
        }

        uint16_t getId() const
        {
            return _Id;
        }

        // 名称
        void setName(const char* name)
        {
            _name.reset(name);
        }

        void setName(const std::string& name)
        {
            setName(name.c_str());
        }

        const char* getName() const
        {
            return _name.c_str();
        }

        void setDataInfo(const FlaDataInfo::Ptr& info)
        {
            _dataInfo = info;
        }

        const FlaDataInfo::Ptr& getDataInfo() const
        {
            return _dataInfo;
        }

        DefinitionType getType() const
        {
            return _type;
        }

        virtual void accept(DefinitionVisitor& visitor) const = 0;
        virtual void onFinishParse() = 0;
        virtual Rect getBounds() const = 0;

    private:
        enum
        {
            Bit_isRoleState = 0x01,
            Bit_FixHscreen = 0x02,
        };

        uint16_t _Id;
        uint8_t _flags;
        DefinitionType _type;

        clover::light_string _name;
        FlaDataInfo::Ptr _dataInfo;
    };

    template <typename T, typename U>
    inline boost::intrusive_ptr<T> ptr_case(const boost::intrusive_ptr<U>& ptr)
    {
        return boost::static_pointer_cast<T>(ptr);
    }

    template <typename T>
    inline boost::intrusive_ptr<T> make_ptr()
    {
        return boost::intrusive_ptr<T>(new T(), false);
    }

    ////////////////////////////////////////////////////////
    template <typename DerivedT>
    class DefinitionHelper : public Definition
    {
    public:
        DefinitionHelper() : Definition((DefinitionType)DefinitionTraits<DerivedT>::type)
        {
        }

        DefinitionHelper(DefinitionType type) : Definition(type)
        {
        }

        typedef boost::intrusive_ptr<DerivedT> Ptr;
        static Ptr create()
        {
            return Ptr(new DerivedT(), false);
        }

        virtual void accept(DefinitionVisitor& visitor) const override
        {
            visitor.visit(static_cast<const DerivedT&>(*this));
        }

        virtual void onFinishParse() override
        {
        }
    };
}

#endif
