//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __LIBRA_ATOMIC_H__
#define __LIBRA_ATOMIC_H__

#include "libra_config.h"

#if _MSC_VER

#include <Windows.h>

#define libra_atomic_increment(a) InterlockedIncrement(a)
#define libra_atomic_decrement(a) InterlockedDecrement(a)

#else

#define libra_atomic_increment(a) __sync_add_and_fetch(a, 1)
#define libra_atomic_decrement(a) __sync_sub_and_fetch(a, 1)

#endif

#endif
