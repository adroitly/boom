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

#ifndef __NETWORK_HTTPRESPONSE_H__
#define __NETWORK_HTTPRESPONSE_H__

#include <vector>
#include <boost/any.hpp>
#include "async/OperationQueue.h"

namespace network
{
    class HttpResponse final
    {
    public:
        HttpResponse() : _responseCode(0), _requestTag(0) {}
        
        typedef std::vector<char> data_t;
        
        const data_t& getData() const       { return _responseData;        }
        const char* getDataBytes() const    { return &_responseData[0];    }
        size_t getDataSize() const          { return _responseData.size(); }
        int getResponseCode() const         { return _responseCode;        }
        int getRequestTag() const           { return _requestTag;          }
        uint64_t  getRequestId() const      { return _requestId;           }
        
        template <typename T>
        const T& getUserData() const
        {
            return *boost::unsafe_any_cast<T>(&_userData);
        }
        
        void swap(HttpResponse& rhs);
        
    private:
        friend class HttpClient;
        data_t      _responseData;
        boost::any  _userData;
        uint64_t   _requestId;
        int         _requestTag;
        int         _responseCode;
    };
    
    inline void HttpResponse::swap(HttpResponse& rhs)
    {
        _responseData.swap(rhs._responseData);
        std::swap(_requestId,    rhs._requestId);
        std::swap(_requestTag,   rhs._requestTag);
        std::swap(_responseCode, rhs._responseCode);
        std::swap(_userData,     rhs._userData);
    }
}

#endif