//
//  rc4.cpp
//  Game
//
//  Created by gnef_jp on 14-7-10.
//
//

#include "rc4.h"

namespace rc4
{
    static void swap_bytes(u_char *a, u_char *b)
    {
        u_char temp;
        
        temp = *a;
        *a = *b;
        *b = temp;
    }
    
    /*
     * Initialize an RC4 state buffer using the supplied key,
     * which can have arbitrary length.
     */
    void init(Sbox *sbox, const std::string &key)
    {
        u_char j;
        int i;
        
        /* Initialize state with identity permutation */
        for (i = 0; i < 256; i++)
            sbox->perm[i] = (u_char)i;
        sbox->index1 = 0;
        sbox->index2 = 0;
        
        /* Randomize the permutation using key data */
        for (j = i = 0; i < 256; i++) {
            j += sbox->perm[i] + key[i % key.length()];
            swap_bytes(&sbox->perm[i], &sbox->perm[j]);
        }
    }
    
    /*
     * Encrypt some data using the supplied RC4 state buffer.
     * The input and output buffers may be the same buffer.
     * Since RC4 is a stream cypher, this function is used
     * for both encryption and decryption.
     */
    void crypt(Sbox *sbox,
               const std::vector<char> &inputBuf,
               std::vector<char> *outputBuf)
    {
        int i;
        u_char j;
        
        for (i = 0; i < inputBuf.size(); i++) {
            
            /* Update modification indicies */
            sbox->index1++;
            sbox->index2 += sbox->perm[sbox->index1];
            
            /* Modify permutation */
            swap_bytes(&sbox->perm[sbox->index1],
                       &sbox->perm[sbox->index2]);
            
            /* Encrypt/decrypt next byte */
            j = sbox->perm[sbox->index1] + sbox->perm[sbox->index2];
            u_char tmpChar = inputBuf[i];
            outputBuf->push_back(tmpChar ^ sbox->perm[j]);
        }
    }
}




