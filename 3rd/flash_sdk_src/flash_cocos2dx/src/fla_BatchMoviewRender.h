//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_BATCHMOVIEWRENDER_H__
#define __FLA_BATCHMOVIEWRENDER_H__

#include <boost/noncopyable.hpp>
#include <memory>
#include "../base/fla_Quad.h"
#include "../base/fla_BatchStack.h"
#include "../FlaConfig.h"
#include "../FlaCacheStrategy.h"
#include "../../core/definition/fla_Definition.h"
#include "../../core/definition/fla_PlaceObject.h"
#include "../FlaGLProgram.h"

namespace fla
{
    typedef struct
    {
        cocos2d_bridge::BlendFunc blendFunc;
        FlaGLProgram* glProgram;
        FlaCacheStrategy* cacheStrategy;
        FlaDefinition root;
        void* shaderInfo;
        float movieScale;
    } BatchRenderInfo;

    class MovieClip;
    class BatchMoviewRender : boost::noncopyable
    {
    public:
        BatchMoviewRender(size_t quadCapacity);
        ~BatchMoviewRender();

        void setClipEnable(bool clipEnabled, int blurClipLevel, const Rect& clipRect);
        void visit(MovieClip* node, const Matrix& matrix, const BatchRenderInfo& drawInfo);

    private:
        void drawQuadFrame(const gles::Quad& quad);
        void pushQuad(MovieClip* node, int level);
        void flushQuads();
        void quickVisit(MovieClip* node, int level);
        void quickVisit2(MovieClip* node, int level);
        void innerVisit(MovieClip* node, int level);
        void flush();
        void setupBlendMode(BlendMode blendMode);
        void setupColorTransform(const ColorTransform& colorTrans);
        void clearFlags();
        GLushort* getTriangleIndices(size_t size);
        bool genSpriteIfNeed(MovieClip* clip, FlaCacheStrategy* cacheStrategy, FlaCacheInfo& cacheInfo);

    private:
        std::vector<gles::Quad> _quads;
        cocos2d_bridge::Texture2D* _texture2d;

        FlaCacheInfo _cacheInfo;
        FlaCacheStrategy* _cacheStrategy;
        cocos2d_bridge::BlendFunc _defaultBlendFunc;
        FlaGLProgram* _glProgram;

        BatchStack<ColorTransform> _colorStack;
        BatchStack<Matrix> _matrixStack;
        BatchStack<BlendMode> _blendModeStack;

        struct
        {
            gles::CoordPoint minPoint;
            gles::CoordPoint maxPoint;
        } _clipRect;

        size_t _lastQuadSize;
        GLushort* _lastQuadIndices;

        int _blurClipLevel;
        bool _clipEnabled;
        bool _isColorTransformDirty;
        bool _isBlendModeDirty;
    };
}

#endif
