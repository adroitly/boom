//
//  fla_RefPtrVector.h
//  FlaPreview
//
//  Created by HJC on 15/4/2.
//  Copyright (c) 2015年 HJC. All rights reserved.
//

#ifndef __FLA_REFPTRVECTOR_H__
#define __FLA_REFPTRVECTOR_H__

#include "clover/ptr_vector.h"

namespace fla
{
    template <typename T>
    struct RefPtrVector
    {
        typedef clover::ptr_vector<T, clover::ptr_ref_policy<T>> type;
    };
    
    /*
     最开始的写法是
    template <typename T>
    struct PodRefPtrVector : public clover::pod_ptr_vector<T, clover::ptr_ref_policy<T>>
    {
    };
     但是这样写的话，在VC++中编译就不可以将PodRefPtrVector<T>放进union中，
     */
    
    template <typename T>
    struct PodRefPtrVector
    {
        typedef clover::pod_ptr_vector<T, clover::ptr_ref_policy<T>> type;
    };
}

#endif
