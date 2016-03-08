//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_ReusableMoviewSet.h"
#include "fla_MovieClip.h"
using namespace cocos2d;

namespace fla
{
    void ReusableMoviewSet::Record::add(MovieClip* node)
    {
        _nodes.push_back(node);
    }

    void ReusableMoviewSet::clear()
    {
        _records.clear();
    }

    MovieClipPtr ReusableMoviewSet::Record::reuseMoview()
    {
        MovieClipPtr result;
        if (_nodes.empty())
        {
            return result;
        }
        result = _nodes.back();
        _nodes.pop_back();
        return result;
    }

    MovieClipPtr ReusableMoviewSet::reuseMoview(Definition* Id)
    {
        auto iter = _records.find(Id);
        if (iter != _records.end())
        {
            return iter->second.reuseMoview();
        }
        return nullptr;
    }

    void ReusableMoviewSet::add(Definition* Id, MovieClip* node)
    {
        _records[Id].add(node);
    }
}
