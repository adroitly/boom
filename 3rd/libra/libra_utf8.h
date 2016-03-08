//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================
#ifndef __LIBRA_UTF8_H__
#define __LIBRA_UTF8_H__

#include "libra_config.h"

/* utf8 和 utf16之间的相互转换 */
/* 返回值为转换后的长度 */
/* 使用的时候，可以先传进 0, 0 先得到需要空间的长度，分配好空间再进行转换 */

/* 比如
 int size = utf16_from_utf8(0, 0, utf8, utf8len);
 uint16_t utf16 = malloc((size + 1) * 2);
 utf16_from_utf8(utf16, size, utf8, utf8len);
 utf16[size] = 0;
 */
libra_extern size_t utf16_from_utf8(uint16_t* utf16, size_t utf16_len, const char* utf8, size_t utf8_len);
libra_extern size_t utf8_from_utf16(char* utf8, size_t utf8_len, const uint16_t* utf16, size_t utf16_len);

#endif
