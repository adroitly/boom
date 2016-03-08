//
//  BWRoleCacheStrategy.cpp
//  Game
//
//  Created by HJC on 14-6-25.
//
//

#include "RoleCacheStrategy.h"
using namespace cocos2d;

namespace fla_ex
{
    std::vector<std::string> RoleCacheStrategy::s_packageStateNames;

    void RoleCacheStrategy::setPackageStateNames(const std::vector<std::string>& stateNames)
    {
        s_packageStateNames = stateNames;
    }

    int RoleCacheStrategy::getPackageId(const std::string& name)
    {
        for (auto& str : s_packageStateNames)
        {
            if (str == name)
            {
                return 0;
            }
        }
        return 1;
    }

    RoleCacheStrategy::RoleCacheStrategy()
    {
    }

    RoleCacheStrategy::RoleCacheStrategy(const std::string& filePath) : FlaTexturePackCacheStrategy(filePath)
    {
    }

    void RoleCacheStrategy::walkChildren(const FlaDefinition& root,
                                         int packageId,
                                         const std::function<void(const FlaDefinition& child)>& fun)
    {
        for (auto& name : root.getStateNames())
        {
            auto stateNode = root.findState(name);
            if (!stateNode.isNull())
            {
                if (RoleCacheStrategy::getPackageId(name) == packageId)
                {
                    stateNode.walkChildren([&](const FlaDefinition& child, int level)
                                           {
                                               if (child.getMovieType() == FlaMovieType::Shape)
                                               {
                                                   fun(child);
                                               }
                                           });
                }
            }
        }
    }

    bool RoleCacheStrategy::hasPackageNode(int packageId, int nodeId) const
    {
        return (_packages[packageId].count(nodeId) > 0);
    }

    void RoleCacheStrategy::setRoot(const FlaDefinition& root)
    {
        _packages[0].clear();
        _packages[1].clear();

        walkChildren(root,
                     0,
                     [&](const FlaDefinition& node)
                     {
                         _packages[0].insert(node.getId());
                     });

        walkChildren(root,
                     1,
                     [&](const FlaDefinition& node)
                     {
                         if (!hasPackageNode(0, node.getId()))
                         {
                             _packages[1].insert(node.getId());
                         }
                     });
    }

    bool RoleCacheStrategy::isInTexturePackage(const FlaCacheInfo& info, int* packageId) const
    {
        assert(packageId);
        if (hasPackageNode(0, info.node.getId()))
        {
            *packageId = 0;
            return true;
        }

        if (hasPackageNode(1, info.node.getId()))
        {
            *packageId = 1;
            return true;
        }

        return false;
    }

    FlaTexturePackage RoleCacheStrategy::packTexturePackage(const FlaCacheInfo& info, int packageId)
    {
        std::set<int> Ids;
        std::vector<FlaDefinition> definitions;

        definitions.reserve(_packages[packageId].size());
        walkChildren(info.root,
                     packageId,
                     [&](const FlaDefinition& node)
                     {
                         if (hasPackageNode(packageId, node.getId()) && Ids.count(node.getId()) == 0)
                         {
                             definitions.push_back(node);
                             Ids.insert(node.getId());
                         }
                     });
        return FlaTexturePackage::pack(definitions, info.movieScale, getPixelFormat());
    }
}
