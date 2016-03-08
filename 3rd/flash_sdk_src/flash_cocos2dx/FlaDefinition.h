//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLADEFINITION_H__
#define __FLADEFINITION_H__

#include "FlaConfig.h"
#include "FlaEnum.h"
#include "FlaBitmapData.h"

namespace fla
{
    class Definition;
}

class FlaPlacement;
class FlaDefinition
{
public:
    FlaDefinition();
    ~FlaDefinition();

    FlaDefinition(const FlaDefinition& rhs);
    FlaDefinition& operator=(const FlaDefinition& rhs);

    explicit FlaDefinition(fla::Definition* impl);
    fla::Definition* getRaw() const;

    // 从文件中读取根定义
    static FlaDefinition loadData(const void* data, size_t dataLen, FlaErrorCode* error);

    // 从文件中读取指定的某个定义
    static FlaDefinition loadData(const void* data, size_t dataLen, int Id, FlaErrorCode* error);

    // 从文件中读取名字为name的某个定义
    static FlaDefinition loadData(const void* data, size_t dataLen, const std::string& name, FlaErrorCode* error);

    // 判断定义是否为空
    bool isNull() const;

    // 得到角色的状态
    FlaDefinition findState(const std::string& name) const;
    FlaDefinition stateAt(int index) const;

    cocos2d_bridge::Color4F getSceneColor() const;

    // 只读属性
    // 包围框
    cocos2d_bridge::Rect getBounds() const;

    // 所有状态的名字
    std::vector<std::string> getStateNames() const;

    std::vector<FlaPlacement> getChildPlacements(float scale) const;

    void replaceDefinition(int Id, const FlaDefinition& definition);

    // 名字
    std::string getName() const;

    // 标示符
    int getId() const;

    // 帧率
    float getFrameRate() const;

    // 数据Md5
    std::string getDataMd5() const;

    FlaMovieType getMovieType() const;

    // 转成对应的纹理
    cocos2d_bridge::Texture2D* transToTexture(FlaPixelFormat format) const;
    cocos2d_bridge::Texture2D* transToTexture(float scale, FlaPixelFormat format) const;
    cocos2d_bridge::Texture2D* transToTexture(float scale, float ratio, FlaPixelFormat format) const;

    // 转成对应的BitmapData
    FlaBitmapData transToBitmap(FlaPixelFormat format) const;
    FlaBitmapData transToBitmap(float scale, FlaPixelFormat format) const;
    FlaBitmapData transToBitmap(float scale, float ratio, FlaPixelFormat format) const;

    void walkChildren(const std::function<void(const FlaDefinition& child, int level)>& fun) const;

    bool operator<(const FlaDefinition& other) const
    {
        return _impl < other._impl;
    }

    bool operator==(const FlaDefinition& other) const
    {
        return _impl == other._impl;
    }

private:
    fla::Definition* _impl;
};

class FlaPlacement
{
public:
    FlaDefinition definition;
    cocos2d_bridge::AffineTransform transform;
    int depth;
};

#endif
