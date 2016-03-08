//
//  SocketClient.cpp
//  RPCTest
//
//  Created by HJC on 15/2/9.
//  Copyright (c) 2015年 HJC. All rights reserved.
//

#include "SocketClient.h"
#include "Message.h"
#include <thread>
#include <netinet/in.h>
#include <condition_variable>

#include <string>

namespace rpc
{
    class SocketClientImpl : public clover::IntrusiveObject<SocketClientImpl>
    {
    public:
        SocketClientImpl(SocketClient* client, SocketClientListener* listener);
        ~SocketClientImpl();

        bool connect(const char* ip, int port);
        void disconnect();

        void send(const void* data, size_t size);
        void dispatchCallbacks(size_t maxCallbackCount);

        void doReadThread();
        void doWriteThread();

        void connectThread(const char* ip, int port);
        
        bool isExitThread()
        {
            LockGuard lock(_mutex);
            return _exitThread;
        }

        void setServerClosed()
        {
            LockGuard lock(_mutex);
            _serverClosed = true;
        }

        bool isServerClosed()
        {
            LockGuard lock(_mutex);
            return _serverClosed;
        }
        
        bool isClosed()
        {
            return eSocketStatus::Close==_socketStatus;
        }
        
    private:
        void connectedAction();

    private:
        enum class eSocketStatus
        {
            Close,
            Connecting,
            Connected,
            ConnectDone,
        };
        
        bool _exitThread;
        bool _serverClosed;
        eSocketStatus _socketStatus;
        bool _isConnected;
        bool _rejectCallbackInfo;
        Mutex _mutex;
        SocketClient* _client;
        SocketClientListener* _listener;
        libra_socket _socket;
        MessageQueue _request;   // 请求
        MessageQueue _response;  // 响应
        ReadBuffer _readBuffer;
        std::condition_variable _requestCond;
    };

    /////////////////////////////////////////////////
    static void s_readThread(void* ctx)
    {
        auto impl = reinterpret_cast<SocketClientImpl*>(ctx);
        impl->doReadThread();
        impl->release();
    }

    static void s_writeThread(void* ctx)
    {
        auto impl = reinterpret_cast<SocketClientImpl*>(ctx);
        impl->doWriteThread();
        impl->release();
    }
    
    SocketClientImpl::SocketClientImpl(SocketClient* client, SocketClientListener* listener)
    {
        _client = client;
        _listener = listener;
        _exitThread = false;
        _serverClosed = false;
        _socketStatus = eSocketStatus::Close;
        _isConnected = false;
        _rejectCallbackInfo = true;
    }
    
    SocketClientImpl::~SocketClientImpl()
    {
        libra_socket_close(&_socket);
    }
    
    void SocketClientImpl::connectThread(const char* ip, int port)
    {
        _isConnected = libra_socket_connect(&_socket, ip, port);
        _socketStatus = eSocketStatus::Connected;
    }
    
    bool SocketClientImpl::connect(const char* ip, int port)
    {
        if (eSocketStatus::Close == _socketStatus)
        {
            _socketStatus = eSocketStatus::Connecting;
            _rejectCallbackInfo = true;
            
            libra_socket_open_tcp(&_socket);
            std::thread thread(&SocketClientImpl::connectThread, this, ip, port);
            thread.detach();
        }
        else if(eSocketStatus::Connecting == _socketStatus)
        {
            _listener->socketClientServerConnect(_client, eConnectStatus::Ing);
        }
        else
        {
            _listener->socketClientServerConnect(_client, eConnectStatus::Success);
        }

        return true;
    }
    
    void SocketClientImpl::connectedAction()
    {
        if (_isConnected)
        {
            _socketStatus = eSocketStatus::ConnectDone;
            _serverClosed = false;
            _exitThread = false;
            
            auto runThread = [=](decltype(s_readThread) woker)
            {
                this->retain();
                std::thread thread(woker, this);
                thread.detach();
            };
            
            runThread(s_writeThread);
            runThread(s_readThread);
            _rejectCallbackInfo = false;
        }
        else
        {
            _socketStatus = eSocketStatus::Close;
            libra_socket_close(&_socket);
        }
        
        eConnectStatus status = _isConnected ? eConnectStatus::Success : eConnectStatus::Faild;
        _listener->socketClientServerConnect(_client, status);
    }
    
    void SocketClientImpl::dispatchCallbacks(size_t maxCallbackCount)
    {
        if (eSocketStatus::Connected == _socketStatus)
        {
            this->connectedAction();
            return;
        }
        
        if (nullptr==_listener || _rejectCallbackInfo)
        {
            return;
        }
        
        for (size_t i = 0; i < maxCallbackCount; i++)
        {
            auto msg = _response.pop();
            if (!msg)
            {
                if (isServerClosed())
                {
                    _listener->socketClientServerClose(_client);
                    _rejectCallbackInfo = true;
                }
                break;
            }
            
            _listener->socketClientMessage(_client, msg->getData(), msg->getSize());
        }
    }

    void SocketClientImpl::send(const void* data, size_t size)
    {
        if (eSocketStatus::ConnectDone != _socketStatus)
        {
            printf("error: server is unconnect\n");
            return;
        }
//        printf("send data = %s\n", (const char*)data);
        auto msg = Message::pack((uint8_t*)data, size);
        _request.push(msg);
        _requestCond.notify_one();
    }

    void SocketClientImpl::disconnect()
    {
        if (eSocketStatus::ConnectDone == _socketStatus)
        {
//            if (_exitThread) {
//                return;
//            }
//            
//            _exitThread = true;
            {
                LockGuard lock(_mutex);
                LockGuard lock2(_request.mutex);
                _exitThread = true;
            }
            _socketStatus = eSocketStatus::Close;
            _requestCond.notify_one();
            libra_socket_close(&_socket);
        }
    }

    void SocketClientImpl::doReadThread()
    {
        char buffer[1024];
        for (;;)
        {
            if (isExitThread())
            {
                break;
            }
            ssize_t n = libra_socket_read(&_socket, buffer, 1024);
            if (n == 0)
            {
                disconnect();
                setServerClosed();
            }
            else if (n > 0)
            {
                _readBuffer.push(buffer, n);
                for (;;)
                {
                    auto msg = _readBuffer.pop();
                    if (!msg)
                    {
                        break;
                    }
                    _response.push(msg);
                }
            }
        }
    }

    void SocketClientImpl::doWriteThread()
    {
        for (;;)
        {
            if (isExitThread())
            {
                break;
            }

            {
                std::unique_lock<std::mutex> lck(_request.mutex);
                while (_request.list.empty() && !_exitThread)
                {
                    _requestCond.wait(lck);
                }
            }

            auto item = _request.pop();
            if (item)
            {
                item->send(_socket);
            }
        }
    }

    /////////////////////////////
    SocketClient::SocketClient(SocketClientListener* listener)
    {
        _impl = new SocketClientImpl(this, listener);
    }

    SocketClient::~SocketClient()
    {
        _impl->disconnect();
        _impl->release();
    }

    bool SocketClient::connect(const char* ip, int port)
    {
        return _impl->connect(ip, port);
    }

    void SocketClient::disconnect()
    {
        _impl->disconnect();
    }

    void SocketClient::send(const void* data, size_t size)
    {
        return _impl->send(data, size);
    }

    void SocketClient::dispatchCallbacks(size_t maxCallbackCount)
    {
        _impl->dispatchCallbacks(maxCallbackCount);
    }
    
    bool SocketClient::isCloseed()
    {
        return _impl->isClosed();
    }
    
}
