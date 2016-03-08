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

#ifndef __RBP_TEXTUREBIN_H__
#define __RBP_TEXTUREBIN_H__

#include "rbp_PackItem.h"

namespace rbp
{
    class TextureBin : public Ref<TextureBin>
    {
    public:
        static Ptr create(const rbp::RectSize& size);
        TextureBin(const rbp::RectSize& size);

        void addPackItem(const PackItem::Ptr& item);

        const rbp::RectSize& getSize() const
        {
            return _size;
        }

        const std::vector<PackItem::Ptr>& getItems() const
        {
            return _items;
        }

        void restorePackRects(const rbp::Rect* rts, size_t size);
        void minimizeBinSize();
        int computeMinimizeHeight() const;

    private:
        std::vector<PackItem::Ptr> _items;
        rbp::RectSize _size;
    };
}

#endif
