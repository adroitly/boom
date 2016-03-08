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

#ifndef __CLOVER_DATA_H__
#define __CLOVER_DATA_H__

#include <vector>
#include <string>
#include <cstdint>

namespace clover
{
    class Data
    {
    public:
        typedef uint8_t byte_t;
        static Data loadFromFile(const std::string& filePath);
        
        Data();
        Data(const Data& rhs);
        Data& operator = (const Data& rhs);
        
        Data(size_t size);
        ~Data();
        Data(Data&& rhs);
        
        void swap(Data& rhs);
        
        // 将数据写入文件
        bool writeToFile(const std::string& filePath) const;
        
        bool pushData(const void* data, size_t len);
                
        void resize(size_t size);
        void reserve(size_t size);
        void shrink_to_fit();
        void clear();
        
        const byte_t*  bytes() const           {   return _bytes;              }
        size_t          size() const            {   return _size;               }
        bool empty() const                      {   return size() == 0;         }
        
        const byte_t& operator[] (size_t idx) const   {   return _bytes[idx];  }
        byte_t& operator[] (size_t idx)        {   return _bytes[idx];         }
        
        const byte_t* begin() const            {   return _bytes;              }
        const byte_t* end() const              {   return _bytes + _size;      }
        
    private:
        void expandCapacity(size_t capacity);
        
    private:
        byte_t*    _bytes;
        size_t      _size;
        size_t      _capacity;
    };
    
    bool operator == (const Data& lhs, const Data& rhs);
    bool operator != (const Data& lhs, const Data& rhs);
}

#endif
