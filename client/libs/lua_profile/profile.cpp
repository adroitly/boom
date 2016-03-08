//=============================================================================
//  easy-lua
//
//  Copyright (C) 2014 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#include "profile.h"
#include <time.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "libra/libra_strbuf.h"
#include <set>

namespace easy_lua
{
    struct CallInfo
    {
        int count;
        int line;
        std::string source;
        std::string name;
        clock_t total_clock;
        clock_t last_clock;
    };

    static std::unordered_map<std::string, CallInfo> s_calls;
    static std::set<std::string> s_watchKeys;
    static bool s_running = false;

    static std::string s_key(lua_Debug* debug)
    {
        strbuf_init_stack(buf, 128);
        strbuf_push_string(buf, debug->source);
        strbuf_push_uint32(buf, debug->linedefined);
        auto result = strbuf_cstr(buf);
        strbuf_finish(buf);
        return result;
    }

    static void s_hook_lua_call(lua_State* L, lua_Debug* debug)
    {
        (void)L;
        auto key = s_key(debug);
        auto iter = s_calls.find(key);
        if (iter != s_calls.end() && iter->first == key)
        {
            iter->second.count++;
            iter->second.last_clock = clock();
        }
        else
        {
            if (!s_watchKeys.empty() && s_watchKeys.count(key) == 0)
            {
                return;
            }

            CallInfo info;
            info.count = 1;
            info.source = debug->source;
            info.line = debug->linedefined;
            if (debug->name)
            {
                info.name = debug->name;
            }
            info.total_clock = 0;
            info.last_clock = clock();
            s_calls.insert(iter, std::make_pair(key, info));
        }
    }

    static void s_hook_lua_return(lua_State* L, lua_Debug* debug)
    {
        (void)L;
        auto key = s_key(debug);
        auto iter = s_calls.find(key);
        if (iter != s_calls.end() && iter->first == key)
        {
            auto& info = iter->second;
            auto this_clock = clock() - info.last_clock;
            info.total_clock += this_clock;
            info.last_clock = 0;
        }
    }

    static void s_hook(lua_State* L, lua_Debug* debug)
    {
        if (lua_getstack(L, 2, debug) != 0)
        {
            lua_getinfo(L, "Sn", debug);
            if (!strcmp(debug->what, "Lua"))
            {
                if (LUA_HOOKCALL == debug->event)
                {
                    s_hook_lua_call(L, debug);
                }
                else if (LUA_HOOKRET == debug->event)
                {
                    s_hook_lua_return(L, debug);
                }
            }
        }
    }

    static int start(lua_State* L)
    {
        s_calls.clear();
        if (!s_running)
        {
            lua_sethook(L, s_hook, LUA_MASKCALL | LUA_MASKRET, 0);
            s_running = true;
        }
        return 0;
    }

    static void s_output(const std::unordered_map<std::string, CallInfo>& calls)
    {
        std::vector<CallInfo> vec;
        for (auto& iter : calls)
        {
            vec.push_back(iter.second);
        }

        std::sort(vec.begin(),
                  vec.end(),
                  [](const CallInfo& l, const CallInfo& r)
                  {
                      return l.total_clock > r.total_clock;
                  });

        printf("\n\n==================== profile output ====================\n");
        size_t size = std::min<size_t>(vec.size(), 30);
        for (size_t i = 0; i < size; i++)
        {
            if (i % 10 == 0)
            {
                printf("%d\n", (int)i);
            }
            auto& v = vec[i];
            auto each = (double)v.total_clock / v.count;
            printf("total_clock: %d, count: %d, each_clock: %f, [%s] in [%s:%d]\n",
                   (int)v.total_clock,
                   v.count,
                   each,
                   v.name.c_str(),
                   v.source.c_str(),
                   v.line);
        }
    }

    static int stop(lua_State* L)
    {
        if (s_running)
        {
            lua_sethook(L, NULL, 0, 0);
            s_running = false;
            s_output(s_calls);
        }
        return 0;
    }

    static int watch_funs(lua_State* L)
    {
        s_watchKeys.clear();
        luaL_checktype(L, 1, LUA_TTABLE);
        int n = (int)lua_rawlen(L, 1);
        for (int i = 1; i <= n; i++)
        {
            lua_rawgeti(L, 1, i);
            if (lua_isfunction(L, -1))
            {
                lua_Debug debug;
                lua_getinfo(L, ">Sn", &debug);
                auto key = s_key(&debug);
                s_watchKeys.insert(key);
            }
            else
            {
                lua_pop(L, 1);
            }
        }
        return 1;
    }

    int lua_open_profile(lua_State* L)
    {
        lua_newtable(L);

        lua_pushcfunction(L, start);
        lua_setfield(L, -2, "start");

        lua_pushcfunction(L, stop);
        lua_setfield(L, -2, "stop");

        lua_pushcfunction(L, watch_funs);
        lua_setfield(L, -2, "watch_funs");

        return 1;
    }
}