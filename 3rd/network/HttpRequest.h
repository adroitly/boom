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

#ifndef __NETWORK_HTTPREQUEST_H__
#define __NETWORK_HTTPREQUEST_H__

#include <string>
#include <map>
#include <vector>
#include <boost/any.hpp>

namespace network
{
    enum class HttpMethod
    {
        Get,
        Post,
    };
    
    class HttpRequest final
    {
    public:
        HttpRequest() : HttpRequest("", HttpMethod::Get) {}
        HttpRequest(const std::string& url, HttpMethod method = HttpMethod::Get)
            : _url(url), _method(method)
        {
            _timeout = 10;
            _tag = 0;
        }
        
        void setUrl(const std::string& url) { _url = url;           }
        void setMethod(HttpMethod method)   { _method = method;     }
        void setTag(int tag)                { _tag = tag;           }
        void setTimeout(double timeout)     { _timeout = timeout;   }
        
        template <typename T>
        void setUserData(const T& data)
        {
            _userData = data;
        }
        
        void addParameter(const std::string& key, const std::string& value)
        {
            _params[key] = value;
        }
        
        void addHeader(const std::string& key, const std::string& value)
        {
            _headers[key] = value;
        }
        
    private:
        friend class HttpClient;
        HttpMethod                          _method;
        std::string                         _url;
        std::map<std::string, std::string>  _params;
        std::map<std::string, std::string>  _headers;
        boost::any                          _userData;
        double                              _timeout;
        int                                 _tag;
    };
}

#endif
