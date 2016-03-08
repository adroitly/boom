//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_MOVIESHAREDATA_H__
#define __FLA_MOVIESHAREDATA_H__

#include "clover/IntrusiveObject.h"
#include "fla_BatchMoviewRender.h"
#include "fla_ReusableMoviewSet.h"
#include "fla_MoviePart.h"
#include <boost/pool/pool.hpp>

namespace fla
{
    class FlaMoviePart;
    class MovieClipListener;
    class MovieClipDataSource;

    class MovieClip;
    class MovieGlobalData : public clover::IntrusiveObject<MovieGlobalData, clover::RefCounter>
    {
    public:
        MovieGlobalData();
        ~MovieGlobalData();

        BatchMoviewRender renderer;
        ReusableMoviewSet reusableMovieSet;

        MovieClip* allocMovieClip(const Definition::Ptr& definition, MovieClipDataSource* dataSource);
        void freeMovieClip(MovieClip* clip);

    private:
        boost::pool<> _movieClipPool;
    };
}

#endif
