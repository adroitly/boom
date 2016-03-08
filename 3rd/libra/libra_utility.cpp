//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#include "libra_utility.h"
#include <assert.h>

#ifdef _WIN32
#ifdef __GNUC__
#else
#include <objbase.h>
void libra_uuid_generate(unsigned char result[16])
{
    assert(sizeof(GUID) == 16);
    GUID* guid = (GUID*)result;
    CoCreateGuid(guid);
}
#endif
#else

#if defined(__MAC_OS_X_VERSION_MIN_REQUIRED)
#include <uuid/uuid.h>
void libra_uuid_generate(unsigned char result[16])
{
    assert(sizeof(uuid_t) == 16);
    uuid_generate(result);
}
#endif

#endif
