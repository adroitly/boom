//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLAMOVIECLIPNODE_H__
#define __FLAMOVIECLIPNODE_H__

#include "FlaConfig.h"
#include "FlaCacheStrategy.h"
#include "FlaMoviePart.h"

class FlaMovieNode;
struct FlaMovieNodeListener
{
    // 播放完动画
    virtual void FlaMovieNodeDidStartMovie(FlaMovieNode* node)
    {
        (void)node;
    }
    
    virtual void FlaMovieNodeDidFinishMovie(FlaMovieNode* node)
    {
        (void)node;
    }
    
    virtual void FlaMovieNodeDidStepFrame(FlaMovieNode* node)
    {
        (void)node;
    }
};

namespace fla
{
    class MovieClip;
    class MovieClipBridge;
    class MovieGlobalData;
    class MoviePartShareData;
}

class FlaGLProgram;
class FlaMovieNode : public cocos2d_bridge::NodeRGBA, public FlaCocos2dCacheStrategy
{
public:
    ~FlaMovieNode();
    
    static FlaMovieNode* createWithDefinition(const FlaDefinition& definition);
    static FlaMovieNode* createWithDefinition(const FlaDefinition& definition, float scale);
    
    // 回调函数
    std::function<void(FlaMovieNode*)> onMovieStart;
    std::function<void(FlaMovieNode*)> onMovieFinish;
    std::function<void(FlaMovieNode*)> onMovieStepFrame;
    
    // 设置listener，监听动画结束的消息
    void setListener(FlaMovieNodeListener* listener);
    FlaMovieNodeListener* getListener() const;
    
    void setBlendFunc(const cocos2d_bridge::BlendFunc& fun);
    
    void setFlaGLProgram(FlaGLProgram* program);
    FlaGLProgram* getFlaGLProgram() const;
    
    void setFlaGLProgramAdditionalInfo(void* info, void (*freeFun)(void* info));
    
    void setCacheStrategy(FlaCacheStrategy* cacheStrategy);
    FlaCacheStrategy* getCacheStrategy() const;

    FlaMoviePart findMoviePart(int Id);
    FlaMoviePart findMoviePart(const std::string& name);
    
    // 进入下一帧
    void stepFrame();
    void stepFrameRatio(float ratio);
    
    // 暂停
    void pauseStep();
    void pauseStep(int Id);
    void pauseStep(const std::string& name);
    
    // 恢复
    void resumeStep();
    void resumeStep(int Id);
    void resumeStep(const std::string& name);
    
    // 跳到第N帧
    void goToFrame(int N);
    
    // 当前帧
    int getCurrentFrame() const;
    
    // 总帧数
    int getFrameCount() const;
    
    // 切换状态
    bool changeState(const std::string& stateName);
    bool changeState(int index);
    bool hasState(const std::string& stateName);
    
    // 得到相应的定义
    FlaDefinition getDefinition() const;
    void setDefinition(const FlaDefinition& definition);
    
    // 类型
    FlaMovieType getMovieType() const;
    
    // 缩放比
    float getMovieScale() const;
    void  setMovieScale(float scale);
    
    // 是否绘画场景颜色
    void setDrawSceneColor(bool sceneColor);
    
    // 名字
    std::string getMovieName() const;
    std::string getStateName() const;
    
    int getMovieId() const;
    
    // 大小
    cocos2d_bridge::Size getMovieSize() const;
    
    void refreshSprites();
    
    bool isAtomHitted(const cocos2d_bridge::Point& pt) const;
    
    void setColorTransform(GLfloat colorMult[4], GLfloat colorAdd[4]);
    
    void setAutoFlipY(bool flag);
    
    virtual void setOpacity(GLubyte opacity) override;
    virtual void setColor(const cocos2d_bridge::Color3B& color) override;
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) override;
    virtual void updateDisplayedColor(const cocos2d_bridge::Color3B& parentColor) override;
    
    void setBlurLevelClip(bool flag, int level);
    
#if COCOS2D_VERSION >= 0x00030000
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
    virtual const cocos2d::Mat4& getNodeToParentTransform() const override;
    
protected:
    cocos2d::CustomCommand  _customCommand;
    
public:
#else
    virtual void draw() override;
    virtual cocos2d::CCAffineTransform nodeToParentTransform() override;
#endif
    
protected:
    FlaMovieNode(const FlaDefinition& define, float scale);
    
private:
    void refreshMovieBounds();
    void refreshColorTransform();
    void innerDraw(const void* matrix);
    
private:
    fla::MovieGlobalData*           _movieGlobalData;
    fla::MovieClip*                 _movieClip;
    fla::MovieClipBridge*           _movieClipBridge;
    FlaGLProgram*                   _glProgram;
    cocos2d_bridge::BlendFunc       _blendFunc;
    FlaCacheStrategy*               _cacheStrategy;
    cocos2d_bridge::Rect            _movieBounds;
    void*                           _glAdditionalInfo;
    void (*_glAddtionFreeFun)(void* info);
    float                           _movieScale;
    int                             _blurClipLevel;
    bool                            _drawSceneColor;
    bool                            _autoFlipY;
};

class FlaTimeMovieNode : public FlaMovieNode
{
public:
    static FlaTimeMovieNode* createWithDefinition(const FlaDefinition& definition);
    static FlaTimeMovieNode* createWithDefinition(const FlaDefinition& definition, float scale);
    
    ~FlaTimeMovieNode();
    
    void time_update(float t);
    void time_setEnableRatio(bool flag);
    void time_setFrameRate(float frameRate);
    
protected:
    FlaTimeMovieNode(const FlaDefinition& definition, float scale);
    
private:
    float   _stepTime;
    float   _frameTime;
    bool    _enableRatio;
};

#endif
