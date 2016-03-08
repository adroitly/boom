//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __LIBRA_CONFIG_H__
#define __LIBRA_CONFIG_H__

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#ifdef LIBRA_FLOAT
typedef LIBRA_FLOAT libra_float
#else
typedef float libra_float;
#endif

#define libra_malloc malloc
#define libra_free free
#define libra_realloc realloc

#if defined(__cplusplus)
#define libra_extern extern "C"
#else
#define libra_extern extern
#endif

#if defined(_MSC_VER) && !defined(__cplusplus)
#define libra_inline __inline
#else
#define libra_inline inline
#endif

#define __libra_macro_concat(s1, s2) s1##s2
#define libra_macro_concat(s1, s2) __libra_macro_concat(s1, s2)

#endif
