//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_BinParseShape.h"

namespace fla
{
    void readEdgeList(const uint8_t*& ptr, EdgeList& edgeList)
    {
        Point curPt = edgeList.firstPt();
        bin::EdgeWriterReader edgeHelper(1.0, curPt);
        bin::EdgeWriterReader::FlagsInfo flags;
        flags.unpack(bin::readUI8(ptr));

        while (flags.type != bin::EdgeWriterReader::EdgeType_End)
        {
            if (flags.type == bin::EdgeWriterReader::EdgeType_Line)
            {
                edgeList.addEdge(edgeHelper.readEdgeLine(ptr, flags));
            }
            else if (flags.type == bin::EdgeWriterReader::EdgeType_Curve)
            {
                edgeList.addEdge(edgeHelper.readEdgeCurve(ptr, flags));
            }
            flags.unpack(bin::readUI8(ptr));
        }
    }

    void parsePaths(std::vector<fla::MorphPath>& paths, const uint8_t*& ptr)
    {
        size_t size = bin::readUI16Or32(ptr);
        if (size > 0)
        {
            paths.resize(size);
        }

        for (size_t i = 0; i < size; i++)
        {
            paths[i].edges<0>().setFirstPt(bin::readPoint(ptr));
            paths[i].edges<1>().setFirstPt(bin::readPoint(ptr));
            paths[i].setLineStyle((int)bin::readUI16(ptr) - 1);
            paths[i].setFillStyle((int)bin::readUI16(ptr) - 1);

            readEdgeList(ptr, paths[i].edges<0>());
            readEdgeList(ptr, paths[i].edges<1>());

            parsePaths(paths[i].subPaths(), ptr);
        }
    }
    
    void parsePaths(std::vector<fla::Path>& paths, const uint8_t*& ptr)
    {
        size_t size = bin::readUI16Or32(ptr);
        
        if (size > 0)
        {
            paths.resize(size);
        }
        
        for (size_t i = 0; i < size; i++)
        {
            paths[i].edges<0>().setFirstPt(bin::readPoint(ptr));
            paths[i].setLineStyle((int)bin::readUI16(ptr) - 1);
            paths[i].setFillStyle((int)bin::readUI16(ptr) - 1);
            
            readEdgeList(ptr, paths[i].edges<0>());
            
            parsePaths(paths[i].subPaths(), ptr);
        }
    }
}
