//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __LIBRA_SOCKET__
#define __LIBRA_SOCKET__

#include "libra_config.h"

#if _WIN32
#include <winsock.h>
typedef long ssize_t;
typedef SOCKET libra_socket_impl;
#else
typedef int libra_socket_impl;
#endif

typedef struct
{
	libra_socket_impl fd;
    int type;
} libra_socket;

libra_extern void libra_socket_startup();

libra_extern void libra_socket_open_tcp(libra_socket* S);
libra_extern void libra_socket_close(libra_socket* S);

libra_extern int libra_socket_fd(libra_socket* S);
libra_extern bool libra_socket_connect(libra_socket* S, const char* ip, int port);

libra_extern ssize_t libra_socket_write(libra_socket* S, void* data, size_t size);
libra_extern ssize_t libra_socket_write_str(libra_socket* S, const char* str);
libra_extern ssize_t libra_socket_read(libra_socket* S, void* vptr, ssize_t n);

#endif
