//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_CFSCOPERELEASE_H__
#define __FLA_CFSCOPERELEASE_H__

#include <boost/preprocessor.hpp>
#include <boost/noncopyable.hpp>

namespace fla
{
    class ScopeRelease : boost::noncopyable
    {
    public:
        ScopeRelease(CFTypeRef ref) : _ref(ref)
        {
        }
        
        ~ScopeRelease()
        {
            if (_ref)
            {
                CFRelease(_ref);
            }
        }
        
    private:
        CFTypeRef _ref;
    };
    
#define CF_SCOPE_RELEASE(ref) ScopeRelease BOOST_PP_CAT(RELEASE, __LINE__)(ref)
}


#endif
