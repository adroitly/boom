//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_SPRITEOBJECT_H__
#define __FLA_SPRITEOBJECT_H__

#include <cstdint>
#include "../base/fla_ColorTransform.h"
#include "../utility/fla_PtrHolder.h"
#include "libra/libra_bits.h"

namespace fla
{
    enum class BlendMode : uint8_t
    {
        Normal    = 0,
        Normal2   = 1,
        Layer     = 2,
        Multiply  = 3,
        Screen    = 4,
        Lighten   = 5,
        Darken    = 6,
        Diffter   = 7,
        Add       = 8,
        Subtract  = 9,
        Invert    = 10,
        Alpha     = 11,
        Erase     = 12,
        Overlay   = 13,
        Hardlight = 14,
    };
    
    class PlaceObject final
    {
    public:
        PlaceObject();
        
        bool isRemoveObject() const         {   return libra::bit_test(_flags, Bit_RemoveObject);   }
        void setRemoveObject(bool flag)     {   libra::bit_set(&_flags, Bit_RemoveObject, flag);   }
        
        // 变换矩阵
        bool hasTrans() const               {   return _trans.hasValue();       }
        const Matrix& trans() const         {   return _trans.value();          }
        void setTrans(const Matrix& trans)  {   _trans.setValue(trans);         }
        
        // 颜色矩阵
        bool hasColorTrans() const                      {   return _colorTrans.hasValue();  }
        const ColorTransform& colorTrans() const        {   return _colorTrans.value();     }
        void setColorTrans(const ColorTransform& trans) {  _colorTrans.setValue(trans);     }
        
        // 深度
        uint16_t depth() const              {   return _depth;          }
        void setDepth(uint16_t depth)       {   _depth = depth;         }
        
        // 角色Id
        bool hasCharacterID() const         {   return libra::bit_test(_flags, Bit_HasCharacterID); }
        uint16_t characterID() const        {   return _characterID;    }
        void setCharacterID(uint16_t Id);
        
        // blend mode
        bool hasBlendMode() const           {   return libra::bit_test(_flags, Bit_hasBlendMode);   }
        BlendMode blendMode() const         {   return _blendMode;      }
        void setBlendMode(BlendMode mode)   {   _blendMode = mode; libra::bit_set(&_flags, Bit_hasBlendMode);    }
        
        bool hasRatio() const               {   return libra::bit_test(_flags, Bit_HasRatio);                     }
        uint16_t ratio() const              {   return _ratio;                        }
        void setRatio(uint16_t ratio)       {   _ratio = ratio;  libra::bit_set(&_flags, Bit_HasRatio);    }
                
        // 深度裁剪, 暂不支持
        bool hasClipDepth() const           {   return false;   }
        uint16_t clipDepth() const          {   return 0;       }
        void setClipDepth(uint16_t depth)   {   (void)depth;    }
        
    private:
        PtrHolder<Matrix>           _trans;
        PtrHolder<ColorTransform>   _colorTrans;
        uint16_t                    _depth;
        uint16_t                    _characterID;
        uint16_t                    _ratio;
        BlendMode                   _blendMode;
        
        enum
        {
            Bit_RemoveObject   = (1 << 0),
            Bit_HasCharacterID = (1 << 1),
            Bit_HasRatio       = (1 << 2),
            Bit_hasBlendMode   = (1 << 3),
        };
        uint8_t                     _flags;
    };
}

#endif
