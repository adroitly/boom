//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __COCOS2D_BRIDGE_2X_H__
#define __COCOS2D_BRIDGE_2X_H__

#include "cocos2d.h"

namespace cocos2d_bridge
{
    typedef cocos2d::CCDictElement DictElement;
    typedef cocos2d::CCTexture2D Texture2D;
    typedef cocos2d::CCImage Image;
    typedef cocos2d::CCSpriteFrame SpriteFrame;
    typedef cocos2d::ccBlendFunc BlendFunc;
    typedef cocos2d::CCRect Rect;
    typedef cocos2d::CCSize Size;
    typedef cocos2d::CCObject Object;
    typedef cocos2d::CCDictionary Dictionary;
    typedef cocos2d::CCNodeRGBA NodeRGBA;
    typedef cocos2d::CCPoint Point;
    typedef cocos2d::ccColor3B Color3B;
    typedef cocos2d::ccColor4F Color4F;

    const int kVertexAttribFlag_Position = cocos2d::kCCVertexAttribFlag_Position;
    const int kVertexAttribFlag_TexCoords = cocos2d::kCCVertexAttribFlag_TexCoords;
    const int kVertexAttrib_Position = cocos2d::kCCVertexAttrib_Position;
    const int kVertexAttrib_TexCoords = cocos2d::kCCVertexAttrib_TexCoords;
    const cocos2d::CCTexture2DPixelFormat kTexture2DPixelFormat_RGBA4444 = cocos2d::kCCTexture2DPixelFormat_RGBA4444;
    const cocos2d::CCTexture2DPixelFormat kTexture2DPixelFormat_RGBA8888 = cocos2d::kCCTexture2DPixelFormat_RGBA8888;

#define kCCBrightAttributeNamePosition kCCAttributeNamePosition
#define kCCBrightAttributeNameTexCoord kCCAttributeNameTexCoord

    inline void GLBlendFunc(GLenum sfactor, GLenum dfactor)
    {
        return cocos2d::ccGLBlendFunc(sfactor, dfactor);
    }

    inline void GLBindTexture2D(GLuint textureId)
    {
        cocos2d::ccGLBindTexture2D(textureId);
    }

    inline void GLEnableVertexAttribs(unsigned int flags)
    {
        cocos2d::ccGLEnableVertexAttribs(flags);
    }

    inline void GLDeleteProgram(GLuint program)
    {
        cocos2d::ccGLDeleteProgram(program);
    }

    inline void GLUseProgram(GLuint program)
    {
        cocos2d::ccGLUseProgram(program);
    }

    inline int Object_getReferenceCount(Object* obj)
    {
        return obj->retainCount();
    }

    inline bool Image_is8888(Image* image)
    {
        return image->getBitsPerComponent() == 8;
    }

    inline Color4F Color4F_Make(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
    {
        return cocos2d::ccc4f(r, g, b, a);
    }

    inline bool loadPngImageFromFile(const std::string& fullPath, Image& image)
    {
        auto fileUtils = cocos2d::CCFileUtils::sharedFileUtils();
        unsigned long size = 0;
        unsigned char* buffer = fileUtils->getFileData(fullPath.c_str(), "rb", &size);
        bool isOK = image.initWithImageData((void*)buffer, size, cocos2d::CCImage::kFmtPng);
        CC_SAFE_DELETE_ARRAY(buffer);
        return isOK;
    }

    inline bool Texture2D_initWithData(Texture2D* texture2d,
                                       const void* data,
                                       ssize_t dataLen,
                                       cocos2d::CCTexture2DPixelFormat pixelFormat,
                                       int pixelsWide,
                                       int pixelsHigh,
                                       const cocos2d::CCSize& contentSize)
    {
        (void)dataLen;
        return texture2d->initWithData(data, pixelFormat, pixelsWide, pixelsHigh, contentSize);
    }

    inline cocos2d::CCDirector* Director_getInstance()
    {
        return cocos2d::CCDirector::sharedDirector();
    }

    inline cocos2d::CCConfiguration* Configuration_getInstance()
    {
        return cocos2d::CCConfiguration::sharedConfiguration();
    }

    inline cocos2d::CCFileUtils* FileUtils_getInstance()
    {
        return cocos2d::CCFileUtils::sharedFileUtils();
    }

    inline SpriteFrame* SpriteFrameCache_getSpriteFrame(cocos2d::CCSpriteFrameCache* cache, const std::string& name)
    {
        return cache->spriteFrameByName(name.c_str());
    }

    inline void Director_schedule(cocos2d::SEL_SCHEDULE selector,
                                  cocos2d::CCObject* target,
                                  float interval,
                                  bool paused)
    {
        auto scheduler = cocos2d::CCDirector::sharedDirector()->getScheduler();
        scheduler->scheduleSelector(selector, target, interval, paused);
    }

    inline void Director_unschedule(cocos2d::SEL_SCHEDULE selector, cocos2d::CCObject* target)
    {
        auto scheduler = cocos2d::CCDirector::sharedDirector()->getScheduler();
        scheduler->unscheduleSelector(selector, target);
    }
}

#endif
