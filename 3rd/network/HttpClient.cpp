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

#include "./HttpClient.h"
#include "./CURLWrapper.h"
#include <vector>
#include <algorithm>

namespace network
{
    typedef HttpClient::CallbackType HttpCallbackType;

    struct CurlOperation : public async::Operation
    {
        CurlOperation()
        {
            callBack = nullptr;
            responseCode = 0;
            requestId = 0;
            tag = 0;
            resultType = HttpResultType::Error;
        }

        CURLRequest request;
        HttpCallbackType callBack;
        uint64_t requestId;
        std::vector<char> data;
        int32_t responseCode;
        HttpResultType resultType;
        boost::any userData;
        int tag;

        void action() override;

    private:
        HttpResultType processNetwork();
    };

    void CurlOperation::action()
    {
        resultType = processNetwork();
    }

    HttpResultType CurlOperation::processNetwork()
    {
        CURLWrapper curl;
        if (!curl.setup(request, &data))
        {
            return HttpResultType::Error;
        }

        if (request.method == CURLHttpMethod::Get)
        {
            if (!curl.setFollowLocation(true))
            {
                return HttpResultType::Error;
            }
        }
        CURLcode urlCode = curl.perform(&responseCode);
        if (urlCode == CURLE_OPERATION_TIMEDOUT)
        {
            return HttpResultType::Timeout;
        }

        if (urlCode == CURLE_OK && responseCode == 200)
        {
            return HttpResultType::Finish;
        }
        return HttpResultType::Error;
    }

    HttpClient& HttpClient::getInstance()
    {
        static HttpClient client;
        return client;
    }

    HttpClient::HttpClient() : _queue(1)
    {
        curl_global_init(CURL_GLOBAL_ALL);
    }

    HttpClient::~HttpClient()
    {
        curl_global_cleanup();
    }

    void HttpClient::setMaxConcurrentRequestCount(int maxCount)
    {
        _queue.setMaxConcurrentOperationCount(maxCount);
    }

    void HttpClient::dispatchResponseCallbacks(size_t maxCallbackCount)
    {
        _queue.dispatchCallbacks(maxCallbackCount);
    }

    void HttpClient::cancelRequestId(const uint64_t& requestId)
    {
        _queue.cancel(requestId);
    }

    uint64_t HttpClient::peedNextId() const
    {
        return _queue.peekNextOperationId();
    }

    static CURLHttpMethod curlMethodFrom(HttpMethod method)
    {
        switch (method)
        {
            case HttpMethod::Get:
                return CURLHttpMethod::Get;

            case HttpMethod::Post:
                return CURLHttpMethod::Post;

            default:
                break;
        }
    }

    uint64_t HttpClient::start(const HttpRequest& request, const CallbackType& callback)
    {
        auto operation = std::make_shared<CurlOperation>();
        CURLRequest& curlRequest = operation->request;
        curlRequest.method = curlMethodFrom(request._method);
        curlRequest.url = request._url;
        curlRequest.params = request._params;
        curlRequest.timeout = request._timeout;
        curlRequest.headers = request._headers;

        operation->userData = request._userData;
        operation->callBack = callback;
        operation->tag = request._tag;
        operation->requestId = _queue.addOperation(operation, this);
        _operations.push_back(operation);

        return operation->requestId;
    }

    void HttpClient::operationOnCompletion(const async::Operation::Ptr& operation, async::OperationResultType type)
    {
        auto iter = std::find(_operations.begin(), _operations.end(), operation);
        if (iter != _operations.end())
        {
            _operations.erase(iter);
        }

        auto ptr = std::static_pointer_cast<CurlOperation>(operation);
        HttpResponse respones;
        respones._requestId = ptr->requestId;
        respones._userData = ptr->userData;
        respones._requestTag = ptr->tag;
        respones._responseCode = ptr->responseCode;
        respones._responseData.swap(ptr->data);

        if (ptr->callBack)
        {
            HttpResultType resultType = HttpResultType::Cancel;
            if (type != async::OperationResultType::Cancel)
            {
                assert(ptr->resultType != HttpResultType::Cancel);
                resultType = ptr->resultType;
            }

            ptr->callBack(respones, resultType);
        }
    }
}
