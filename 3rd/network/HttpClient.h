/*
 The MIT License (MIT)

 Copyright (c) 2015 HJC hjcapple@gmail.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#ifndef __NETWORK_HTTPCLIENT_H__
#define __NETWORK_HTTPCLIENT_H__

#include <memory>
#include <boost/noncopyable.hpp>
#include "./HttpRequest.h"
#include "./HttpResponse.h"
#include "async/OperationQueue.h"

namespace network
{
    enum class HttpResultType
    {
        Cancel,
        Error,
        Timeout,
        Finish,
    };

    class HttpClientImpl;
    class HttpClient : boost::noncopyable, public async::OperationCallBack
    {
    public:
        // 返回单件实例
        static HttpClient& getInstance();

        // 设置后台最大的同时请求数目
        void setMaxConcurrentRequestCount(int maxCount);

        // 发起一个网络请求
        typedef std::function<void(const HttpResponse&, HttpResultType)> CallbackType;
        
        uint64_t peedNextId() const;
        uint64_t start(const HttpRequest& request, const CallbackType& callback);

        // 取消网络请求
        void cancelRequestId(const uint64_t& requestId);

        // 通知外面调用CallBack函数
        void dispatchResponseCallbacks(size_t maxCallbackCount);

    private:
        void operationOnCompletion(const async::Operation::Ptr& operation, async::OperationResultType type);

    private:
        HttpClient();
        ~HttpClient();
        async::OperationQueue _queue;
        std::vector<async::Operation::Ptr> _operations;
    };
}

#endif
