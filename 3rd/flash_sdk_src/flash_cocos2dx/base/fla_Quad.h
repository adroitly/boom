//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_QUAD_H__
#define __FLA_QUAD_H__

#include "cocos2d.h"

namespace fla
{
    namespace gles
    {
        // 平坦类型，避免生成构造和析构函数
        typedef struct
        {
            GLfloat x;
            GLfloat y;
        } CoordPoint;

        typedef struct
        {
            CoordPoint position;
            CoordPoint texCoords;
        } Coord;

        typedef struct
        {
            Coord topLeft;
            Coord bottomLeft;
            Coord topRight;
            Coord bottomRight;
        } Quad;

        inline CoordPoint coordPoint_make(float x, float y)
        {
            CoordPoint pt = { x, y };
            return pt;
        }

        struct Rect2 final
        {
            void flipX()
            {
                x = x + width;
                width = -width;
            }

            void flipY()
            {
                y = y + height;
                height = -height;
            }

            void rotate()
            {
                std::swap(width, height);
            }

            void normalized(GLfloat totalWidth, GLfloat totalHeight)
            {
                x /= totalWidth;
                y /= totalHeight;
                width /= totalWidth;
                height /= totalHeight;
            }

            CoordPoint topLeft() const
            {
                return coordPoint_make(x, y);
            }

            CoordPoint bottomLeft() const
            {
                return coordPoint_make(x, y + height);
            }

            CoordPoint topRight() const
            {
                return coordPoint_make(x + width, y);
            }

            CoordPoint bottomRight() const
            {
                return coordPoint_make(x + width, y + height);
            }

            GLfloat x;
            GLfloat y;
            GLfloat width;
            GLfloat height;
        };

        inline Rect2 MakeRect2(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
        {
            Rect2 rt = { x, y, width, height };
            return rt;
        }
    }
}

#endif
