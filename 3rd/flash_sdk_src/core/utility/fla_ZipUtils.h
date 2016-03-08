//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __CLOVER_ZIPUTILS_H__
#define __CLOVER_ZIPUTILS_H__

#include "clover/Data.h"

namespace fla
{
    clover::Data data_zipUncompress(const uint8_t* data, size_t len);
    clover::Data data_zipCompress(const uint8_t* data, size_t len);
}

#endif
