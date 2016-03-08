//=============================================================================
//  GameBox
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "Preloader.h"
#include "clover/ScopeGuard.h"
#include "RoleCacheStrategy.h"
#include "SDKWrapper.h"

namespace fla_ex
{
    static std::vector<PreloadItem> s_uniquePreloadItems(const std::vector<PreloadItem>& items)
    {
        auto result = items;

        // 去掉重复
        std::sort(result.begin(), result.end());
        auto iter = std::unique(result.begin(), result.end());
        if (iter != result.end())
        {
            result.erase(iter, result.end());
        }
        return result;
    }

    template <typename CallBackT>
    static void s_doProgress(CallBackT&& onProgress, int total, int current)
    {
        if (onProgress)
        {
            onProgress(total, current);
        }
    }

    template <typename CallBackT>
    static void s_doFinish(CallBackT&& onFinish)
    {
        if (onFinish)
        {
            onFinish();
        }
    }

    void Preloader::preload(const std::vector<PreloadItem>& roleItems_, const std::vector<PreloadItem>& effectItems_)
    {
        auto roleItems = s_uniquePreloadItems(roleItems_);
        auto effectItems = s_uniquePreloadItems(effectItems_);

        FlaCacheStrategy::beginPreload();
        CLOVER_SCOPE_EXIT
        {
            FlaCacheStrategy::endPreload();
        };

        _totalLoadSize = 0;
        _currentLoadSize = 0;

        auto myCallback = [&](const fla::TextureFrame*)
        {
            _currentLoadSize++;
            s_doProgress(onProgress, _totalLoadSize, _currentLoadSize);
            if (_currentLoadSize >= _totalLoadSize)
            {
                s_doFinish(onFinish);
            }
        };

        for (auto& item : roleItems)
        {
            RoleCacheStrategy* strategy = new RoleCacheStrategy();
            CLOVER_SCOPE_EXIT
            {
                strategy->release();
            };
            
            strategy->setPixelFormat(item.format);
            strategy->setRoot(item.definition);
            _totalLoadSize += strategy->preload(item.definition, item.definition, item.scale, myCallback);
        }

        for (auto& item : effectItems)
        {
            auto cache = fla_ex::getGlobalCacheStrategy(item.format);
            _totalLoadSize += cache->preload(item.definition, item.definition, item.scale, myCallback);
        }

        if (_totalLoadSize == _currentLoadSize)
        {
            s_doProgress(onProgress, _totalLoadSize, _currentLoadSize);
            s_doFinish(onFinish);
        }
    }
}
