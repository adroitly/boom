/*
 The MIT License (MIT)

 Copyright (c) 2015 HJC hjcapple@gmail.com

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

#ifndef __CCEX_LABELATLASEX_H__
#define __CCEX_LABELATLASEX_H__

#include "cocos2d.h"
#include <string>

namespace ccex
{
    using namespace cocos2d;
    class LabelAtlasEx : public AtlasNode, public LabelProtocol
    {
    public:
        LabelAtlasEx();

        static LabelAtlasEx* createWithString(const std::string& string,
                                              Texture2D* texture,
                                              int xSpace,
                                              int tileWidth,
                                              int tileHeight,
                                              int startCharMap);

        virtual void setString(const std::string& label) override;
        virtual const std::string& getString() const override;

    private:
        bool initWithString(const std::string& string,
                            Texture2D* texture,
                            int xSpace,
                            int tileWidth,
                            int tileHeight,
                            int startCharMap);

        virtual void updateAtlasValues() override;
        virtual void updateColor() override;

    private:
        std::string _string;
        int _xSpace;
        int _mapStartChar;
    };
}

#endif
