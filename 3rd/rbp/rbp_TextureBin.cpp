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

#include "rbp_TextureBin.h"

namespace rbp
{
    TextureBin::Ptr TextureBin::create(const rbp::RectSize& size)
    {
        return makeRef<TextureBin>(size);
    }
    
    TextureBin::TextureBin(const rbp::RectSize& size)
    {
        _size = size;
    }
    
    void TextureBin::addPackItem(const PackItem::Ptr& item)
    {
        _items.push_back(item);
    }
    
    void TextureBin::restorePackRects(const rbp::Rect* rts, size_t size)
    {
        auto minSize = std::min(size, _items.size());
        for (size_t i = 0; i < minSize; i++)
        {
            _items[i]->setPackRect(rts[i]);
        }
    }
    
    int TextureBin::computeMinimizeHeight() const
    {
        auto height = 0;
        for (auto& item : _items)
        {
            auto& rect = item->getPackRect();
            height = std::max(height, rect.y + rect.height);
        }
        return height;
    }
    
    void TextureBin::minimizeBinSize()
    {
        _size.height = computeMinimizeHeight();
    }
}