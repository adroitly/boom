//
//  BWRoleCacheStrategy.h
//  Game
//
//  Created by HJC on 14-6-25.
//
//

#ifndef __FLAROLECACHESTRATEGY_H__
#define __FLAROLECACHESTRATEGY_H__

#include "FlaSDK.h"
#include <set>

namespace fla_ex
{
    class RoleCacheStrategy : public FlaTexturePackCacheStrategy
    {
    public:
        RoleCacheStrategy();
        RoleCacheStrategy(const std::string& filePath);

        virtual bool isInTexturePackage(const FlaCacheInfo& info, int* packageId) const override;
        virtual FlaTexturePackage packTexturePackage(const FlaCacheInfo& info, int packageId) override;

        void setRoot(const FlaDefinition& root);
        static void setPackageStateNames(const std::vector<std::string>& stateNames);

    private:
        void walkChildren(const FlaDefinition& root,
                          int packageId,
                          const std::function<void(const FlaDefinition& child)>& fun);
        bool hasPackageNode(int packageId, int nodeId) const;
        static int getPackageId(const std::string& name);

    private:
        std::set<int> _packages[2];
        static std::vector<std::string> s_packageStateNames;
    };
}

#endif
