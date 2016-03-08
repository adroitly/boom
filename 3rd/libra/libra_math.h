//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __LIBRA_MATH_H__
#define __LIBRA_MATH_H__

#include "libra_config.h"
#include <stdlib.h>
#include <math.h>
#include <algorithm>

namespace libra
{
    inline int floor(float x)
    {
        int i = (int)x;     /* truncate */
        return i - (i > x); /* convert trunc to floor */
    }

    inline int ceil(float x)
    {
        int i = (int)x;
        return i + (x > i);
    }

    inline bool is_float(float x)
    {
        return floor(x) != x;
    }

    inline bool is_even(int v)
    {
        return (v & 0x01) == 0;
    }

    inline bool is_odd(int v)
    {
        return !is_even(v);
    }
    
    template <typename T>
    inline T max3(T v0, T v1, T v2)
    {
        return std::max(v0, std::max(v1, v2));
    }
}

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 产生0, 1之间的浮点数
static libra_inline libra_float libra_random_0_1()
{
    return ((libra_float)rand() / RAND_MAX);
}

// 产生min, max之间的浮点数
static libra_inline libra_float libra_random_f(libra_float min, libra_float max)
{
    return (min + (max - min) * libra_random_0_1());
}

static libra_inline int libra_random(int min, int max)
{
    int range = max - min;
    return rand() % range + min;
}

// 生成 [min, max) 之间的随机数，保证每个随机数字都不相同
libra_extern void libra_diff_randoms(int* result, int cout, int min, int max);

static libra_inline int libra_mode_inc(int value, int mode)
{
    return (value + 1) % mode;
}

libra_extern unsigned long libra_next_pot(unsigned long x);

static libra_inline libra_float libra_radian_to_degree(libra_float angle)
{
    return (libra_float)(angle / M_PI * 180.0);
}

static libra_inline libra_float libra_degree_to_radian(libra_float angle)
{
    return (libra_float)(angle * M_PI / 180.0);
}

static libra_inline libra_float libra_lerp(libra_float lhs, libra_float rhs, libra_float ratio)
{
    return (libra_float)(lhs * (1.0 - ratio) + rhs * ratio);
}

#define is_float_equal(x, y, accuracy) (fabs((x) - (y)) < (accuracy))

static libra_inline libra_float libra_round(libra_float r)
{
    double result = (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
    return (libra_float)result;
}

#endif
