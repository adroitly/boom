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

#ifndef __RBP_TEXTUREPACKER_H__
#define __RBP_TEXTUREPACKER_H__

#include "rbp_PackItem.h"
#include "rbp_TextureBin.h"
#include <functional>
#include <boost/noncopyable.hpp>

namespace rbp
{
    class TexturePacker : boost::noncopyable
    {
    public:
        typedef std::function<rbp::RectSize(const rbp::RectSize&)> CalTextureFun;
        TexturePacker(CalTextureFun calTextureSize);

        bool packItems(std::vector<PackItem::Ptr>& packItems);
        const std::vector<TextureBin::Ptr>& getBins() const;

        void setShouldCropLastBin(bool flag);
        void minimizeBinSize();

    private:
        void cropLastBin();
        size_t numOfItems() const;

    private:
        std::vector<TextureBin::Ptr> _bins;
        CalTextureFun _calTextureSize;
        bool _shouldCropLastBin;
    };
}

#endif
