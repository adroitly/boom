//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_DEFINEPLACEHOLDER__
#define __FLA_DEFINEPLACEHOLDER__

#include "./fla_Definition.h"
#include "../base/fla_Base.h"

namespace fla
{
    class DefinitionPlaceholder : public DefinitionHelper<DefinitionPlaceholder>
    {
    public:
        template <typename T>
        static Ptr createWithOriginal(const typename T::Ptr& ptr);
        void setBounds(const Rect& bounds);
        virtual Rect getBounds() const  {   return _bounds; }

    private:
        Rect _bounds;
    };

    template <typename T>
    DefinitionPlaceholder::Ptr DefinitionPlaceholder::createWithOriginal(const typename T::Ptr& ptr)
    {
        Ptr result = make_ptr<DefinitionPlaceholder>();
        result->setBounds(ptr->getBounds());
        result->setId(ptr->getId());
        result->setName(ptr->getName());
        return result;
    }

    inline void DefinitionPlaceholder::setBounds(const Rect& bounds)
    {
        _bounds = bounds;
    }
}

#endif