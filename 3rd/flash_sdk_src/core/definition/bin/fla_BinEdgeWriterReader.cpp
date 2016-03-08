//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_BinEdgeWriterReader.h"
#include <limits>

namespace fla
{
    namespace bin
    {
        // 判断一个整数最起码可以用多数字节表示
        // 返回1表示1字节，2表示2字节，3表示四字节
        static int numberOfBytes(int32_t value)
        {
            int32_t min = std::numeric_limits<int8_t>::min();
            int32_t max = std::numeric_limits<int8_t>::max();

            if (min < value && value < max)
            {
                return 1;
            }

            min = std::numeric_limits<int16_t>::min();
            max = std::numeric_limits<int16_t>::max();
            if (min < value && value < max)
            {
                return 2;
            }

            return 3;
        }

        static int numberOfBytes(int32_t v0, int32_t v1)
        {
            return std::max(numberOfBytes(v0), numberOfBytes(v1));
        }

        static int numberOfBytes(int32_t v0, int32_t v1, int32_t v2, int32_t v3)
        {
            return std::max(numberOfBytes(v0, v1), numberOfBytes(v2, v3));
        }

        void EdgeWriterReader::writeOffset(Data& data,
                                           const Offset& offset,
                                           const Point& pt,
                                           const FlagsInfo& flags)
        {
            if (flags.numOfBytes == 0)
            {
                writePoint(data, pt, _scale);
            }
            else if (flags.numOfBytes == 1)
            {
                if (offset.x)
                {
                    writeSI8(data, offset.x);
                }
                if (offset.y)
                {
                    writeSI8(data, offset.y);
                }
            }
            else if (flags.numOfBytes == 2)
            {
                if (offset.x)
                {
                    writeSI16(data, offset.x);
                }
                if (offset.y)
                {
                    writeSI16(data, offset.y);
                }
            }
            else if (flags.numOfBytes == 3)
            {
                if (offset.x)
                {
                    writeFloat(data, pt.x * _scale);
                }
                if (offset.y)
                {
                    writeFloat(data, pt.y * _scale);
                }
            }
            _curPt = pt;
        }

        EdgeWriterReader::EdgeWriterReader(float scale, const Point& curPt)
            : _scale(scale), _curPt(curPt)
        {
            _intCurX = _curPt.x * _scale * 20;
            _intCurY = _curPt.y * _scale * 20;
        }

        EdgeWriterReader::Offset EdgeWriterReader::updateCurrent(Point last)
        {
            Offset offset;
            int32_t thisX = last.x * _scale * 20;
            int32_t thisY = last.y * _scale * 20;

            offset.x = thisX - _intCurX;
            offset.y = thisY - _intCurY;

            _curPt = last;
            _intCurX = thisX;
            _intCurY = thisY;

            return offset;
        }

        void EdgeWriterReader::readCurPoint(const uint8_t*& ptr,
                                            bool hasX,
                                            bool hasY,
                                            const FlagsInfo& flags)
        {
            if (flags.numOfBytes == 0)
            {
                _curPt = readPoint(ptr);
            }
            else if (flags.numOfBytes == 1)
            {
                if (hasX)
                {
                    _curPt.x += (readSI8(ptr) / 20.0);
                }
                if (hasY)
                {
                    _curPt.y += (readSI8(ptr) / 20.0);
                }
            }
            else if (flags.numOfBytes == 2)
            {
                if (hasX)
                {
                    _curPt.x += (readSI16(ptr) / 20.0);
                }
                if (hasY)
                {
                    _curPt.y += (readSI16(ptr) / 20.0);
                }
            }
            else if (flags.numOfBytes == 3)
            {
                if (hasX)
                {
                    _curPt.x = readFloat(ptr);
                }
                if (hasY)
                {
                    _curPt.y = readFloat(ptr);
                }
            }
        }

        void EdgeWriterReader::fillFlagsInfo(FlagsInfo& flags,
                                             const Offset& ctrl,
                                             const Offset& pt)
        {
            flags.hasXCtrl = (ctrl.x != 0);
            flags.hasYCtrl = (ctrl.y != 0);
            flags.hasXPos = (pt.x != 0);
            flags.hasYPos = (pt.y != 0);
            flags.numOfBytes = numberOfBytes(ctrl.x, ctrl.y, pt.x, pt.y);
        }

        void EdgeWriterReader::fillFlagsInfo(FlagsInfo& flags, const Offset& pt)
        {
            flags.hasXPos = (pt.x != 0);
            flags.hasYPos = (pt.y != 0);
            flags.numOfBytes = numberOfBytes(pt.x, pt.y);
        }

        void EdgeWriterReader::writeEdgeLine(Data& data,
                                             const LineTo& lineTo,
                                             bool useCompressed)
        {
            if (useCompressed)
            {
                FlagsInfo flags(EdgeType_Line);
                auto offset = updateCurrent(lineTo.point);
                fillFlagsInfo(flags, offset);
                writeUI8(data, flags.pack());
                writeOffset(data, offset, lineTo.point, flags);
            }
            else
            {
                FlagsInfo flags(EdgeType_Line);
                writeUI8(data, flags.pack());
                writePoint(data, lineTo.point, _scale);
                _curPt = lineTo.point;
            }
        }

        void EdgeWriterReader::writeEdgeCurve(Data& data,
                                              const CurveTo& curveTo,
                                              bool useCompressed)
        {
            if (useCompressed)
            {
                FlagsInfo flags(EdgeType_Curve);
                auto ctrlOffset = updateCurrent(curveTo.control);
                auto offset = updateCurrent(curveTo.point);

                fillFlagsInfo(flags, ctrlOffset, offset);
                writeUI8(data, flags.pack());

                writeOffset(data, ctrlOffset, curveTo.control, flags);
                writeOffset(data, offset, curveTo.point, flags);
            }
            else
            {
                FlagsInfo flags(EdgeType_Curve);
                writeUI8(data, flags.pack());
                writePoint(data, curveTo.control, _scale);
                writePoint(data, curveTo.point, _scale);
                _curPt = curveTo.point;
            }
        }

        LineTo EdgeWriterReader::readEdgeLine(const uint8_t*& ptr, const FlagsInfo& flags)
        {
            LineTo line;
            readCurPoint(ptr, flags.hasXPos, flags.hasYPos, flags);
            line.point = _curPt;
            return line;
        }

        CurveTo EdgeWriterReader::readEdgeCurve(const uint8_t*& ptr,
                                                const FlagsInfo& flags)
        {
            CurveTo curve;

            readCurPoint(ptr, flags.hasXCtrl, flags.hasYCtrl, flags);
            curve.control = _curPt;

            readCurPoint(ptr, flags.hasXPos, flags.hasYPos, flags);
            curve.point = _curPt;

            return curve;
        }

        uint8_t EdgeWriterReader::FlagsInfo::pack() const
        {
            uint8_t flags = type;
            flags |= (numOfBytes << 2);
            if (hasXCtrl)
            {
                flags |= EdgeWriterReader::EdgeMask_HasXControl;
            }
            if (hasYCtrl)
            {
                flags |= EdgeWriterReader::EdgeMask_HasYControl;
            }
            if (hasXPos)
            {
                flags |= EdgeWriterReader::EdgeMask_HasXPos;
            }
            if (hasYPos)
            {
                flags |= EdgeWriterReader::EdgeMask_HasYPos;
            }
            return flags;
        }
        
        EdgeWriterReader::FlagsInfo::FlagsInfo(EdgeType t) : type(t)
        {
            numOfBytes = 0;
            hasXPos = false;
            hasYPos = false;
            hasXCtrl = false;
            hasYCtrl = false;
        }
        
        void EdgeWriterReader::FlagsInfo::unpack(uint8_t flags)
        {
            type = (EdgeWriterReader::EdgeType)(flags & 0x3);
            numOfBytes = (flags >> 2) & 0x3;
			hasXCtrl = (flags & EdgeMask_HasXControl) != 0;
			hasYCtrl = (flags & EdgeMask_HasYControl) != 0;
			hasXPos = (flags & EdgeMask_HasXPos) != 0;
			hasYPos = (flags & EdgeMask_HasYPos) != 0;
        }
    };
};
