//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_BINDATA_H__
#define __FLA_BINDATA_H__

#include <vector>
#include <string>
#include <cstdint>
#include "../../base/fla_Color4.h"
#include "../../base/fla_ColorTransform.h"
#include "../../utility/fla_Holder.h"

namespace fla
{
    namespace bin
    {
        typedef std::vector<uint8_t> Data;

        ////////////////////////////////////////////////////////////////
        // Data
        inline void writeData(Data& data, const Data& other)
        {
            data.insert(data.end(), other.begin(), other.end());
        }

        ////////////////////////////////////////////////////////////////
        // 字节
        // 这里隐含一个条件，数据格式一定为小尾顺序
        inline void writeBytes(Data& data, const uint8_t* bytes, size_t len)
        {
            data.insert(data.end(), bytes, bytes + len);
        }

        inline void readBytes(const uint8_t*& cur, uint8_t* bytes, size_t len)
        {
            memcpy(bytes, cur, len);
            cur += len;
        }

        ////////////////////////////////////////////////////////////////
        // 8位无符号整数
        inline void writeUI8(Data& data, uint8_t v)
        {
            writeBytes(data, &v, 1);
        }

        inline void writeUI8(Data& data, const Holder<uint8_t, 2>& value)
        {
            writeUI8(data, value.start);
            writeUI8(data, value.end);
        }

        inline uint8_t readUI8(const uint8_t*& ptr)
        {
            uint8_t v = *reinterpret_cast<const uint8_t*>(ptr);
            ptr += 1;
            return v;
        }

        ////////////////////////////////////////////////////////////////
        // 8位有符号整数
        inline void writeSI8(Data& data, int8_t v)
        {
            writeBytes(data, (uint8_t*)&v, 1);
        }

        inline int8_t readSI8(const uint8_t*& ptr)
        {
            int8_t v = *reinterpret_cast<const int8_t*>(ptr);
            ptr += 1;
            return v;
        }

        ////////////////////////////////////////////////////////////////
        // 16位无符号整数
        inline void writeUI16(Data& data, uint16_t v)
        {
            writeBytes(data, (uint8_t*)&v, 2);
        }

        inline uint16_t readUI16(const uint8_t*& ptr)
        {
            uint16_t v;
            readBytes(ptr, (uint8_t*)&v, 2);
            return v;
        }

        ////////////////////////////////////////////////////////////////
        // 16位有符号整数
        inline void writeSI16(Data& data, int16_t v)
        {
            writeBytes(data, (uint8_t*)&v, 2);
        }

        inline int16_t readSI16(const uint8_t*& ptr)
        {
            int16_t v;
            readBytes(ptr, (uint8_t*)&v, 2);
            return v;
        }

        ////////////////////////////////////////////////////////////////
        // 32位无符号整数
        inline void writeUI32(Data& data, uint32_t v)
        {
            writeBytes(data, (uint8_t*)&v, 4);
        }

        inline uint32_t readUI32(const uint8_t*& ptr)
        {
            uint32_t v;
            readBytes(ptr, (uint8_t*)&v, 4);
            return v;
        }

        ////////////////////////////////////////////////////////////////
        // 16 or 32
        size_t readUI16Or32(const uint8_t*& ptr);
        void writeUI16Or32(bin::Data& data, size_t pathSize);

        ////////////////////////////////////////////////////////////////
        // 浮点
        inline void writeFloat(Data& data, float v)
        {
            static_assert(sizeof(v) == 4, "");
            writeBytes(data, (uint8_t*)&v, 4);
        }

        inline void writeFloat(Data& data, Holder<float, 2> v)
        {
            writeFloat(data, v.start);
            writeFloat(data, v.end);
        }

        inline float readFloat(const uint8_t*& ptr)
        {
            static_assert(sizeof(float) == 4, "");
            float v;
            readBytes(ptr, (uint8_t*)&v, 4);
            return v;
        }

        ////////////////////////////////////////////////////////////////
        // Size
        inline void writeSize(Data& data, const Size& size, float scale)
        {
            writeFloat(data, size.width * scale);
            writeFloat(data, size.height * scale);
        }

        inline Size readSize(const uint8_t*& ptr)
        {
            float width = readFloat(ptr);
            float height = readFloat(ptr);
            return fla::Size(width, height);
        }

        inline void skipSize(const uint8_t*& ptr)
        {
            ptr += 4 * 2;
        }

        ////////////////////////////////////////////////////////////////
        // Point
        inline void writePoint(Data& data, const Point& pt, float scale)
        {
            writeFloat(data, pt.x * scale);
            writeFloat(data, pt.y * scale);
        }

        inline Point readPoint(const uint8_t*& ptr)
        {
            float x = readFloat(ptr);
            float y = readFloat(ptr);
            return Point(x, y);
        }

        ////////////////////////////////////////////////////////////////
        // Color
        inline void writeColor(Data& data, const Color4& color)
        {
            writeUI8(data, color.red * 255);
            writeUI8(data, color.green * 255);
            writeUI8(data, color.blue * 255);
            writeUI8(data, color.alpha * 255);
        }

        inline void writeColor(Data& data, const Holder<Color4, 2>& color)
        {
            writeColor(data, color.start);
            writeColor(data, color.end);
        }

        inline Color4 readColor(const uint8_t*& ptr)
        {
            Color4 color;
            color.red = readUI8(ptr) / 255.0;
            color.green = readUI8(ptr) / 255.0;
            color.blue = readUI8(ptr) / 255.0;
            color.alpha = readUI8(ptr) / 255.0;
            return color;
        }

        ////////////////////////////////////////////////////////////////
        // Rect
        inline void writeRect(Data& data, const Rect& rt, float scale)
        {
            writeFloat(data, rt.x * scale);
            writeFloat(data, rt.y * scale);
            writeFloat(data, rt.width * scale);
            writeFloat(data, rt.height * scale);
        }

        inline Rect readRect(const uint8_t*& ptr)
        {
            Rect rt;
            rt.x = readFloat(ptr);
            rt.y = readFloat(ptr);
            rt.width = readFloat(ptr);
            rt.height = readFloat(ptr);
            return rt;
        }

        inline void skipRect(const uint8_t*& ptr)
        {
            ptr += 4 * 4;
        }

        ////////////////////////////////////////////////////////////////
        // String
        inline void writeString(Data& data, const std::string& str)
        {
            for (auto c : str)
            {
                writeUI8(data, c);
            }
            writeUI8(data, 0);
        }

        inline std::string readString(const uint8_t*& ptr)
        {
            std::string buf;
            char c = 0;
            while ((c = *ptr++))
            {
                buf.push_back(c);
            }
            return buf;
        }

        inline void skipString(const uint8_t*& ptr)
        {
            char c = 0;
            while ((c = *ptr++))
            {
            }
        }

        ////////////////////////////////////////////////////////////////
        // Matrix
        Matrix readMatrix(const uint8_t*& ptr);

        void writeMatrix(Data& data, const Matrix& trans, float scale);
        void writeMatrix(Data& data, const Holder<Matrix, 2>& matrix, float scale);
    }

    namespace bin
    {
        template <int N>
        Holder<Color4, N> readColor(const uint8_t*& ptr)
        {
            return readColor(ptr);
        }

        template <>
        Holder<Color4, 2> readColor(const uint8_t*& ptr);

        template <int N>
        Holder<float, N> readFloat(const uint8_t*& ptr)
        {
            return readFloat(ptr);
        }

        template <>
        Holder<float, 2> readFloat(const uint8_t*& ptr);

        template <int N>
        Holder<uint8_t, N> readUI8(const uint8_t*& ptr)
        {
            return readUI8(ptr);
        }

        template <>
        Holder<uint8_t, 2> readUI8(const uint8_t*& ptr);

        inline void readMatrix(const uint8_t*& ptr, Holder<Matrix, 1>& matrix)
        {
            matrix = readMatrix(ptr);
        }

        void readMatrix(const uint8_t*& ptr, Holder<Matrix, 2>& matrix);
    }
}

#endif