//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

// ScopeGuard for C++11, Andrei Alexandrescu

#ifndef __CLOVER_SCOPEGUARD_H__
#define __CLOVER_SCOPEGUARD_H__

#include <functional>

namespace clover
{
    template <typename Fun>
    class ScopeGuard
    {
    public:
        ScopeGuard(Fun&& f) : _fun(std::forward<Fun>(f)), _active(true)
        {
        }

        ~ScopeGuard()
        {
            if (_active)
            {
                _fun();
            }
        }

        void dismiss()
        {
            _active = false;
        }

        ScopeGuard() = delete;
        ScopeGuard(const ScopeGuard&) = delete;
        ScopeGuard& operator=(const ScopeGuard&) = delete;

        ScopeGuard(ScopeGuard&& rhs) : _fun(std::move(rhs._fun)), _active(rhs._active)
        {
            rhs.dismiss();
        }

    private:
        Fun _fun;
        bool _active;
    };

    namespace detail
    {
        enum class ScopeGuardOnExit
        {
        };

        template <typename Fun>
        inline ScopeGuard<Fun> operator+(ScopeGuardOnExit, Fun&& fn)
        {
            return ScopeGuard<Fun>(std::forward<Fun>(fn));
        }
    }
}

// Helper macro
#define CLOVER_SCOPE_EXIT \
    auto __CLOVER_ANONYMOUS_VARIABLE(SCOPE_EXIT_STATE) = clover::detail::ScopeGuardOnExit() + [&]()

#define __CLOVER_CONCATENATE_IMPL(s1, s2) s1##s2
#define __CLOVER_CONCATENATE(s1, s2) __CLOVER_CONCATENATE_IMPL(s1, s2)

#ifdef __COUNTER__
#define __CLOVER_ANONYMOUS_VARIABLE(str) __CLOVER_CONCATENATE(str, __COUNTER__)
#else
#define __CLOVER_ANONYMOUS_VARIABLE(str) __CLOVER_CONCATENATE(str, __LINE__)
#endif

#endif
