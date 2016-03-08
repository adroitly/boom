//
//  CRC.h
//  boom
//
//  Created by PatGame on 15/8/10.
//
//

#ifndef boom_CRC_h
#define boom_CRC_h

namespace CRC
{
    
    static unsigned short get_crc16(const char *bufData, unsigned int buflen)
    {
        // 备注：这里是个坑，网上的源码是 unsigned short CRC = 0xffff;不是int类型
        // 如果数据包含浮点型就会与服务器验证不一致
        int CRC = 0xffff;
        int POLYNOMIAL = 0xa001;
        int i, j;
        
        if(bufData == NULL)
        {
            return -1;
        }
        
        if (buflen == 0)
        {
            return -1;
        }
        for (i = 0; i < buflen; i++)
        {
            CRC ^= bufData[i];
            for (j = 0; j < 8; j++)
            {
                if ((CRC & 0x0001) != 0)
                {
                    CRC >>= 1;
                    CRC ^= POLYNOMIAL;
                }
                else
                {
                    CRC >>= 1;
                }
            }
        }
        
//        printf("crc = %d, %d\n", CRC & 0x00ff, CRC >> 8);
        return CRC;
    }
}

#endif
