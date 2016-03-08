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

#ifndef __NETWORK_CURLWRAPPER_H__
#define __NETWORK_CURLWRAPPER_H__

#include "curl/curl.h"
#include <boost/noncopyable.hpp>
#include <assert.h>
#include <string>
#include <map>
#include <vector>

namespace network
{
    enum class CURLHttpMethod
    {
        Get,
        Post,
    };

    struct CURLRequest
    {
        CURLRequest()
        {
            timeout = 10;
            method = CURLHttpMethod::Get;
        }

        CURLHttpMethod method;
        std::string url;
        std::map<std::string, std::string> params;
        std::map<std::string, std::string> headers;
        double timeout;
    };

    typedef size_t (*write_callback)(void* ptr, size_t size, size_t nmemb, void* stream);
    class CURLWrapper : boost::noncopyable
    {
    public:
        CURLWrapper();
        ~CURLWrapper();

        CURLcode perform(int* responseCode);

        bool setup(const CURLRequest& request, write_callback callback, void* stream);
        bool setup(const CURLRequest& request, std::vector<char>* data);
        bool setup(const CURLRequest& request, std::vector<uint8_t>* data);
        bool setup(const CURLRequest& request, std::string* string);

        bool setErrorBuf(const char* buff, size_t size)
        {
            assert(size >= CURL_ERROR_SIZE);
            return setOption(CURLOPT_ERRORBUFFER, buff);
        }

        bool setURL(const std::string& url)
        {
            return setOption(CURLOPT_URL, url.c_str());
        }

        bool setWriteCallback(write_callback callback, void* callbackData)
        {
            return setOption(CURLOPT_WRITEFUNCTION, callback) && setOption(CURLOPT_WRITEDATA, callbackData);
        }

        bool setHeaderCallback(write_callback callback, void* callbackData)
        {
            return setOption(CURLOPT_HEADERFUNCTION, callback) && setOption(CURLOPT_HEADERDATA, callbackData);
        }

        bool setTimeout(double timeout)
        {
            return setOption(CURLOPT_TIMEOUT, static_cast<long>(timeout)) &&
                   setOption(CURLOPT_CONNECTTIMEOUT, static_cast<long>(timeout));
        }

        bool setConnectTimeout(double timeout)
        {
            return setOption(CURLOPT_CONNECTTIMEOUT, static_cast<long>(timeout));
        }

        bool setUseSSL(bool useSSL)
        {
            long value = useSSL ? 1L : 0L;
            return setOption(CURLOPT_SSL_VERIFYPEER, value) && setOption(CURLOPT_SSL_VERIFYHOST, value);
        }

        bool setFollowLocation(bool flag)
        {
            long value = flag ? 1L : 0L;
            return setOption(CURLOPT_FOLLOWLOCATION, value);
        }

        bool setHttpHeaders(const std::map<std::string, std::string>& headers);

    private:
        template <class T>
        bool setOption(CURLoption option, T data)
        {
            return CURLE_OK == curl_easy_setopt(_curl, option, data);
        }

        bool setupPostRequest(const CURLRequest& request);
        bool setupGetRequest(const CURLRequest& request);

    private:
        struct curl_slist* _cHeaders;
        CURL* _curl;
        char _errorBuff[CURL_ERROR_SIZE];
    };
}

#endif
