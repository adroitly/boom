//
//  RpcClient.cpp
//  RPCTest
//
//  Created by HJC on 15/2/11.
//  Copyright (c) 2015年 HJC. All rights reserved.
//

#include "RpcClient.h"
#include "rpcpack.h"
#include "clover/ScopeGuard.h"
#include "CRC.h"
#include <algorithm>
#include <string>

namespace rpc
{
    const char* StatusServerClose           = "StatusServerClose";
    const char* StatusServerConnectIng      = "StatusServerConnectIng";
    const char* StatusServerConnectSuccess  = "StatusServerConnectSuccess";
    const char* StatusServerConnectFaild    = "StatusServerConnectFaild";
    const char* StatusCheckCRCError         = "StatusCheckCRCError";
    RpcClient::RpcClient()
    {
        _ctx = nullptr;
        _onMessage = nullptr;
        _onStatus = nullptr;
        _socket = std::make_shared<SocketClient>(this);
    }

    void RpcClient::setCallback(void* ctx, message_call_back onMessage, status_call_back onStatus)
    {
        _ctx = ctx;
        _onMessage = onMessage;
        _onStatus = onStatus;
    }
    
    bool RpcClient::connect(const char* ip, int port, const char* socketKey)
    {
        if (nullptr == socketKey)
        {
            return _socket->connect(ip, port);
        }
        
        auto iter = _socketPtrMap.find(socketKey);
        if (iter != _socketPtrMap.end())
        {
            return iter->second->connect(ip, port);
        }
        else
        {
            SocketClientPtr ptr = std::make_shared<SocketClient>(this);
            _socketPtrMap[socketKey] = ptr;
            return ptr->connect(ip, port);
        }
    }
    
    void RpcClient::disconnect(const char* socketKey)
    {
        if (nullptr == socketKey)
        {
            _socket->disconnect();
            return;
        }
        
        auto iter = _socketPtrMap.find(socketKey);
        if (iter != _socketPtrMap.end())
        {
            (iter->second)->disconnect();
//            _socketPtrMap.erase(iter);
        }
    }
    
    void RpcClient::dispatchCallbacks(size_t maxCallbackCount)
    {
        _socket->dispatchCallbacks(maxCallbackCount);
        for (auto iter=_socketPtrMap.begin(); iter!=_socketPtrMap.end(); iter++)
        {
            iter->second->dispatchCallbacks(maxCallbackCount);
            if (iter->second->isCloseed())
            {
                _socketPtrMap.erase(iter);
                break;
            }
        }
        
    }
    
    uint16_t RpcClient::send(const char* cmd, const void* data, size_t size, const char* socketKey)
    {
        membuf_init_stack(result, 64);
        CLOVER_SCOPE_EXIT
        {
            membuf_finish(result);
        };

        // 数据包格式：长度（4字节）+ type（字符串，以\0结尾） + data（protobuf二进制数据）+ CRC（16位验证）
        // CRC = CRC16(type .. data)
        libra_slice cmd_range = { cmd, cmd + strlen(cmd) };
        libra_slice data_range = { (char*)data, (char*)data + size };
        
        rpc::message_pack(result, cmd_range, data_range);
        
        if (nullptr == socketKey)
        {
            _socket->send(membuf_ptr(result, 0), membuf_size(result));
        }
        else
        {
            auto iter = _socketPtrMap.find(socketKey);
            if (iter != _socketPtrMap.end())
            {
                iter->second->send(membuf_ptr(result, 0), membuf_size(result));
            }
        }
        return 0;
    }

    const char* RpcClient::_getSocketWithClient(const SocketClient* client)
    {
        for (auto iter=_socketPtrMap.begin(); iter!=_socketPtrMap.end(); iter++)
        {
            if (iter->second.get() == client)
            {
                return iter->first.c_str();
            }
        }
        return nullptr;
    }
    
    // realData已经不包含前4个数据
    void RpcClient::socketClientMessage(SocketClient* client, const void* realData, size_t size)
    {
        auto key = _getSocketWithClient(client);
        if (!rpc::message_is_complete((char *)realData, size))
        {
            if (_onStatus)
            {
                _onStatus(_ctx, StatusCheckCRCError, "check crc error", key);
            }
            return;
        }
        
        libra_slice cmd_range;
        libra_slice data_range;
        rpc::message_unpack((char*)realData, size, &cmd_range, &data_range);
        
        if (_onMessage)
        {
            std::string cmd(cmd_range.begin, cmd_range.end - cmd_range.begin);
            _onMessage(_ctx, cmd.c_str(), data_range.begin, data_range.end - data_range.begin, key);
        }
    }

    void RpcClient::socketClientServerClose(SocketClient* client)
    {
        if (_onStatus)
        {
            printf("与服务器断开链接\n");
            auto key = _getSocketWithClient(client);
            _onStatus(_ctx, StatusServerClose, "server close", key);
        }
    }
    
    void RpcClient::socketClientServerConnect(SocketClient* client, eConnectStatus status)
    {
        if (_onStatus)
        {
            const char* cmd = nullptr;
            if (eConnectStatus::Success==status)
                cmd = StatusServerConnectSuccess;
            else if (eConnectStatus::Faild==status)
                cmd = StatusServerConnectFaild;
            else
                cmd = StatusServerConnectIng;
        
            auto key = _getSocketWithClient(client);
            _onStatus(_ctx, cmd, "connect callback", key);
        }
    }
}