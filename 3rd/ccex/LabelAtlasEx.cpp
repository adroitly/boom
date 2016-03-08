/*
 The MIT License (MIT)

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include "LabelAtlasEx.h"

namespace ccex
{
    LabelAtlasEx* LabelAtlasEx::createWithString(const std::string& string,
                                                 Texture2D* texture,
                                                 int xSpace,
                                                 int tileWidth,
                                                 int tileHeight,
                                                 int startCharMap)
    {
        LabelAtlasEx* label = new LabelAtlasEx();
        if (label->initWithString(string, texture, xSpace, tileWidth, tileHeight, startCharMap))
        {
            label->autorelease();
        }
        else
        {
            delete label;
            label = NULL;
        }
        return label;
    }

    LabelAtlasEx::LabelAtlasEx()
    {
    }

    bool LabelAtlasEx::initWithString(const std::string& string,
                                      Texture2D* texture,
                                      int xSpace,
                                      int tileWidth,
                                      int tileHeight,
                                      int startCharMap)
    {
        if (AtlasNode::initWithTexture(texture, tileWidth, tileHeight, (int)string.size()))
        {
            _xSpace = xSpace;
            _mapStartChar = startCharMap;
            this->setString(string);
            return true;
        }
        return false;
    }

    void LabelAtlasEx::setString(const std::string& label)
    {
        unsigned int len = (unsigned int)label.size();
        if (len > _textureAtlas->getTotalQuads())
        {
            _textureAtlas->resizeCapacity(len);
        }
        _string.clear();
        _string = label;
        this->updateAtlasValues();

        cocos2d::Size s(len * _xSpace, _itemHeight);
        this->setContentSize(s);
        _quadsToDraw = len;
    }

    const std::string& LabelAtlasEx::getString() const
    {
        return _string;
    }

    void LabelAtlasEx::updateAtlasValues()
    {
        unsigned int n = (unsigned int)_string.length();

        V3F_C4B_T2F_Quad quad;
        auto pTextureAtlas = _textureAtlas;
        auto itemWidth = _itemWidth;
        auto itemHeight = _itemHeight;
        auto itemsPerRow = _itemsPerRow;

        const unsigned char* s = (unsigned char*)_string.c_str();

        auto texture = pTextureAtlas->getTexture();
        float textureWide = (float)texture->getPixelsWide();
        float textureHigh = (float)texture->getPixelsHigh();
        float itemWidthInPixels = itemWidth * CC_CONTENT_SCALE_FACTOR();
        float itemHeightInPixels = itemHeight * CC_CONTENT_SCALE_FACTOR();

        for (unsigned int i = 0; i < n; i++)
        {
            unsigned char a = s[i] - _mapStartChar;
            float row = (float)(a % itemsPerRow);
            float col = (float)(a / itemsPerRow);

#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
            // Issue #938. Don't use texStepX & texStepY
            float left = (2 * row * itemWidthInPixels + 1) / (2 * textureWide);
            float right = left + (itemWidthInPixels * 2 - 2) / (2 * textureWide);
            float top = (2 * col * itemHeightInPixels + 1) / (2 * textureHigh);
            float bottom = top + (itemHeightInPixels * 2 - 2) / (2 * textureHigh);
#else
            float left = row * itemWidthInPixels / textureWide;
            float right = left + itemWidthInPixels / textureWide;
            float top = col * itemHeightInPixels / textureHigh;
            float bottom = top + itemHeightInPixels / textureHigh;
#endif  // ! CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

            quad.tl.texCoords.u = left;
            quad.tl.texCoords.v = top;
            quad.tr.texCoords.u = right;
            quad.tr.texCoords.v = top;
            quad.bl.texCoords.u = left;
            quad.bl.texCoords.v = bottom;
            quad.br.texCoords.u = right;
            quad.br.texCoords.v = bottom;

            quad.bl.vertices.x = (float)(i * _xSpace);
            quad.bl.vertices.y = 0;
            quad.bl.vertices.z = 0.0f;
            quad.br.vertices.x = (float)(i * _xSpace + itemWidth);
            quad.br.vertices.y = 0;
            quad.br.vertices.z = 0.0f;
            quad.tl.vertices.x = (float)(i * _xSpace);
            quad.tl.vertices.y = (float)(itemHeight);
            quad.tl.vertices.z = 0.0f;
            quad.tr.vertices.x = (float)(i * _xSpace + itemWidth);
            quad.tr.vertices.y = (float)(itemHeight);
            quad.tr.vertices.z = 0.0f;

            Color4B c = { _displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity };
            quad.tl.colors = c;
            quad.tr.colors = c;
            quad.bl.colors = c;
            quad.br.colors = c;
            pTextureAtlas->updateQuad(&quad, i);
        }
    }

    void LabelAtlasEx::updateColor()
    {
        if (_textureAtlas)
        {
            Color4B color4(_displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity);
            if (_isOpacityModifyRGB)
            {
                color4.r *= _displayedOpacity / 255.0f;
                color4.g *= _displayedOpacity / 255.0f;
                color4.b *= _displayedOpacity / 255.0f;
            }
            auto quads = _textureAtlas->getQuads();
            ssize_t length = _string.length();
            for (int index = 0; index < length; index++)
            {
                quads[index].bl.colors = color4;
                quads[index].br.colors = color4;
                quads[index].tl.colors = color4;
                quads[index].tr.colors = color4;
                _textureAtlas->updateQuad(&quads[index], index);
            }
        }
    }
}
