//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_BinData.h"
#include <algorithm>
#include <limits>
#include <stdlib.h>
#include "fla_Codec.h"

namespace fla
{
    namespace bin
    {
        void writeMatrix(Data& data, const Holder<Matrix, 2>& matrix, float scale)
        {
            BinDataCoder_v1 coder;
            coder.writeMatrix(data, matrix.start, scale);
            coder.writeMatrix(data, matrix.end, scale);
        }

        void readMatrix(const uint8_t*& ptr, Holder<Matrix, 2>& matrix)
        {
            BinDataEncoder_v1 encoder;
            matrix.start = encoder.readMatrix(ptr);
            matrix.end = encoder.readMatrix(ptr);
        }

        void writeMatrix(Data& data, const Matrix& trans, float scale)
        {
            BinDataCoder_v1 coder;
            coder.writeMatrix(data, trans, scale);
        }

        Matrix readMatrix(const uint8_t*& ptr)
        {
            BinDataEncoder_v1 encoder;
            return encoder.readMatrix(ptr);
        }

        size_t readUI16Or32(const uint8_t*& ptr)
        {
            size_t size = bin::readUI16(ptr);
            if (size & 0x01)
            {
                ptr -= 2;
                size = bin::readUI32(ptr);
                size = size >> 1;
            }
            else
            {
                size = size >> 1;
            }
            return size;
        }

        void writeUI16Or32(bin::Data& data, size_t pathSize)
        {
            // size 有可能是十六位或者32位
            if (pathSize < (1 << 15))
            {
                uint16_t size = (pathSize << 1);
                bin::writeUI16(data, size);
            }
            else
            {
                uint32_t size = (uint32_t)(pathSize << 1) | 0x01;
                bin::writeUI32(data, size);
            }
        }
    }

    namespace bin
    {
        template <>
        Holder<uint8_t, 2> readUI8(const uint8_t*& ptr)
        {
            Holder<uint8_t, 2> result;
            result.start = readUI8(ptr);
            result.end = readUI8(ptr);
            return result;
        }

        template <>
        Holder<float, 2> readFloat(const uint8_t*& ptr)
        {
            Holder<float, 2> result;
            result.start = readFloat(ptr);
            result.end = readFloat(ptr);
            return result;
        }

        template <>
        Holder<Color4, 2> readColor(const uint8_t*& ptr)
        {
            Holder<Color4, 2> result;
            result.start = readColor(ptr);
            result.end = readColor(ptr);
            return result;
        }
    }
}
