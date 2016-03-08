//
//  RpcClient.h
//  RPCTest
//
//  Created by HJC on 15/2/11.
//  Copyright (c) 2015年 HJC. All rights reserved.
//

#ifndef __RPCCLIENT_H__
#define __RPCCLIENT_H__

#include <stdint.h>
#include <string>
#include <map>
//#include <memory.h>
#include "SocketClient.h"

namespace rpc
{
    extern const char* StatusServerClose;  //  server.close
    
    typedef std::shared_ptr<SocketClient> SocketClientPtr;
    typedef void (*message_call_back)(void* ctx, const char* cmd, const void* data, size_t size, const char* socketKey);
    typedef void (*status_call_back)(void* ctx, const char* cmd, const char* errorMsg, const char* socketKey);

    class RpcClient : boost::noncopyable, public SocketClientListener
    {
    public:
        RpcClient();

        void setCallback(void* ctx, message_call_back onMessage, status_call_back onStatus);
        
        // 通过socketKey可以创建多个socket
        bool connect(const char* ip, int port, const char* socketKey);
        void disconnect(const char* socketKey);
        uint16_t send(const char* cmd, const void* data, size_t size, const char* socketKey);
        
        void dispatchCallbacks(size_t maxCallbackCount);

    private:
        virtual void socketClientMessage(SocketClient* client, const void* data, size_t size) override;
        virtual void socketClientServerClose(SocketClient* client) override;
        virtual void socketClientServerConnect(SocketClient* client, eConnectStatus status) override;
        
        const char* _getSocketWithClient(const SocketClient* client);
        
    private:
        SocketClientPtr _socket;
        std::map<std::string, SocketClientPtr> _socketPtrMap;
        void* _ctx;
        message_call_back _onMessage;
        status_call_back _onStatus;
    };

}

#endif
