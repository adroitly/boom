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

#include "lua_network.h"
#include "../HttpClient.h"
#include <boost/scope_exit.hpp>
#include <boost/format.hpp>

#if LUA_VERSION_NUM == 501
#define lua_rawlen lua_objlen
#endif

namespace network
{
    static inline void registry_setfield(lua_State* L, const std::string& key)
    {
        lua_setfield(L, LUA_REGISTRYINDEX, key.c_str());
    }
    
    static void inline registry_getfield(lua_State* L, const std::string& key)
    {
        lua_getfield(L, LUA_REGISTRYINDEX, key.c_str());
    }
    
    static uint64_t lua_to_uint64(lua_State* L, int idx)
    {
        if (lua_type(L, idx) == LUA_TSTRING)
        {
            size_t len;
            const char* str = lua_tolstring(L, idx, &len);
            if (len == sizeof(uint64_t))
            {
                return *reinterpret_cast<const uint64_t*>(str);
            }
        }
        return 0;
    }
    
    static inline void lua_push_uint64(lua_State* L, uint64_t val)
    {
        const char* p = reinterpret_cast<const char*>(&val);
        lua_pushlstring(L, p, sizeof(val));
    }
    
    template <typename Fun>
    static void table_walk(lua_State* L, int idx, const Fun& fun)
    {
        lua_pushvalue(L, idx);
        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            int top = lua_gettop(L);
            const char* key = luaL_checkstring(L, top - 1);
            const char* value = luaL_checkstring(L, top);
            fun(key, value);
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
    }
    
    static bool s_parse_request_table(HttpRequest& request, lua_State* L, int idx)
    {
        // url
        lua_getfield(L, idx, "url");
        if (lua_isnil(L, -1))
        {
            lua_pop(L, 1);
            return false;
        }
        request.setUrl(luaL_checkstring(L, -1));
        lua_pop(L, 1);
        
        // tag
        lua_getfield(L, idx, "tag");
        if (lua_isnumber(L, -1))
        {
            request.setTag((int)lua_tonumber(L, -1));
        }
        lua_pop(L, 1);
        
        // timeout
        lua_getfield(L, idx, "timeout");
        if (lua_isnumber(L, -1))
        {
            request.setTimeout(lua_tonumber(L, -1));
        }
        lua_pop(L, 1);
        
        // params
        lua_getfield(L, idx, "params");
        if (lua_istable(L, -1))
        {
            table_walk(L,
                       -1,
                       [&](const char* key, const char* value)
                       {
                           request.addParameter(key, value);
                       });
        }
        lua_pop(L, 1);
        
        // headers"
        lua_getfield(L, idx, "headers");
        if (lua_istable(L, -1))
        {
            table_walk(L,
                       -1,
                       [&](const char* key, const char* value)
                       {
                           request.addHeader(key, value);
                       });
        }
        lua_pop(L, 1);
        
        return true;
    }
    
    static bool s_parse_request_string(HttpRequest& request, lua_State* L, int idx)
    {
        request.setUrl(lua_tostring(L, idx));
        return true;
    }
    
    static bool s_parseRequest(HttpRequest& request, lua_State* L)
    {
        auto type = lua_type(L, 1);
        if (type == LUA_TSTRING)
        {
            return s_parse_request_string(request, L, 1);
        }
        
        if (type == LUA_TTABLE)
        {
            return s_parse_request_table(request, L, 1);
        }
        return false;
    }
    
    static inline std::string s_keyFromId(uint64_t Id)
    {
        auto format = boost::format("network.http.%1%") % Id;
        return format.str();
    }
    
    static void lua_push_response(lua_State* L, const HttpResponse& response)
    {
        lua_newtable(L);
        if (response.getDataBytes())
        {
            lua_pushlstring(L, response.getDataBytes(), response.getDataSize());
            lua_setfield(L, -2, "data");
        }
        
        lua_pushinteger(L, response.getResponseCode());
        lua_setfield(L, -2, "code");
        
        lua_pushinteger(L, response.getRequestTag());
        lua_setfield(L, -2, "tag");
        
        lua_push_uint64(L, response.getRequestId());
        lua_setfield(L, -2, "id");
    }
    
    static void lua_push_result_type(lua_State* L, HttpResultType type)
    {
        switch (type)
        {
            case HttpResultType::Finish:
                lua_pushstring(L, "finish");
                break;
                
            case HttpResultType::Cancel:
                lua_pushstring(L, "cancel");
                break;
                
            case HttpResultType::Timeout:
                lua_pushstring(L, "timeout");
                break;
                
            case HttpResultType::Error:
                lua_pushstring(L, "error");
                break;
                
            default:
                break;
        }
    }
    
    static void s_callback(lua_State* L, const HttpResponse& response, HttpResultType type)
    {
        auto key = s_keyFromId(response.getRequestId());
        registry_getfield(L, key);
        if (lua_isfunction(L, -1))
        {
            lua_push_response(L, response);
            lua_push_result_type(L, type);
            lua_execute_function(L, 2);
        }
        lua_pushnil(L);
        registry_setfield(L, key);
    }
    
    static int http_start(lua_State* L, HttpMethod method)
    {
        HttpRequest request;
        request.setMethod(method);
        
        if (!s_parseRequest(request, L))
        {
            return 0;
        }
        
        luaL_checktype(L, 2, LUA_TFUNCTION);
        auto realId = HttpClient::getInstance().start(request,
                                                      [=](const HttpResponse& response, HttpResultType type)
                                                      {
                                                          s_callback(L, response, type);
                                                      });
        if (realId == 0)
        {
            return 0;
        }
        
        lua_pushvalue(L, 2);
        registry_setfield(L, s_keyFromId(realId));
        lua_push_uint64(L, realId);
        return 1;
    }
    
    static int http_get(lua_State* L)
    {
        return http_start(L, HttpMethod::Get);
    }
    
    static int http_post(lua_State* L)
    {
        return http_start(L, HttpMethod::Post);
    }
    
    static void http_cancel_id(lua_State* L, int idx)
    {
        uint64_t id = lua_to_uint64(L, idx);
        if (id != 0)
        {
            HttpClient::getInstance().cancelRequestId(id);
        }
    }
    
    static int http_cancel(lua_State* L)
    {
        if (lua_istable(L, 1))
        {
            size_t len = lua_rawlen(L, 1);
            for (size_t idx = 1; idx <= len; idx++)
            {
                lua_rawgeti(L, 1, (int)idx);
                http_cancel_id(L, -1);
                lua_pop(L, 1);
            }
        }
        else
        {
            http_cancel_id(L, 1);
        }
        return 0;
    }
    
    static int http_id_str(lua_State* L)
    {
        char buf[64];
        uint64_t id = lua_to_uint64(L, 1);
        sprintf(buf, "%lld", id);
        lua_pushstring(L, buf);
        return 1;
    }
    
    static int lua_open_http(lua_State* L)
    {
        luaL_Reg regs[] = {
            { "get",    http_get    },
            { "send",    http_get    },
            { "post",   http_post   },
            { "cancel", http_cancel },
            { "id_str", http_id_str },
        };
        
        lua_createtable(L, 0, sizeof(regs) / sizeof(regs[0]));
        for (auto& reg : regs)
        {
            lua_pushcfunction(L, reg.func);
            lua_setfield(L, -2, reg.name);
        }
        return 1;
    }
    
    int lua_open_network(lua_State* L)
    {
        lua_createtable(L, 0, 1);
        
        lua_open_http(L);
        lua_setfield(L, -2, "http");
        
        return 1;
    }
}
