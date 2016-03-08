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

#include "./CURLWrapper.h"
#include <vector>
#include <boost/algorithm/string.hpp>

namespace network
{
    static std::string url_encode(CURL* curl, const std::string& str)
    {
        char* result = curl_easy_escape(curl, str.c_str(), (int)str.length());
        std::string cppResult = result;
        curl_free(result);
        return cppResult;
    }

    static std::string changeMapToNetParam(CURL* curl, const std::map<std::string, std::string>& map)
    {
        std::vector<std::string> v;
        v.reserve(map.size());

        for (auto& iter : map)
        {
            auto str = iter.first;
            str += "=";
            str += url_encode(curl, iter.second);
            v.push_back(str);
        }
        return boost::join(v, "&");
    }

    bool CURLWrapper::setHttpHeaders(const std::map<std::string, std::string>& headers)
    {
        if (!headers.empty())
        {
            if (_cHeaders)
            {
                curl_slist_free_all(_cHeaders);
                _cHeaders = nullptr;
            }

            for (auto& pair : headers)
            {
                auto head = pair.first + ": " + pair.second;
                /* append custom headers one by one */
                _cHeaders = curl_slist_append(_cHeaders, head.c_str());
            }

            CURLcode code = curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, _cHeaders);
            return (code == CURLE_OK);
        }
        return true;
    }

    CURLcode CURLWrapper::perform(int* responseCode)
    {
        CURLcode code = curl_easy_perform(_curl);
        if (CURLE_OK != code)
        {
            return code;
        }
        return curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, responseCode);
    }

    CURLWrapper::CURLWrapper()
    {
        _curl = curl_easy_init();
        _cHeaders = nullptr;
        curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);
    }

    CURLWrapper::~CURLWrapper()
    {
        if (_cHeaders)
        {
            curl_slist_free_all(_cHeaders);
        }

        if (_curl)
        {
            curl_easy_cleanup(_curl);
        }
    }

    bool CURLWrapper::setupPostRequest(const CURLRequest& request)
    {
        auto netParams = changeMapToNetParam(_curl, request.params);
        if (!netParams.empty())
        {
            setOption(CURLOPT_POSTFIELDSIZE, static_cast<long>(netParams.size()));
            setOption(CURLOPT_COPYPOSTFIELDS, netParams.c_str());
        }

        return setOption(CURLOPT_POST, 1L) && setURL(request.url);
    }

    bool CURLWrapper::setupGetRequest(const CURLRequest& request)
    {
        auto netParams = changeMapToNetParam(_curl, request.params);
        auto url = request.url;
        if (!netParams.empty())
        {
            url += "?";
            url += netParams;
        }
        return setURL(url);
    }

    bool CURLWrapper::setup(const CURLRequest& request, write_callback callback, void* stream)
    {
        assert(_curl);

        bool result = setErrorBuf(_errorBuff, CURL_ERROR_SIZE) && setTimeout(request.timeout) && setUseSSL(false) &&
                      setWriteCallback(callback, stream);

        if (result)
        {
            if (request.method == CURLHttpMethod::Get)
            {
                result = setupGetRequest(request);
            }
            else
            {
                result = setupPostRequest(request);
            }

            if (result)
            {
                setHttpHeaders(request.headers);
            }
        }
        return result;
    }

    template <typename T>
    static size_t s_writeData(void* ptr, size_t size, size_t nmemb, void* stream)
    {
        auto recvBuffer = (T*)stream;
        size_t sizes = size * nmemb;
        recvBuffer->insert(recvBuffer->end(), (char*)ptr, (char*)ptr + sizes);
        return sizes;
    }

    bool CURLWrapper::setup(const CURLRequest& request, std::vector<uint8_t>* stream)
    {
        return setup(request, s_writeData<std::vector<uint8_t>>, stream);
    }

    bool CURLWrapper::setup(const CURLRequest& request, std::vector<char>* stream)
    {
        return setup(request, s_writeData<std::vector<char>>, stream);
    }

    bool CURLWrapper::setup(const CURLRequest& request, std::string* stream)
    {
        return setup(request, s_writeData<std::string>, stream);
    }
}
