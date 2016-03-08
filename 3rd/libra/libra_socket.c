//=============================================================================
//  libra
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#include "libra_socket.h"
#include <stdio.h>
#include <sys/types.h>
#include <memory.h>
#include <errno.h>

#ifdef _WIN32
#pragma comment(lib, "ws2_32.lib")
static int write(SOCKET s, const void* buf, size_t size)
{
    return send(s, (const char*)buf, size, 0);
}
static int read(SOCKET s, void* buf, size_t size)
{
    return recv(s, (char*)buf, size, 0);
}

void libra_socket_startup()
{
    WSADATA ws;
    WSAStartup(MAKEWORD(2, 2), &ws);
}
#else
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void libra_socket_startup()
{
}

static libra_inline void closesocket(int fd)
{
    close(fd);
}

#endif

void libra_socket_open_tcp(libra_socket* S)
{
    S->fd = socket(AF_INET, SOCK_STREAM, 0);
    S->type = AF_INET;
}

void libra_socket_close(libra_socket* S)
{
    if (S->fd > 0)
    {
        closesocket(S->fd);
        S->fd = 0;
    }
}

int libra_socket_fd(libra_socket* S)
{
    return S->fd;
}

bool libra_socket_connect(libra_socket* S, const char* ip, int port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
#ifdef _WIN32
    addr.sin_addr.S_un.S_addr = inet_addr(ip);
#else
    inet_pton(AF_INET, ip, &addr.sin_addr);
#endif
    return connect(S->fd, (struct sockaddr*)&addr, sizeof(addr)) == 0;
}

ssize_t libra_socket_write(libra_socket* S, void* vptr, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char* ptr;

    ptr = (char*)vptr;
    nleft = n;
    while (nleft > 0)
    {
        if ((nwritten = write(S->fd, ptr, nleft)) <= 0)
        {
            if (nwritten < 0 && errno == EINTR)
            {
                nwritten = 0; /* and call write() again */
            }
            else
            {
                return (-1); /* error */
            }
        }

        nleft -= nwritten;
        ptr += nwritten;
    }
    return (n);
}

ssize_t libra_socket_write_str(libra_socket* S, const char* str)
{
    return libra_socket_write(S, (void*)str, strlen(str));
}

ssize_t libra_socket_read(libra_socket* S, void* vptr, ssize_t n)
{
    return read(S->fd, vptr, n);
}
