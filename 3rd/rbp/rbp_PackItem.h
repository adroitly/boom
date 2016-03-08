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

#ifndef __RBP_PACKITEM_H__
#define __RBP_PACKITEM_H__

#include "rbp_Rect.h"
#include "rbp_Ref.h"

namespace rbp
{
    class PackItem : public Ref<PackItem>
    {
    public:
        PackItem(const Rect& bounds) : _bounds(bounds)
        {
        }

        PackItem()
        {
        }

        virtual ~PackItem()
        {
        }

        const Rect& getBounds() const
        {
            return _bounds;
        }

        void setBounds(const Rect& bounds)
        {
            _bounds = bounds;
        }

        const Rect& getPackRect() const
        {
            return _packRect;
        }

        void setPackRect(const Rect& packRect)
        {
            _packRect = packRect;
        }

        bool isRotation() const
        {
            return _packRect.width != _bounds.width;
        }

        // 计算面积
        size_t getArea() const
        {
            return _bounds.width * _bounds.height;
        }

    private:
        Rect _bounds;
        Rect _packRect;
    };
}

#endif
