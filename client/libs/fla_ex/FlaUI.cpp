//
//  FlaUI.cpp
//  big-devil
//
//  Created by HJC on 15/5/29.
//
//

#include "FlaUI.h"
#include "libra/libra_strbuf.h"
#include "libra/libra_path.h"
#include "clover/ScopeGuard.h"
#include "core/utility/fla_md5.h"
#include <tuple>
#include "SDKWrapper.h"
#include "FlaAsync.h"

namespace fla_ex
{
    static std::string s_getPackageDir()
    {
        auto writablePath = cocos2d::FileUtils::getInstance()->getWritablePath();
        return libra::path_join(writablePath, "UICaches");
    }

    static std::vector<FlaDefinition> s_getAllSymbolDefinitions(const FlaCollection& collection)
    {
        std::vector<FlaDefinition> definitions;
        collection.walkName(
            [&](const FlaDefinition& def)
            {
                if (def.getMovieType() != FlaMovieType::Scene && def.getMovieType() != FlaMovieType::Font)
                {
                    definitions.push_back(def);
                }
            });
        return definitions;
    }

    cocos2d::SpriteFrame* getSpriteFrame(const FlaCollection& collection,
                                         const std::string& name,
                                         const UIPreloadInfo& preloadInfo)
    {
        if (collection.isNull())
        {
            return nullptr;
        }

        auto defintion = collection.findDefinition(name);
        if (defintion.isNull())
        {
            return nullptr;
        }
        auto frame = FlaTexturePackage::getSpriteFrame(defintion, preloadInfo.scale);
        if (frame)
        {
            return frame->toSpriteFrame();
        }

        std::string packageDir = s_getPackageDir();
        std::string packageName = FlaSDK::getKeyOfCache(collection.getDataMd5(), 0, preloadInfo.scale);
        if (FlaTexturePackage::load(packageDir, packageName, preloadInfo.format))
        {
            frame = FlaTexturePackage::getSpriteFrame(defintion, preloadInfo.scale);
            if (frame)
            {
                return frame->toSpriteFrame();
            }
        }

        auto definitions = s_getAllSymbolDefinitions(collection);
        auto package = FlaTexturePackage::pack(definitions, preloadInfo.scale, preloadInfo.format);
        package.transToSpriteFrames(packageDir, packageName);

        if (preloadInfo.saveToFile)
        {
            package.saveAsPngAsync(packageDir, packageName);
        }

        return FlaTexturePackage::getSpriteFrame(defintion, preloadInfo.scale)->toSpriteFrame();
    }

    static bool hasAllDefinitions(const std::vector<FlaDefinition>& definitions, float scale)
    {
        return std::all_of(definitions.begin(),
                           definitions.end(),
                           [&](const FlaDefinition& def)
                           {
                               return FlaTexturePackage::getSpriteFrame(def, scale);
                           });
    }

    static std::string s_getPackageName(const std::vector<FlaDefinition>& definitions, float scale)
    {
        strbuf_init_stack(result, 64);
        CLOVER_SCOPE_EXIT
        {
            strbuf_finish(result);
        };

        for (auto& def : definitions)
        {
            auto md5 = def.getDataMd5();
            strbuf_push_lstring(result, md5.c_str(), md5.size());
            strbuf_push_char(result, '_');
            strbuf_push_uint32(result, def.getId());
            strbuf_push_char(result, '_');
        }

        strbuf_push_uint32(result, static_cast<uint32_t>(scale * FlaSDK::getTextureContentScaleFactor() * 100));
        md5_state_t state;
        md5_init(&state);
        md5_append(&state, (md5_byte_t*)strbuf_cstr(result), (int)strbuf_length(result));

        md5_byte_t buf[16];
        md5_finish(&state, buf);

        return libra::str_md5HexString(buf);
    }

    void loadSpriteFrames(std::vector<FlaDefinition>& definitions, const UIPreloadInfo& preloadInfo)
    {
        // 排序，并去掉重复的值
        std::sort(definitions.begin(), definitions.end());
        auto iter = std::unique(definitions.begin(), definitions.end());
        if (iter != definitions.end())
        {
            definitions.erase(iter, definitions.end());
        }

        std::sort(definitions.begin(),
                  definitions.end(),
                  [](const FlaDefinition& lhs, const FlaDefinition& rhs)
                  {
                      return std::make_pair(lhs.getDataMd5(), lhs.getId()) <
                             std::make_pair(rhs.getDataMd5(), rhs.getId());
                  });

        if (hasAllDefinitions(definitions, preloadInfo.scale))
        {
            return;
        }

        std::string packageDir = s_getPackageDir();
        std::string packageName = s_getPackageName(definitions, preloadInfo.scale);

        if (FlaTexturePackage::load(packageDir, packageName, preloadInfo.format))
        {
            return;
        }

        if (preloadInfo.saveToFile)
        {
            auto package = FlaTexturePackage::pack(definitions, preloadInfo.scale, preloadInfo.format);
            package.transToSpriteFrames(packageDir, packageName);

            if (preloadInfo.saveToFile)
            {
                package.saveAsPngAsync(packageDir, packageName);
            }
        }
        else
        {
            auto iter = std::remove_if(definitions.begin(),
                                       definitions.end(),
                                       [&](const FlaDefinition& rhs)
                                       {
                                           return FlaTexturePackage::getSpriteFrame(rhs, preloadInfo.scale);
                                       });
            if (iter != definitions.end())
            {
                definitions.erase(iter, definitions.end());
            }
            auto package = FlaTexturePackage::pack(definitions, preloadInfo.scale, preloadInfo.format);
            package.transToSpriteFrames(packageDir, packageName);
        }
    }
    
    void loadUIAsync(const char* binName)
    {
        static fla_ex::UIPreloadInfo defaultInfo;
        FlaSDK::async([=]()
                      {
                          FlaCollection collection = fla_ex::getCollection(binName);
                          if (collection.isNull())
                          {
                              return;
                          }
                          
                          std::string packageDir = s_getPackageDir();
                          std::string packageName = FlaSDK::getKeyOfCache(collection.getDataMd5(), 0, defaultInfo.scale);
                          
                          if (FlaTexturePackage::isExit(packageDir, packageName))
                          {
                              return;
                          }
                          
                          auto definitions = s_getAllSymbolDefinitions(collection);
                          auto package = FlaTexturePackage::pack(definitions, defaultInfo.scale, defaultInfo.format);
                          package.saveAsPngAsync(packageDir, packageName);
                      },
                      []()
                      {
                      });
    }
}
