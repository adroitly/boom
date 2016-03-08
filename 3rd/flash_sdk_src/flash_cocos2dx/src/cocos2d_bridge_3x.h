//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __COCOS2D_BRIDGE_3X_H__
#define __COCOS2D_BRIDGE_3X_H__

#include "cocos2d.h"

namespace cocos2d_bridge
{
    typedef cocos2d::DictElement    DictElement;
    typedef cocos2d::Texture2D      Texture2D;
    typedef cocos2d::Image          Image;
    typedef cocos2d::SpriteFrame    SpriteFrame;
    typedef cocos2d::BlendFunc      BlendFunc;
    typedef cocos2d::Rect           Rect;
    typedef cocos2d::Size           Size;
    typedef cocos2d::Ref            Object;
    typedef cocos2d::__Dictionary   Dictionary;
    typedef cocos2d::Node           NodeRGBA;
    typedef cocos2d::Vec2           Point;
    typedef cocos2d::Color3B        Color3B;
    typedef cocos2d::Color4F        Color4F;

    const int kVertexAttribFlag_Position                        = cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION;
    const int kVertexAttribFlag_TexCoords                       = cocos2d::GL::VERTEX_ATTRIB_FLAG_TEX_COORD;
    const int kVertexAttrib_Position                            = cocos2d::GLProgram::VERTEX_ATTRIB_POSITION;
    const int kVertexAttrib_TexCoords                           = cocos2d::GLProgram::VERTEX_ATTRIB_TEX_COORD;
    const Texture2D::PixelFormat kTexture2DPixelFormat_RGBA4444 = cocos2d::Texture2D::PixelFormat::RGBA4444;
    const Texture2D::PixelFormat kTexture2DPixelFormat_RGBA8888 = cocos2d::Texture2D::PixelFormat::RGBA8888;

#define kCCBrightAttributeNamePosition cocos2d::GLProgram::ATTRIBUTE_NAME_POSITION
#define kCCBrightAttributeNameTexCoord cocos2d::GLProgram::ATTRIBUTE_NAME_TEX_COORD

    inline void GLBlendFunc(GLenum sfactor, GLenum dfactor)
    {
        return cocos2d::GL::blendFunc(sfactor, dfactor);
    }

    inline void GLBindTexture2D(GLuint textureId)
    {
        cocos2d::GL::bindTexture2D(textureId);
    }

    inline void GLEnableVertexAttribs(unsigned int flags)
    {
        cocos2d::GL::enableVertexAttribs(flags);
    }
    
    inline void GLDeleteProgram(GLuint program)
    {
        cocos2d::GL::deleteProgram(program);
    }
    
    inline void GLUseProgram(GLuint program)
    {
        cocos2d::GL::useProgram(program);
    }
    
    inline int Object_getReferenceCount(Object* obj)
    {
        return obj->getReferenceCount();
    }

    inline bool Image_is8888(Image* image)
    {
        return image->getBitPerPixel() == 32;
    }
    
    inline Color4F Color4F_Make(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
    {
        return Color4F(r, g, b, a);
    }

    inline bool loadPngImageFromFile(const std::string& fullPath, Image& image)
    {
        auto fileUtils = cocos2d::FileUtils::getInstance();
		auto data = fileUtils->getDataFromFile(fullPath);
        bool bRet = image.initWithImageData(data.getBytes(), data.getSize());
        return bRet;
    }

    inline bool Texture2D_initWithData(Texture2D* texture2d,
                                       const void* data,
                                       ssize_t dataLen,
                                       Texture2D::PixelFormat pixelFormat,
                                       int pixelsWide,
                                       int pixelsHigh,
                                       const cocos2d::Size& contentSize)
    {
        return texture2d->initWithData(data, dataLen, pixelFormat, pixelsWide, pixelsHigh, contentSize);
    }

    inline cocos2d::Director* Director_getInstance()
    {
        return cocos2d::Director::getInstance();
    }

    inline cocos2d::Configuration* Configuration_getInstance()
    {
        return cocos2d::Configuration::getInstance();
    }

    inline cocos2d::SpriteFrameCache* SpriteFrameCache_getInstance()
    {
        return cocos2d::SpriteFrameCache::getInstance();
    }

    inline cocos2d::FileUtils* FileUtils_getInstance()
    {
        return cocos2d::FileUtils::getInstance();
    }

    inline SpriteFrame* SpriteFrameCache_getSpriteFrame(cocos2d::SpriteFrameCache* cache,
                                                        const std::string& name)
    {
        return cache->getSpriteFrameByName(name);
    }

    inline void Director_schedule(cocos2d::SEL_SCHEDULE selector,
                                  cocos2d::Ref* target,
                                  float interval,
                                  bool paused)
    {
        auto scheduler = cocos2d::Director::getInstance()->getScheduler();
        scheduler->schedule(selector, target, interval, paused);
    }

    inline void Director_unschedule(cocos2d::SEL_SCHEDULE selector, cocos2d::Ref* target)
    {
        cocos2d::Director::getInstance()->getScheduler()->unschedule(selector, target);
    }
}

#endif
