//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_DefinitionUtils.h"
#include <set>
#include "fla_DefinitionShape.h"
#include "fla_DefinitionRole.h"
#include "fla_DefinitionScene.h"
#include "fla_DefinitionAnimation.h"
#include "fla_DefinitionImage.h"
#include "fla_DefinitionPlaceholder.h"
#include "fla_DefinitionPackage.h"
#include "./bin/fla_BinaryReader.h"
#include "./fla_DefinitionFont.h"
#include "./fla_DefinitionText.h"
#include "./shape/fla_RenderShape.h"
#include "../graphics/fla_RenderOfDefinition.h"

namespace fla
{
    static void s_extractAllShapes(std::set<Definition::Ptr>& shapes,
                                   std::set<Definition::Ptr>& visited,
                                   const Definition::Ptr& root)
    {
        if (visited.count(root) > 0)
        {
            return;
        }

        visited.insert(root);
        switch (root->getType())
        {
            case DefinitionType::Shape:
                shapes.insert(root);
                break;

            case DefinitionType::Scene:
            case DefinitionType::Animation:
            case DefinitionType::Package:
            {
                auto sprite = fla::ptr_case<DefinitionAnimation>(root);
                for (auto& item : sprite->getDefinitions())
                {
                    s_extractAllShapes(shapes, visited, item);
                }
            }
            break;

            case DefinitionType::Role:
            {
                auto role = fla::ptr_case<DefinitionRole>(root);
                for (auto& state : role->getStates())
                {
                    s_extractAllShapes(shapes, visited, state.definition);
                }
            }
            break;

            default:
                break;
        }
    }

    void extractAllShapes(std::set<Definition::Ptr>& shapes, const Definition::Ptr& root)
    {
        std::set<Definition::Ptr> visited;
        s_extractAllShapes(shapes, visited, root);
    }

    bool Definition_isAnimation(const Definition::Ptr& definition)
    {
        auto type = definition->getType();
        return (type == DefinitionType::Animation) || (type == DefinitionType::Scene) ||
               (type == DefinitionType::Package);
    }

    template <typename Fun>
    static Definition::Ptr s_loadData(const void* data, size_t dataLen, LoadDataInfo info, ErrorCode* error, Fun lambda)
    {
        fla::BinaryReader reader;
        reader.setIgnorePlaceHolde(info.ignorePlaceHolde);
        reader.setCheckAuthorizedFunc(info.checkAuthorizedFunc);

        fla::ErrorCode errorCode = fla::ErrorCode::Success;
        fla::Definition::Ptr definition;
        if (reader.loadData(data, dataLen, &errorCode))
        {
            definition = lambda(reader);
            if (!definition)
            {
                errorCode = fla::ErrorCode::NoThisDefine;
            }
        }
        if (error)
        {
            *error = errorCode;
        }
        return definition;
    }

    Definition::Ptr Definition_loadData(const void* data, size_t dataLen, LoadDataInfo info, NullType, ErrorCode* error)
    {
        return s_loadData(data,
                          dataLen,
                          info,
                          error,
                          [&](fla::BinaryReader& reader)
                          {
                              return reader.readRoot();
                          });
    }

    Definition::Ptr Definition_loadData(const void* data, size_t dataLen, LoadDataInfo info, int Id, ErrorCode* error)
    {
        return s_loadData(data,
                          dataLen,
                          info,
                          error,
                          [&](fla::BinaryReader& reader)
                          {
                              return reader.readDefinition(Id);
                          });
    }

    Definition::Ptr Definition_loadData(const void* data,
                                        size_t dataLen,
                                        LoadDataInfo info,
                                        const std::string& name,
                                        ErrorCode* error)
    {
        return s_loadData(data,
                          dataLen,
                          info,
                          error,
                          [&](fla::BinaryReader& reader)
                          {
                              return reader.readDefinition(name);
                          });
    }

    Definition::Ptr Definition_findState(const Definition* impl, const std::string& name)
    {
        assert(impl);
        if (impl->getType() != fla::DefinitionType::Role)
        {
            return Definition::Ptr();
        }
        auto role = static_cast<const fla::DefinitionRole*>(impl);
        return role->findDefinition(name);
    }

    Definition::Ptr Definition_stateAt(const Definition* impl, int index)
    {
        assert(impl);
        if (impl->getType() != fla::DefinitionType::Role)
        {
            return Definition::Ptr();
        }
        auto role = static_cast<const fla::DefinitionRole*>(impl);
        return role->getStates()[index].definition;
    }

    Color4 Definition_getSceneColor(const Definition* impl)
    {
        assert(impl);
        if (impl->getType() != fla::DefinitionType::Scene)
        {
            return Color4(0, 0, 0, 0);
        }
        auto scene = static_cast<const fla::DefinitionScene*>(impl);
        return scene->getColor();
    }

    void Definition_changeDefaultState(Definition* root, const std::string& name)
    {
        assert(root);
        if (root->getType() != fla::DefinitionType::Role)
        {
            return;
        }
        auto role = static_cast<fla::DefinitionRole*>(root);
        return role->setDefualtState(name);
    }

    std::vector<std::string> Definition_getStateNames(const Definition* impl)
    {
        assert(impl);
        std::vector<std::string> names;
        if (impl->getType() != fla::DefinitionType::Role)
        {
            return names;
        }

        auto role = static_cast<const fla::DefinitionRole*>(impl);
        for (auto& state : role->getStates())
        {
            names.push_back(state.name);
        }
        return std::move(names);
    }

    static void walkChildrenImpl(const fla::Definition::Ptr& root,
                                 const std::function<void(const Definition::Ptr& child, int level)>& fun,
                                 int level)
    {
        auto type = root->getType();
        if (type == fla::DefinitionType::Scene || type == fla::DefinitionType::Animation ||
            type == fla::DefinitionType::Package)
        {
            auto sprite = fla::ptr_case<fla::DefinitionAnimation>(root);
            for (auto& item : sprite->getDefinitions())
            {
                fun(item, level);
                walkChildrenImpl(item, fun, level + 1);
            }
        }
        else if (type == fla::DefinitionType::Role)
        {
            auto role = fla::ptr_case<fla::DefinitionRole>(root);
            for (auto& state : role->getStates())
            {
                fun(state.definition, level);
                walkChildrenImpl(state.definition, fun, level + 1);
            }
        }
    }

    void Definition_walkChildren(const Definition::Ptr& root,
                                 const std::function<void(const Definition::Ptr& child, int level)>& fun)
    {
        walkChildrenImpl(root, fun, 1);
    }
}
