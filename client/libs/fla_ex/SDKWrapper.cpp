//
//  FlaSDKWrapper.cpp
//  Game
//
//  Created by HJC on 14-1-10.
//
//

#include "SDKWrapper.h"
using namespace cocos2d;

namespace fla_ex
{
    FlaCacheStrategy* getGlobalCacheStrategy(FlaPixelFormat pixelFormat)
    {
        static FlaCacheStrategy* s_4444cacheStrategy = NULL;
        static FlaCacheStrategy* s_8888cacheStrategy = NULL;
        if (pixelFormat == FlaPixelFormat::RGBA4444)
        {
            if (s_4444cacheStrategy == NULL)
            {
                s_4444cacheStrategy = new FlaAllTexturePackCacheStrategy();
                s_4444cacheStrategy->setPixelFormat(FlaPixelFormat::RGBA4444);
            }
            return s_4444cacheStrategy;
        }

        if (s_8888cacheStrategy == NULL)
        {
            s_8888cacheStrategy = new FlaAllTexturePackCacheStrategy();
            s_8888cacheStrategy->setPixelFormat(FlaPixelFormat::RGBA8888);
        }
        return s_8888cacheStrategy;
    }

    FlaCollection getCollection(const std::string& binName)
    {
        auto collection = FlaResourceCache::getInstance().collectionForKey(binName);
        if (!collection.isNull())
        {
            return collection;
        }

        auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(binName);
        collection = FlaCollection::loadData(data.getBytes(), data.getSize(), NULL);

        if (!collection.isNull())
        {
            FlaResourceCache::getInstance().setCollection(collection, binName);
        }
        return collection;
    }
}