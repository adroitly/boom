//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_REUSABLEMOVIEWSET_H__
#define __FLA_REUSABLEMOVIEWSET_H__

#include <map>
#include <memory>
#include <vector>
#include <boost/intrusive_ptr.hpp>
#include "../../core/base/fla_RefPtrVector.h"

namespace fla
{
    class MovieClip;
    class Definition;
    typedef boost::intrusive_ptr<MovieClip> MovieClipPtr;
    class ReusableMoviewSet
    {
    public:
        void add(Definition* Id, MovieClip* node);
        MovieClipPtr reuseMoview(Definition* Id);

        void clear();

    private:
        class Record
        {
        public:
            void add(MovieClip* node);
            MovieClipPtr reuseMoview();

        private:
            RefPtrVector<MovieClip>::type _nodes;
        };

    private:
        std::map<Definition*, Record> _records;
    };
}

#endif
