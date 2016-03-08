//
//  FlaUI.h
//  big-devil
//
//  Created by HJC on 15/5/29.
//
//

#ifndef __FLAUI_H__
#define __FLAUI_H__

#include "FlaSDK.h"

namespace fla_ex
{
    struct UIPreloadInfo
    {
        UIPreloadInfo()
        {
            scale = 1.0;
            format = FlaPixelFormat::RGBA8888;
            saveToFile = true;
        }
        float scale;
        FlaPixelFormat format;
        bool saveToFile;
    };

    cocos2d::SpriteFrame* getSpriteFrame(const FlaCollection& collection,
                                         const std::string& name,
                                         const UIPreloadInfo& info);

    // 可能会修改definitions的值
    void loadSpriteFrames(std::vector<FlaDefinition>& definitions, const UIPreloadInfo& info);
    void loadUIAsync(const char* binName);
}

#endif
