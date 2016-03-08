//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_DEFINEUTILS_H__
#define __FLA_DEFINEUTILS_H__

#include <vector>
#include <set>
#include "fla_Definition.h"
#include "../base/fla_ColorTransform.h"
#include "../base/fla_Error.h"
#include "../base/fla_utils.h"
#include "../graphics/fla_RenderOfDefinition.h"

namespace fla
{
    bool Definition_isAnimation(const Definition::Ptr& def);
    inline bool Definition_isSamePackage(const Definition::Ptr& def0, const Definition::Ptr& def1)
    {
        return def0->getDataInfo() == def1->getDataInfo();
    }

    template <typename Graphics>
    void Definition_drawInGraphics(const Definition& defintion, Graphics& graphics)
    {
        Definition_drawInGraphics(defintion, graphics, ColorTransform::identity());
    }

    inline std::string keyOfCache(const Definition* definition, float scale)
    {
        return keyOfCache(definition->getDataInfo()->getMd5String(), definition->getId(), 0, scale, 0);
    }

    template <typename Graphics>
    void Definition_drawInGraphics(const Definition& defintion, Graphics& graphics, const ColorTransform& colorTrans)
    {
        RenderOfDefinition<Graphics> renderVisitor(graphics, colorTrans);
        defintion.accept(renderVisitor);
    }

    void extractAllShapes(std::set<Definition::Ptr>& shapes, const Definition::Ptr& root);

    struct NullType
    {
    };
    struct LoadDataInfo
    {
        bool ignorePlaceHolde;
        bool (*checkAuthorizedFunc)();
    };

    Definition::Ptr Definition_loadData(const void* data, size_t dataLen, LoadDataInfo info, NullType, ErrorCode* code);
    Definition::Ptr Definition_loadData(const void* data, size_t dataLen, LoadDataInfo info, int Id, ErrorCode* code);
    Definition::Ptr Definition_loadData(const void* data,
                                        size_t dataLen,
                                        LoadDataInfo info,
                                        const std::string& name,
                                        ErrorCode* error);

    Definition::Ptr Definition_findState(const Definition* root, const std::string& name);
    Definition::Ptr Definition_stateAt(const Definition* root, int index);
    Color4 Definition_getSceneColor(const Definition* root);
    std::vector<std::string> Definition_getStateNames(const Definition* root);
    void Definition_changeDefaultState(Definition* root, const std::string& name);
    void Definition_walkChildren(const Definition::Ptr& root,
                                 const std::function<void(const Definition::Ptr& child, int level)>& fun);
}

#endif
