//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_BINPARSESHAPE__
#define __FLA_BINPARSESHAPE__

#include "../shape/fla_EdgeList.h"
#include "fla_BinEdgeWriterReader.h"
#include "../shape/fla_Path.h"
#include "../shape/fla_LineStyle.h"
#include "../shape/fla_FillStyle.h"
#include "../shape/fla_Shape.h"

namespace fla
{
    void readEdgeList(const uint8_t*& ptr, EdgeList& edgeList);

    void parsePaths(std::vector<fla::MorphPath>& paths, const uint8_t*& ptr);
    void parsePaths(std::vector<fla::Path>& paths, const uint8_t*& ptr);

    template <int N>
    LineStyleBase<N> parseLineStyle(const uint8_t*& ptr)
    {
        LineStyleBase<N> style;
        style.width = bin::readFloat<N>(ptr);
        style.color = bin::readColor<N>(ptr);

        uint8_t flags = bin::readUI8(ptr);
        if (flags & bin::LineStyleFlag_OnlyWidthAndColor)
        {
            style.onlyWidthAndColor = true;
        }
        else
        {
            style.onlyWidthAndColor = false;
        }

        if (!style.onlyWidthAndColor)
        {
            style.startCapStyle = static_cast<LineCapStyle>(bin::readUI8(ptr));
            style.endCapStyle = static_cast<LineCapStyle>(bin::readUI8(ptr));
            style.jointStyle = static_cast<LineJoinStyle>(bin::readUI8(ptr));
            style.miterLimitFactor = bin::readFloat(ptr);
        }
        return style;
    }

    template <int N>
    FillStyleBase<N> parseFillStyle(const uint8_t*& ptr)
    {
        FillStyleBase<N> style;
        style.setFillType((FillType)bin::readUI8(ptr));

        if (style.isSolidStyle())
        {
            auto solid = RcWrapObj<typename FillStyleBase<N>::SolidData>::create();
            solid->val = bin::readColor<N>(ptr);
            style.setFillData(solid);
        }

        else if (style.isGradientStyle())
        {
            auto data = RcWrapObj<typename FillStyleBase<N>::GradientData>::create();
            style.setFillData(data);

            auto& gradient = data->val;
            Holder<Matrix, N> matrix;
            bin::readMatrix(ptr, matrix);
            gradient.setMatrix(matrix);

            if (style.fillType() == FillType::FocalRadialGradient)
            {
                gradient.setFocalPoint(bin::readFloat<N>(ptr));
            }

            size_t count = bin::readUI16(ptr);
            for (size_t i = 0; i < count; i++)
            {
                auto color = bin::readColor<N>(ptr);
                auto loc = bin::readUI8<N>(ptr) / 255.0;
                gradient.addRecord(color, loc);
            }
        }

        else if (style.isBitmapStyle())
        {
            auto bitmap = RcWrapObj<typename FillStyleBase<N>::BitmapData>::create();
            bin::readMatrix(ptr, bitmap->val.matrix);
            bitmap->val.bitmapId = bin::readUI16(ptr);
            style.setFillData(bitmap);
        }

        return style;
    }

    template <int N>
    void parseSingleShape(ShapeBase<N>& shape, const uint8_t*& ptr)
    {
        size_t count = bin::readUI16(ptr);
        for (size_t i = 0; i < count; i++)
        {
            shape.lineStyles.push_back(parseLineStyle<N>(ptr));
        }

        count = bin::readUI16(ptr);
        for (size_t i = 0; i < count; i++)
        {
            shape.fillStyles.push_back(parseFillStyle<N>(ptr));
        }

        parsePaths(shape.paths, ptr);
    }
}

#endif
