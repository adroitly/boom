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

#include "rbp_TexturePacker.h"
#include "rbp_MaxRectsBinPack.h"
#include <algorithm>

namespace rbp
{
    static rbp::RectSize s_computeMaxItemSize(const std::vector<PackItem::Ptr>& items)
    {
        rbp::RectSize maxItemSize = { 0, 0 };
        for (auto& item : items)
        {
            maxItemSize.width = std::max(maxItemSize.width, item->getBounds().width);
            maxItemSize.height = std::max(maxItemSize.height, item->getBounds().height);
        }
        return maxItemSize;
    }

    static void s_sortPackItems(std::vector<PackItem::Ptr>& packItems)
    {
        std::sort(packItems.begin(),
                  packItems.end(),
                  [](const PackItem::Ptr& lhs, const PackItem::Ptr& rhs)
                  {
                      return lhs->getArea() < rhs->getArea();
                  });
    }

    static rbp::RectSize s_cropBinSize(const rbp::RectSize& size)
    {
        auto binSize = size;
        if (binSize.width >= binSize.height)
        {
            binSize.width >>= 1;
        }
        else
        {
            binSize.height >>= 1;
        }
        return binSize;
    }

    static bool s_innerPackItems(const std::vector<PackItem::Ptr>& packItems,
                                 const rbp::RectSize& binSize,
                                 std::vector<TextureBin::Ptr>& bins)
    {
        auto bin = TextureBin::create(binSize);

        rbp::MaxRectsBinPack maxRectPack;
        maxRectPack.init(binSize.width, binSize.height);

        std::vector<rbp::Rect> packRects(packItems.size());
        for (size_t i = 0; i < packItems.size(); i++)
        {
            auto item = packItems[i];
            auto packRt = maxRectPack.insert(item->getBounds().width, item->getBounds().height);

            if (packRt.width == 0 && packRt.height == 0)
            {
                if (bin->getItems().empty())
                {
                    return false;
                }
                bins.push_back(bin);
                bin = TextureBin::create(binSize);
                maxRectPack.init(binSize.width, binSize.height);
                i--;
            }
            else
            {
                packRects[i] = packRt;
                bin->addPackItem(item);
            }
        }

        for (size_t i = 0; i < packItems.size(); i++)
        {
            packItems[i]->setPackRect(packRects[i]);
        }
        assert(!bin->getItems().empty());
        bins.push_back(bin);
        return true;
    }

    TexturePacker::TexturePacker(CalTextureFun calTextureSize)
    {
        _calTextureSize = calTextureSize;
        _shouldCropLastBin = true;
    }

    size_t TexturePacker::numOfItems() const
    {
        size_t numberOfItems = 0;
        for (auto& bin : _bins)
        {
            numberOfItems += bin->getItems().size();
        }
        return numberOfItems;
    }

    const std::vector<TextureBin::Ptr>& TexturePacker::getBins() const
    {
        return _bins;
    }

    bool TexturePacker::packItems(std::vector<PackItem::Ptr>& packItems)
    {
        if (packItems.empty())
        {
            return false;
        }

        auto maxItemSize = s_computeMaxItemSize(packItems);
        rbp::RectSize binSize = _calTextureSize(maxItemSize);

        _bins.clear();
        s_sortPackItems(packItems);
        if (s_innerPackItems(packItems, binSize, _bins))
        {
            if (_shouldCropLastBin)
            {
                cropLastBin();
            }
            assert(numOfItems() == packItems.size());
            return true;
        }
        return false;
    }

    void TexturePacker::setShouldCropLastBin(bool flag)
    {
        _shouldCropLastBin = flag;
    }

    void TexturePacker::minimizeBinSize()
    {
        for (auto& bin : _bins)
        {
            bin->minimizeBinSize();
        }
    }

    void TexturePacker::cropLastBin()
    {
        if (_bins.empty())
        {
            return;
        }

        auto lastBin = _bins.back();
        if (lastBin->getItems().empty())
        {
            return;
        }

        auto minimizeHeight = lastBin->computeMinimizeHeight();
        auto binSize = lastBin->getSize();
        auto cropBinSize = binSize;

        while (minimizeHeight * 2 <= binSize.height)
        {
            cropBinSize = s_cropBinSize(cropBinSize);
            minimizeHeight *= 2;
        }

        // 不能再装下了，直接返回
        if (binSize.width == cropBinSize.width && binSize.height == cropBinSize.height)
        {
            return;
        }

        std::vector<TextureBin::Ptr> tryBins;
        if (s_innerPackItems(lastBin->getItems(), cropBinSize, tryBins))
        {
            _bins.pop_back();
            _bins.insert(_bins.end(), tryBins.begin(), tryBins.end());
            this->cropLastBin();
        }
    }
}