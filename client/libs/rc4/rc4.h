//
//  rc4.h
//  Game
//
//  Created by gnef_jp on 14-7-10.
//
//

#ifndef __Game__rc4__
#define __Game__rc4__

#include <string>
#include <vector>

namespace rc4
{
    typedef	unsigned char u_char;
    struct Sbox
    {
        u_char	perm[256];
        u_char	index1;
        u_char	index2;
    };
    
    void init(Sbox *sbox, const std::string &key);
    void crypt(Sbox *sbox,
               const std::vector<char> &inputBuf,
               std::vector<char> *outputBuf);
}

#endif /* defined(__Game__rc4__) */
