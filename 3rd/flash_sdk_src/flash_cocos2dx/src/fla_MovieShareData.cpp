//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_MovieShareData.h"
#include "fla_MovieClip.h"
#include <libs/system/src/error_code.cpp>

namespace fla
{
    ///////////////////
    MovieGlobalData::MovieGlobalData() : renderer(64), _movieClipPool(sizeof(MovieClip))
    {
    }

    MovieGlobalData::~MovieGlobalData()
    {
    }

    MovieClip* MovieGlobalData::allocMovieClip(const Definition::Ptr& def, MovieClipDataSource* dataSource)
    {
        void* ptr = _movieClipPool.malloc();
        MovieClip* clip = new (ptr) MovieClip();
        clip->init(def, dataSource);
        return clip;
    }

    void MovieGlobalData::freeMovieClip(MovieClip* clip)
    {
        clip->~MovieClip();
        _movieClipPool.free(clip);
    }
}