//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#include "fla_ZipUtils.h"
#include <zlib.h>

namespace fla
{
    clover::Data data_zipUncompress(const uint8_t* zlibData, size_t zlibLength)
    {
        clover::Data outBytes;
        if (zlibLength <= 0)
        {
            return outBytes;
        }

        size_t full_length = zlibLength;
        outBytes.resize(full_length * 2);

        z_stream d_stream;  // decompression stream
        d_stream.next_in = (Bytef*)zlibData;
        d_stream.avail_in = (uInt)full_length;
        d_stream.total_out = 0;
        d_stream.zalloc = Z_NULL;
        d_stream.zfree = Z_NULL;

        if (inflateInit2(&d_stream, (15 + 32)) != Z_OK)
        {
            return outBytes;
        }

        bool done = false;
        while (!done)
        {
            if (d_stream.total_out >= outBytes.size())
            {
                outBytes.resize(outBytes.size() * 2);
            }
            d_stream.next_out = &outBytes[0] + d_stream.total_out;
            d_stream.avail_out = (uInt)(outBytes.size() - d_stream.total_out);
            // Inflate another chunk.
            int status = inflate(&d_stream, Z_NO_FLUSH);
            if (status == Z_STREAM_END)
            {
                done = true;
            }
            else if (status != Z_OK)
            {
                break;
            }
        }

        inflateEnd(&d_stream);

        if (done)
        {
            outBytes.resize(d_stream.total_out);
        }
        return std::move(outBytes);
    }

    clover::Data data_zipCompress(const uint8_t* bytes, size_t len)
    {
        clover::Data zipData;
        if (bytes == nullptr || len == 0)
        {
            return zipData;
        }

        z_stream zlibStreamStruct;
        zlibStreamStruct.zalloc = Z_NULL;          // Set zalloc, zfree, and opaque to Z_NULL so
        zlibStreamStruct.zfree = Z_NULL;           // that when we call deflateInit2 they will be
        zlibStreamStruct.opaque = Z_NULL;          // updated to use default allocation functions.
        zlibStreamStruct.total_out = 0;            // Total number of output bytes produced so far
        zlibStreamStruct.next_in = (Bytef*)bytes;  // Pointer to input bytes
        zlibStreamStruct.avail_in = (uInt)len;     // Number of input bytes left to process

        int initError = deflateInit2(&zlibStreamStruct,
                                     Z_DEFAULT_COMPRESSION,
                                     Z_DEFLATED,
                                     (15 + 16),
                                     8,
                                     Z_DEFAULT_STRATEGY);
        if (initError != Z_OK)
        {
            return zipData;
        }

        // Create output memory buffer for compressed data. The zlib
        // documentation states that
        // destination buffer size must be at least 0.1% larger than avail_in
        // plus 12 bytes.
        zipData.resize(len * 1.01 + 12);

        int deflateStatus;
        do
        {
            // Store location where next byte should be put in next_out
            zlibStreamStruct.next_out = &zipData[0] + zlibStreamStruct.total_out;

            // Calculate the amount of remaining free space in the output buffer
            // by subtracting the number of bytes that have been written so far
            // from the buffer's total capacity
            zlibStreamStruct.avail_out = (uInt)(zipData.size() - zlibStreamStruct.total_out);
            deflateStatus = deflate(&zlibStreamStruct, Z_FINISH);

        } while (deflateStatus == Z_OK);

        // Check for zlib error and convert code to usable error message if
        // appropriate
        if (deflateStatus != Z_STREAM_END)
        {
            deflateEnd(&zlibStreamStruct);
            return clover::Data();
        }

        deflateEnd(&zlibStreamStruct);
        zipData.resize(zlibStreamStruct.total_out);

        return zipData;
    }
}
