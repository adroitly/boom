//
//  NetDataChange.h
//  boom
//
//  Created by PatGame on 15/8/10.
//
//

#ifndef __boom__NetDataChange__
#define __boom__NetDataChange__

#include <netinet/in.h>
#include <assert.h>

namespace NetDataChange
{
    template<typename T>
    T HostToNet(T data)
    {
        int typeSize = sizeof(T);
        if (2 == typeSize)
            return htons(data);
        else if (4 == typeSize)
            return htonl(data);
        assert(false);
        return 0;
    }
    
    template<typename T>
    T NetToHost(T data)
    {
        int typeSize = sizeof(T);
        if (2 == typeSize)
            return ntohs(data);
        else if (4 == typeSize)
            return ntohl(data);
        assert(false);
        return 0;
    }
}

#endif /* defined(__boom__NetDataChange__) */
