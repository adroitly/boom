//
//  SocketClient.h
//  RPCTest
//
//  Created by HJC on 15/2/9.
//  Copyright (c) 2015年 HJC. All rights reserved.
//

#ifndef __RPC_SOCKETCLIENT_H__
#define __RPC_SOCKETCLIENT_H__

#include <stddef.h>
#include <boost/noncopyable.hpp>

namespace rpc
{
    enum class eConnectStatus
    {
        Ing,
        Success,
        Faild
    };
    
    class SocketClient;
    class SocketClientListener
    {
    public:
        virtual ~SocketClientListener()  {}
        virtual void socketClientMessage(SocketClient* client, const void* data, size_t size) {}
        virtual void socketClientServerClose(SocketClient* client)   {}
        virtual void socketClientServerConnect(SocketClient* client, eConnectStatus status) {}
    };
    
    class SocketClientImpl;
    class SocketClient : boost::noncopyable
    {
    public:
        SocketClient(SocketClientListener* listener);
        ~SocketClient();
        
        bool connect(const char* ip, int port);
        void disconnect();
        
        void send(const void* data, size_t size);
        void dispatchCallbacks(size_t maxCallbackCount);
        
        bool isCloseed();
    private:
        SocketClientImpl* _impl;
    };
}

#endif
