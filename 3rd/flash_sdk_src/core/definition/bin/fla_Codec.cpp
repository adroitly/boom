//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_Codec.h"
#include "fla_BinData.h"
#include "bit/bit_io.hpp"

namespace fla
{
    namespace bin
    {
        void BinDataCoder_v1::writeColorTransform(Data& data, const ColorTransform& trans)
        {
            uint8_t flags = 0;
            if (trans.isIdentity())
            {
                flags |= 0x01;
                writeUI8(data, flags);
                return;
            }

            auto saveLen = data.size();
            writeUI8(data, flags);

            if (trans.rMult != 1 || trans.rAdd != 0)
            {
                flags |= 0x02;
                writeFloat(data, trans.rMult);
                writeFloat(data, trans.rAdd);
            }

            if (trans.gMult != 1 || trans.gAdd != 0)
            {
                flags |= 0x04;
                writeFloat(data, trans.gMult);
                writeFloat(data, trans.gAdd);
            }

            if (trans.bMult != 1 || trans.bAdd != 0)
            {
                flags |= 0x08;
                writeFloat(data, trans.bMult);
                writeFloat(data, trans.bAdd);
            }

            if (trans.aMult != 1 || trans.aAdd != 0)
            {
                flags |= 0x10;
                writeFloat(data, trans.aMult);
                writeFloat(data, trans.aAdd);
            }

            data[saveLen] = flags;
        }

        void BinDataCoder_v1::writeMatrix(Data& data, const Matrix& trans, float scale)
        {
            real_t xscale, yscale, rotate0, rotate1, tx, ty;
            trans.get(xscale, rotate0, rotate1, yscale, tx, ty);

            uint8_t flags = 0;
            auto saveLen = data.size();
            writeUI8(data, flags);

            if (xscale != 1)
            {
                flags |= 0x01;  // xscale
                writeFloat(data, xscale);
            }

            if (yscale != 1)
            {
                flags |= 0x02;  // yscale
                writeFloat(data, yscale);
            }

            if (rotate0 != 0)
            {
                flags |= 0x04;  // rotate0
                writeFloat(data, rotate0);
            }

            if (rotate1 != 0)
            {
                flags |= 0x08;  // rotate1
                writeFloat(data, rotate1);
            }

            if (tx != 0)
            {
                flags |= 0x10;  // tx
                writeFloat(data, tx * scale);
            }

            if (ty != 0)
            {
                flags |= 0x20;  // ty;
                writeFloat(data, ty * scale);
            }
            data[saveLen] = flags;
        }

        ColorTransform BinDataEncoder_v1::readColorTransform(const uint8_t*& ptr)
        {
            real_t rMult = 1.0, gMult = 1.0, bMult = 1.0, aMult = 1.0;
            real_t rAdd = 0.0, gAdd = 0.0, bAdd = 0.0, aAdd = 0.0;

            uint8_t flags = readUI8(ptr);
            if (flags & 0x01)
            {
                return ColorTransform::identity();
            }

            if (flags & 0x02)
            {
                rMult = readFloat(ptr);
                rAdd = readFloat(ptr);
            }

            if (flags & 0x04)
            {
                gMult = readFloat(ptr);
                gAdd = readFloat(ptr);
            }

            if (flags & 0x08)
            {
                bMult = readFloat(ptr);
                bAdd = readFloat(ptr);
            }

            if (flags & 0x10)
            {
                aMult = readFloat(ptr);
                aAdd = readFloat(ptr);
            }

            return ColorTransform::make(rMult, gMult, bMult, aMult, rAdd, gAdd, bAdd, aAdd);
        }

        Matrix BinDataEncoder_v1::readMatrix(const uint8_t*& ptr)
        {
            real_t xscale = 1, yscale = 1;
            real_t rotate0 = 0, rotate1 = 0;
            real_t tx = 0, ty = 0;

            uint8_t flags = readUI8(ptr);

            if (flags & 0x01)
            {
                xscale = readFloat(ptr);
            }

            if (flags & 0x02)
            {
                yscale = readFloat(ptr);
            }

            if (flags & 0x04)
            {
                rotate0 = readFloat(ptr);
            }

            if (flags & 0x08)
            {
                rotate1 = readFloat(ptr);
            }

            if (flags & 0x10)
            {
                tx = readFloat(ptr);
            }

            if (flags & 0x20)
            {
                ty = readFloat(ptr);
            }

            return Matrix(xscale, rotate0, rotate1, yscale, tx, ty);
        }

        static uint32_t s_numberOfBits(uint32_t b)
        {
            uint32_t bits = 0;
            while (b > 0)
            {
                bits++;
                b >>= 1;
            }
            return bits;
        }

        static uint32_t s_calculateMaxBits(int32_t* values, size_t N)
        {
            uint32_t b = 0;
            int32_t vmax = std::numeric_limits<int32_t>::min();

            for (size_t i = 0; i < N; i++)
            {
                auto svalue = values[i];
                if (svalue >= 0)
                {
                    b |= svalue;
                }
                else
                {
                    b |= ~svalue << 1;
                }

                if (vmax < svalue)
                {
                    vmax = svalue;
                }
            }

            uint32_t bits = s_numberOfBits(b);
            if (vmax > 0 && s_numberOfBits(vmax) >= bits)
            {
                bits++;
            }
            return bits;
        }

        static uint32_t calculateMaxBits(int32_t v0, int32_t v1)
        {
            int32_t values[] = { v0, v1 };
            return s_calculateMaxBits(values, 2);
        }

        class BitWriter : public bit::BitWriter<BitWriter>
        {
        public:
            BitWriter(Data& data) : _data(data)
            {
            }

            ~BitWriter()
            {
            }

            void outputByte(uint8_t byte)
            {
                writeUI8(_data, byte);
            }

            void writeUB(uint32_t bits, uint32_t value)
            {
                writeBits(bits, value);
            }

            void writeSB(uint32_t bits, int32_t value)
            {
                writeBits(bits, value);
            }

            void writeFB(uint32_t bits, float value)
            {
                writeSB(bits, value * 65536);
            }

            void writeColorTrans(const ColorTransform& transform);
            void writeMatrix(const Matrix& trans);

        private:
            Data& _data;
        };

        void BitWriter::writeColorTrans(const ColorTransform& transform)
        {
            int32_t rMult = transform.rMult * 255;
            int32_t gMult = transform.gMult * 255;
            int32_t bMult = transform.bMult * 255;
            int32_t aMult = transform.aMult * 255;

            int32_t rAdd = transform.rAdd * 255;
            int32_t gAdd = transform.gAdd * 255;
            int32_t bAdd = transform.bAdd * 255;
            int32_t aAdd = transform.aAdd * 255;

            bool hasAddTerms = (rAdd != 0) || (gAdd != 0) || (bAdd != 0) || (aAdd != 0);
            bool hasMultTerms = (rMult != 255) || (gMult != 255) || (bMult != 255) || (aMult != 255);

            writeUB(1, hasAddTerms ? 1 : 0);
            writeUB(1, hasMultTerms ? 1 : 0);

            int32_t values[8];
            size_t N = 0;

            if (hasMultTerms)
            {
                values[N] = rMult;
                values[N + 1] = gMult;
                values[N + 2] = bMult;
                values[N + 3] = aMult;
                N += 4;
            }

            if (hasAddTerms)
            {
                values[N] = rAdd;
                values[N + 1] = gAdd;
                values[N + 2] = bAdd;
                values[N + 3] = aAdd;
                N += 4;
            }

            auto bits = s_calculateMaxBits(values, N);
            writeUB(4, bits);

            if (hasMultTerms)
            {
                writeSB(bits, rMult);
                writeSB(bits, gMult);
                writeSB(bits, bMult);
                writeSB(bits, aMult);
            }

            if (hasAddTerms)
            {
                writeSB(bits, rAdd);
                writeSB(bits, gAdd);
                writeSB(bits, bAdd);
                writeSB(bits, aAdd);
            }
        }

        void BitWriter::writeMatrix(const Matrix& trans)
        {
            real_t xscale, yscale, rotate0, rotate1, tx, ty;
            trans.get(xscale, rotate0, rotate1, yscale, tx, ty);

            tx *= 20.0;
            ty *= 20.0;

            bool hasScale = (xscale != 1) || (yscale != 1);
            bool hasRotate = (rotate0 != 0) || (rotate1 != 0);

            writeBits(1, hasScale ? 1 : 0);
            if (hasScale)
            {
                uint32_t scaleBits;
                if (xscale == 0 && yscale == 0)
                {
                    scaleBits = 1;
                }
                else
                {
                    scaleBits = calculateMaxBits(xscale * 65536, yscale * 65536);
                }
                writeUB(5, scaleBits);
                writeFB(scaleBits, xscale);
                writeFB(scaleBits, yscale);
            }

            writeBits(1, hasRotate ? 1 : 0);
            if (hasRotate)
            {
                uint32_t rotateBits = calculateMaxBits(rotate0 * 65536, rotate1 * 65536);
                writeUB(5, rotateBits);
                writeFB(rotateBits, rotate0);
                writeFB(rotateBits, rotate1);
            }

            uint32_t translateBits = calculateMaxBits(tx, ty);
            writeUB(5, translateBits);
            writeSB(translateBits, tx);
            writeSB(translateBits, ty);
        }

        // swf的原始格式用Twip作为单位，很多时候，用 真实数据*20，取整之后存放在二进制中
        // 这样就变成统一存放整数，整数容易压缩存储
        // 所以要取得真实数据，需要除以20
        template <typename T>
        inline real_t pixelFromTwip(T t)
        {
            return t / 20.0f;
        }

        class BitReader : public bit::BitReader<BitReader>
        {
        public:
            BitReader(const uint8_t*& ptr) : _curByte(ptr)
            {
            }

            uint8_t inputByte()
            {
                return *(_curByte++);
            }

            uint32_t readUB(uint32_t bits)
            {
                return readBits(bits);
            }

            // 按位读取，有符号
            int32_t readSB(uint32_t bits)
            {
                uint32_t shift = 32 - bits;
                return int32_t(readBits(bits) << shift) >> shift;
            }

            // 按位读取一个浮点数
            float readFB(uint32_t bits)
            {
                return (float)(readSB(bits)) / 65536.0f;
            }

            Matrix readMatrix();
            ColorTransform readTransform();

        private:
            const uint8_t*& _curByte;  // 当期读取的字节位置
        };

        Matrix BitReader::readMatrix()
        {
            Matrix matrix;
            // scale
            if (readUB(1) == 1)
            {
                uint32_t bits = readUB(5);
                matrix.a = readFB(bits);
                matrix.d = readFB(bits);
            }

            // rotate
            if (readUB(1) == 1)
            {
                uint32_t bits = readUB(5);
                matrix.b = readFB(bits);
                matrix.c = readFB(bits);
            }

            // translate
            {
                uint32_t bits = readUB(5);
                matrix.tx = pixelFromTwip(readSB(bits));
                matrix.ty = pixelFromTwip(readSB(bits));
            }

            return matrix;
        }

        ColorTransform BitReader::readTransform()
        {
            ColorTransform trans = ColorTransform::identity();

            bool hasAdd = (readUB(1) == 1);
            bool hasMult = (readUB(1) == 1);

            uint32_t bits = readUB(4);
            real_t factor = 1.0 / 255.0;
            if (hasMult)
            {
                trans.rMult = readSB(bits) * factor;
                trans.gMult = readSB(bits) * factor;
                trans.bMult = readSB(bits) * factor;
                trans.aMult = readSB(bits) * factor;
            }

            if (hasAdd)
            {
                trans.rAdd = readSB(bits) * factor;
                trans.gAdd = readSB(bits) * factor;
                trans.bAdd = readSB(bits) * factor;
                trans.aAdd = readSB(bits) * factor;
            }
            return trans;
        }

        void BinDataCoder_v2::writeColorTransform(Data& data, const ColorTransform& trans)
        {
            BitWriter writer(data);
            writer.writeColorTrans(trans);
        }

        void BinDataCoder_v2::writeMatrix(Data& data, const Matrix& trans, float scale)
        {
            auto tmpTrans = trans;
            tmpTrans.tx *= scale;
            tmpTrans.ty *= scale;

            BitWriter writer(data);
            writer.writeMatrix(tmpTrans);
        }

        ColorTransform BinDataEncoder_v2::readColorTransform(const uint8_t*& ptr)
        {
            BitReader reader(ptr);
            return reader.readTransform();
        }

        Matrix BinDataEncoder_v2::readMatrix(const uint8_t*& ptr)
        {
            BitReader reader(ptr);
            return reader.readMatrix();
        }
    }
}