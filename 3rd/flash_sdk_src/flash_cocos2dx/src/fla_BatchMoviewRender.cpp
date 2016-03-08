//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_BatchMoviewRender.h"
#include "fla_TextureFrame.h"
#include "fla_MovieClip.h"
#include "../../core/definition/fla_DefinitionUtils.h"
#include "clover/ScopeGuard.h"
#include "cocos2d_bridge.h"
#include "libra/libra_bits.h"
#include "../../core/base/fla_Utils.h"
#include "fla_MovieShareData.h"
#include "fla_Settings.h"

using namespace cocos2d;

namespace fla
{
    GLushort* BatchMoviewRender::getTriangleIndices(size_t size)
    {
        if (size <= _lastQuadSize)
        {
            return _lastQuadIndices;
        }

        _lastQuadIndices = (GLushort*)realloc(_lastQuadIndices, size * 6 * sizeof(GLushort));
        for (size_t i = _lastQuadSize; i < size; i++)
        {
            _lastQuadIndices[i * 6 + 0] = i * 4 + 0;
            _lastQuadIndices[i * 6 + 1] = i * 4 + 1;
            _lastQuadIndices[i * 6 + 2] = i * 4 + 2;

            _lastQuadIndices[i * 6 + 3] = i * 4 + 3;
            _lastQuadIndices[i * 6 + 4] = i * 4 + 2;
            _lastQuadIndices[i * 6 + 5] = i * 4 + 1;
        }
        _lastQuadSize = size;
        return _lastQuadIndices;
    }

    void BatchMoviewRender::clearFlags()
    {
        _texture2d = nullptr;
        _isColorTransformDirty = true;
        _isBlendModeDirty = true;
        _glProgram = nullptr;
    }

    BatchMoviewRender::BatchMoviewRender(size_t quadCapacity)
    {
        _colorStack.push(ColorTransform::identity());
        _blendModeStack.push(BlendMode::Normal);
        _quads.reserve(quadCapacity);
        clearFlags();
        _lastQuadSize = 0;
        _lastQuadIndices = nullptr;
        _blurClipLevel = -1;
        _clipEnabled = false;
    }

    BatchMoviewRender::~BatchMoviewRender()
    {
        free(_lastQuadIndices);
    }

    void BatchMoviewRender::visit(MovieClip* node, const Matrix& matrix, const BatchRenderInfo& drawInfo)
    {
        assert(_matrixStack.isEmpty());
        assert(drawInfo.glProgram);

        clearFlags();
        _matrixStack.push(matrix);
        CLOVER_SCOPE_EXIT
        {
            _matrixStack.pop();
        };

        _cacheInfo.contentScale = fla::settings::getTextureContentScale();
        _cacheInfo.movieScale = drawInfo.movieScale;
        _cacheInfo.root = drawInfo.root;
        _glProgram = drawInfo.glProgram;
        _cacheStrategy = drawInfo.cacheStrategy;
        _defaultBlendFunc = drawInfo.blendFunc;

        _glProgram->use();
        if (drawInfo.shaderInfo)
        {
            _glProgram->setAdditionalInfo(drawInfo.shaderInfo);
        }
        _glProgram->setUniformsForBuiltins();

        cocos2d_bridge::GLEnableVertexAttribs(cocos2d_bridge::kVertexAttribFlag_Position |
                                              cocos2d_bridge::kVertexAttribFlag_TexCoords);

        innerVisit(node, 0);

        flush();

        assert(_colorStack.isUnique());
        assert(_colorStack.isUnique());
    }

    void BatchMoviewRender::innerVisit(MovieClip* node, int level)
    {
        assert(node);
        bool hasColorTransform = libra::bit_test(node->_flags, MovieClip::Bit_HasColorTransform);
        bool hasBlendMode = libra::bit_test(node->_flags, MovieClip::Bit_HasBlendMode) && _blendModeStack.isUnique();

        if (hasColorTransform || hasBlendMode)
        {
            flush();
            if (hasColorTransform)
            {
                _colorStack.push(_colorStack.top() * node->_colorTransform);
                _isColorTransformDirty = true;
            }

            if (hasBlendMode)
            {
                _blendModeStack.push(node->_blendMode);
                _isBlendModeDirty = true;
            }

            CLOVER_SCOPE_EXIT
            {
                flush();
                if (hasColorTransform)
                {
                    _colorStack.pop();
                    _isColorTransformDirty = true;
                }

                if (hasBlendMode)
                {
                    _blendModeStack.pop();
                    _isBlendModeDirty = true;
                }
            };
            quickVisit(node, level);
        }
        else
        {
            quickVisit(node, level);
        }
    }

    bool BatchMoviewRender::genSpriteIfNeed(MovieClip* movieClip,
                                            FlaCacheStrategy* cacheStrategy,
                                            FlaCacheInfo& cacheInfo)
    {
        assert(movieClip && movieClip->isLeaf());
        if (movieClip->_leaf.sprite)
        {
            return true;
        }

        auto type = movieClip->_state->getType();
        if (type == DefinitionType::Placeholder || type == DefinitionType::Null)
        {
            return false;
        }

        cacheInfo.node = FlaDefinition(movieClip->_definition.get());
        cacheInfo.morphRatio = movieClip->getFloatRatio();

        auto quickSprite = cacheStrategy->cache(cacheInfo);
        quickSprite->updateQuad(movieClip->getDefinition()->isFixHscreen());

        movieClip->setQuickSprite(quickSprite);
        return true;
    }

    static unsigned int s_checkCode(const gles::CoordPoint& minPt,
                                    const gles::CoordPoint& maxPt,
                                    const gles::CoordPoint& pt)
    {
        unsigned int code = 0;
        if (pt.x < minPt.x)
        {
            code = 0x01;
        }
        else if (pt.x > maxPt.x)
        {
            code = 0x02;
        }

        if (pt.y < minPt.y)
        {
            code |= (0x01 << 2);
        }
        else if (pt.y > maxPt.y)
        {
            code |= (0x02 << 2);
        }
        return code;
    }

    static bool s_isQuadInside(const gles::CoordPoint& minPt, const gles::CoordPoint& maxPt, const gles::Quad& quad)
    {
        auto code0 = s_checkCode(minPt, maxPt, quad.topLeft.position);
        if (!code0)
        {
            return true;
        }

        auto code1 = s_checkCode(minPt, maxPt, quad.topRight.position);
        if (!(code1 & code0))
        {
            return true;
        }

        auto code2 = s_checkCode(minPt, maxPt, quad.bottomLeft.position);
        if (!(code2 & code0) || !(code2 & code1))
        {
            return true;
        }

        auto code3 = s_checkCode(minPt, maxPt, quad.bottomRight.position);
        if (!(code3 & code0) || !(code3 & code1) || !(code3 & code2))
        {
            return true;
        }

        return false;
    }

    void BatchMoviewRender::quickVisit2(MovieClip* node, int level)
    {
        _matrixStack.push(_matrixStack.top() * node->nodeToParentTransform(_cacheInfo.movieScale));
        CLOVER_SCOPE_EXIT
        {
            _matrixStack.pop();
        };

        if (node->isTree())
        {
            if (_blurClipLevel == level)
            {
                auto bounds = node->getBounds();
                bounds.inset(-4, -4);
                bounds *= _cacheInfo.movieScale;
                gles::Quad quad;
                transformQuadToBatch(_matrixStack.top(),
                                     Point(bounds.x, bounds.y),
                                     cocos2d_bridge::Size(bounds.width, bounds.height),
                                     &quad);
                if (!s_isQuadInside(_clipRect.minPoint, _clipRect.maxPoint, quad))
                {
                    return;
                }
            }

            for (auto& child : node->_tree.subMovieClips)
            {
                innerVisit(child, level + 1);
            }
        }
        else
        {
            if (!genSpriteIfNeed(node, _cacheStrategy, _cacheInfo))
            {
                return;
            }

            auto texture2d = node->_leaf.sprite->getTexture();
            if (_texture2d != texture2d)
            {
                flush();
            }

            _texture2d = texture2d;
            pushQuad(node, level);
        }
    }

    void BatchMoviewRender::quickVisit(MovieClip* node, int level)
    {
        auto moviePart = node->_moviePart;
        if (moviePart && moviePart->isHidden())
        {
            return;
        }

        if (moviePart && moviePart->isChangeDefintion())
        {
            auto root = _cacheInfo.root;
            _cacheInfo.root = FlaDefinition(node->getDefinition().get());
            quickVisit2(node, level);
            _cacheInfo.root = root;
        }
        else
        {
            quickVisit2(node, level);
        }
    }

    void BatchMoviewRender::setClipEnable(bool clipEnabled, int blurClipLevel, const Rect& clipRect)
    {
        _clipEnabled = clipEnabled;
        _blurClipLevel = blurClipLevel;
        if (_clipEnabled)
        {
            _clipRect.minPoint.x = clipRect.x;
            _clipRect.minPoint.y = clipRect.y;
            _clipRect.maxPoint.x = clipRect.x + clipRect.width;
            _clipRect.maxPoint.y = clipRect.y + clipRect.height;
        }
        else
        {
            _blurClipLevel = -1;
        }
    }

    static cocos2d_bridge::Point s_makeVec(const gles::CoordPoint& pt)
    {
        return cocos2d_bridge::Point(pt.x, pt.y);
    }

    void BatchMoviewRender::drawQuadFrame(const gles::Quad& quad)
    {
        std::vector<cocos2d_bridge::Point> pts;
        pts.push_back(s_makeVec(quad.topLeft.position));
        pts.push_back(s_makeVec(quad.topRight.position));
        pts.push_back(s_makeVec(quad.bottomRight.position));
        pts.push_back(s_makeVec(quad.bottomLeft.position));
        DrawPrimitives::drawPoly(&pts[0], (unsigned int)pts.size(), true);
        _glProgram->use();
        _glProgram->setUniformsForBuiltins();
        cocos2d_bridge::GLEnableVertexAttribs(cocos2d_bridge::kVertexAttribFlag_Position |
                                              cocos2d_bridge::kVertexAttribFlag_TexCoords);
        _isBlendModeDirty = true;
        _isColorTransformDirty = true;
    }

    void BatchMoviewRender::pushQuad(MovieClip* node, int level)
    {
        assert(node && node->_leaf.sprite);
        auto& sprite = node->_leaf.sprite;
        gles::Quad quad = sprite->getQuad();
        auto offset = node->getLeafTranslatePoint(_cacheInfo.movieScale);
        transformQuadToBatch(_matrixStack.top(), offset, sprite->getFrameSize(), &quad);
        if (!_clipEnabled || s_isQuadInside(_clipRect.minPoint, _clipRect.maxPoint, quad))
        {
            if (node->getDefinition()->isFixHscreen())
            {
                quad.topLeft.position.x = quad.bottomLeft.position.x = _clipRect.minPoint.x;
                quad.topRight.position.x = quad.bottomRight.position.x = _clipRect.maxPoint.x;
            }
            _quads.push_back(quad);
        }
    }

    void BatchMoviewRender::setupColorTransform(const ColorTransform& colorTrans)
    {
        assert(_glProgram);
        _glProgram->setColorTransform(&colorTrans.rMult, &colorTrans.rAdd);
    }

    void BatchMoviewRender::setupBlendMode(BlendMode blendMode)
    {
        _glProgram->setBlendMode((GLuint)blendMode);

        switch (blendMode)
        {
            case BlendMode::Invert:
                glBlendEquation(GL_FUNC_ADD);
                cocos2d_bridge::GLBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
                break;

            case BlendMode::Multiply:
                glBlendEquation(GL_FUNC_ADD);
                cocos2d_bridge::GLBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
                break;

            case BlendMode::Screen:
                glBlendEquation(GL_FUNC_ADD);
                cocos2d_bridge::GLBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
                break;

            case BlendMode::Add:
                glBlendEquation(GL_FUNC_ADD);
                cocos2d_bridge::GLBlendFunc(GL_ONE, GL_ONE);
                break;

            case BlendMode::Lighten:
                glBlendEquation(0x8008);  // GL_MAX
                cocos2d_bridge::GLBlendFunc(GL_ONE, GL_ONE);
                break;

            case BlendMode::Darken:
                glBlendEquation(0x8007);  // GL_MIN
                cocos2d_bridge::GLBlendFunc(GL_ONE, GL_ONE);
                break;

            case BlendMode::Subtract:
                glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
                cocos2d_bridge::GLBlendFunc(GL_ONE, GL_ONE);
                break;

            case BlendMode::Alpha:
            case BlendMode::Erase:
                glBlendEquation(GL_FUNC_ADD);
                cocos2d_bridge::GLBlendFunc(GL_ZERO, GL_ONE);
                break;

            default:
                glBlendEquation(GL_FUNC_ADD);
                cocos2d_bridge::GLBlendFunc(_defaultBlendFunc.src, _defaultBlendFunc.dst);
                break;
        }
    }

    void BatchMoviewRender::flushQuads()
    {
        assert(!_quads.empty() && _texture2d);
        cocos2d_bridge::GLBindTexture2D(_texture2d->getName());

        GLushort* indices = getTriangleIndices(_quads.size());

        long offset = (long)&_quads[0];
        const size_t kQuadSize = sizeof(_quads[0].bottomLeft);

        // vertex
        int diff = offsetof(gles::Coord, position);
        glVertexAttribPointer(cocos2d_bridge::kVertexAttrib_Position,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              kQuadSize,
                              (void*)(offset + diff));

        // texCoods
        diff = offsetof(gles::Coord, texCoords);
        glVertexAttribPointer(cocos2d_bridge::kVertexAttrib_TexCoords,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              kQuadSize,
                              (void*)(offset + diff));

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(6 * _quads.size()), GL_UNSIGNED_SHORT, indices);
    }

    void BatchMoviewRender::flush()
    {
        if (_isColorTransformDirty)
        {
            setupColorTransform(_colorStack.top());
            _isColorTransformDirty = false;
        }

        if (_isBlendModeDirty)
        {
            setupBlendMode(_blendModeStack.top());
            _isBlendModeDirty = false;
        }

        if (!_quads.empty() && _texture2d)
        {
            flushQuads();
        }

        _quads.clear();
        _texture2d = nullptr;
    }
}
