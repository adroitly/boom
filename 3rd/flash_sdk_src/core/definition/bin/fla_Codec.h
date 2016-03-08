//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_CODEC_H__
#define __FLA_CODEC_H__

#include <map>
#include <vector>
#include <cstdint>
#include "../../base/fla_ColorTransform.h"
#include "../../utility/fla_Holder.h"

namespace fla
{
    namespace bin
    {
        typedef std::vector<uint8_t> Data;
        class BinDataCoder
        {
        public:
            ~BinDataCoder()
            {
            }

            virtual void writeColorTransform(Data& data, const ColorTransform& trans) = 0;
            virtual void writeMatrix(Data& data, const Matrix& matrix, float scale) = 0;
        };

        class BinDataEncoder
        {
        public:
            ~BinDataEncoder()
            {
            }

            virtual ColorTransform readColorTransform(const uint8_t*& ptr) = 0;
            virtual Matrix readMatrix(const uint8_t*& ptr) = 0;
        };

        class BinDataCoder_v1 : public BinDataCoder
        {
        public:
            virtual void writeColorTransform(Data& data, const ColorTransform& trans) override;
            virtual void writeMatrix(Data& data, const Matrix& matrix, float scale) override;
        };

        class BinDataEncoder_v1 : public BinDataEncoder
        {
        public:
            virtual ColorTransform readColorTransform(const uint8_t*& ptr) override;
            virtual Matrix readMatrix(const uint8_t*& ptr) override;
        };

        class BinDataCoder_v2 : public BinDataCoder
        {
        public:
            virtual void writeColorTransform(Data& data, const ColorTransform& trans) override;
            virtual void writeMatrix(Data& data, const Matrix& matrix, float scale) override;
        };

        class BinDataEncoder_v2 : public BinDataEncoder
        {
        public:
            virtual ColorTransform readColorTransform(const uint8_t*& ptr) override;
            virtual Matrix readMatrix(const uint8_t*& ptr) override;
        };
    }
}

#endif
