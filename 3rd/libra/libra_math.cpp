//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#include "libra_math.h"
#include "libra_utility.h"
#include <assert.h>
#include <algorithm>

unsigned long libra_next_pot(unsigned long x)
{
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    return x + 1;
}

static void random_shuffle(int* numbers, int len)
{
    while (len > 0)
    {
        int tmp = rand() % len;
        len--;
        std::swap(numbers[tmp], numbers[len]);
    }
}

static libra_inline void fill_number(int* numbers, int len, int min)
{
    int idx;
    for (idx = 0; idx < len; idx++)
    {
        numbers[idx] = min + idx;
    }
}

void libra_diff_randoms(int* result, int count, int min, int max)
{
    assert(0 < count);
    assert(min < max);
    assert(count <= max - min);

    int len = max - min;
    if (count == len)
    {
        fill_number(result, len, min);
        random_shuffle(result, len);
    }
    else
    {
		int* tmp_nums = (int*)libra_malloc(len * sizeof(int));
        fill_number(tmp_nums, len, min);
        int idx;
        for (idx = 0; idx < count; idx++)
        {
            int randIdx = rand() % len;
            result[idx] = tmp_nums[randIdx];
            len--;
            std::swap(tmp_nums[randIdx], tmp_nums[len]);
        }
		libra_free(tmp_nums);
    }
}
