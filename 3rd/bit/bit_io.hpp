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

#ifndef __BIT_IO_H__
#define __BIT_IO_H__

#include <assert.h>
#include <limits>

namespace bit
{
    template <typename DerivedT>
    class BitWriter
    {
    public:
        BitWriter()
        {
            _bitsPending = 0;
            _rack = 0;
        }

        ~BitWriter()
        {
            if (_bitsPending != 0)
            {
                flush();
            }
        }

        void writeBits(size_t bit_count, uint32_t value);

    private:
        void flush()
        {
            static_cast<DerivedT*>(this)->outputByte(_rack);
            _rack = 0;
            _bitsPending = 0;
        }

    private:
        size_t _bitsPending;
        uint8_t _rack;
    };

    template <typename DerivedT>
    void BitWriter<DerivedT>::writeBits(size_t bit_count, uint32_t value)
    {
        while (bit_count != 0)
        {
            value &= (0xffffffff >> (32 - bit_count));
            if (_bitsPending > 0)
            {
                if (_bitsPending > bit_count)
                {
                    _bitsPending -= bit_count;
                    bit_count = 0;
                    _rack |= value << _bitsPending;
                }
                else if (_bitsPending < bit_count)
                {
                    bit_count -= _bitsPending;
                    _rack |= value >> bit_count;
                    flush();
                }
                else
                {
                    assert(_bitsPending == bit_count);
                    bit_count = 0;
                    _rack |= value;
                    flush();
                }
            }
            else
            {
                assert(_bitsPending == 0);
                if (bit_count < 8)
                {
                    _bitsPending = 8 - bit_count;
                    bit_count = 0;
                    _rack = value << _bitsPending;
                }
                else
                {
                    bit_count -= 8;
                    _rack = value >> bit_count;
                    flush();
                }
            }
        }
    }

    template <typename DerivedT>
    class BitReader
    {
    public:
        BitReader()
        {
            _bitsPending = 0;
            _rack = 0;
        }

        uint32_t readBits(size_t bits);

    private:
        size_t _bitsPending;  // 当前字节的位位置
        uint8_t _rack;
    };

    template <typename DerivedT>
    uint32_t BitReader<DerivedT>::readBits(size_t bit_count)
    {
        uint32_t result = 0;
        while (bit_count != 0)
        {
            if (_bitsPending == 0)
            {
                _rack = static_cast<DerivedT*>(this)->inputByte();
                _bitsPending = 8;
            }

            uint32_t byte = _rack & (0xff >> (8 - _bitsPending));

            if (_bitsPending < bit_count)
            {
                result = (result << _bitsPending) | byte;
                bit_count -= _bitsPending;
                _bitsPending = 0;
            }
            else
            {
                assert(bit_count <= _bitsPending);
                _bitsPending -= bit_count;
                result = (result << bit_count) | (byte >> _bitsPending);
                bit_count = 0;
            }
        }
        return result;
    }
}

#endif
