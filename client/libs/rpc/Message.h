//
//  Message.h
//  boom
//
//  Created by PatGame on 15/8/25.
//
//

#ifndef __boom__Message__
#define __boom__Message__

#include <stdlib.h>
#include "NetDataChange.h"
#include "clover/IntrusiveObject.h"
#include "libra/libra_socket.h"
#include "libra/libra_membuf.h"
#include <list>
#include <mutex>

namespace rpc
{
    typedef uint32_t PackageHeadDataType;           // 包头数据类型
    inline static int s_headPackageNumber()
    {
        return sizeof(PackageHeadDataType);
    }
    
    inline static void s_setHeadSize(uint8_t* data, PackageHeadDataType s)
    {
        s = NetDataChange::HostToNet(s);
        *reinterpret_cast<PackageHeadDataType*>(data) = s;
    }
    
    inline static PackageHeadDataType s_getHeadSize(uint8_t* data)
    {
        PackageHeadDataType s = *reinterpret_cast<PackageHeadDataType*>(data);
        return NetDataChange::NetToHost(s);
    }
    
    namespace
    {
        class Message : public clover::IntrusiveObject<Message>
        {
        public:
            static Message::Ptr pack(uint8_t* raw_data, size_t raw_size)
            {
                Message::Ptr msg = Message::Ptr(new Message());
                msg->doPack(raw_data, raw_size);
                return msg;
            }
            
            static Message::Ptr unpack(uint8_t* packed_data, size_t packed_size)
            {
                Message::Ptr msg = Message::Ptr(new Message());
                msg->doUnpack(packed_data, packed_size);
                return msg;
            }
            
            void send(libra_socket& socket)
            {
                libra_socket_write(&socket, _packedData, _packedSize);
            }
            
            uint8_t* getData() const
            {
                return _packedData + s_headPackageNumber();
            }
            
            size_t getSize() const
            {
                return _packedSize - s_headPackageNumber();
            }
            
            ~Message();
            Message();
            
        private:
            void doPack(uint8_t* raw_data, size_t raw_size);
            void doUnpack(uint8_t* packed_data, size_t packed_size);
            
        private:
            size_t _packedSize;
            uint8_t* _packedData;
        };
        
        Message::Message()
        {
            _packedSize = 0;
            _packedData = nullptr;
        }
        
        Message::~Message()
        {
            free(_packedData);
        }
        
        void Message::doPack(uint8_t* raw_data, size_t raw_size)
        {
            assert(_packedData == nullptr);
            _packedSize = raw_size + s_headPackageNumber();
            _packedData = (uint8_t*)malloc(_packedSize);
            s_setHeadSize(_packedData, (PackageHeadDataType)raw_size);
            memcpy(_packedData + s_headPackageNumber(), raw_data, raw_size);
        }
        
        void Message::doUnpack(uint8_t* packed_data, size_t packed_size)
        {
            assert(_packedData == nullptr);
            _packedSize = packed_size;
            _packedData = (uint8_t*)malloc(_packedSize);
            memcpy(_packedData, packed_data, packed_size);
            assert(s_getHeadSize(_packedData) == _packedSize - s_headPackageNumber());
        }
        
        typedef std::mutex Mutex;
        typedef std::lock_guard<Mutex> LockGuard;
        
        struct MessageQueue
        {
            Message::Ptr pop();
            void push(const Message::Ptr& msg);
            
            std::list<Message::Ptr> list;
            mutable Mutex mutex;
        };
        
        Message::Ptr MessageQueue::pop()
        {
            LockGuard lock(mutex);
            if (!list.empty())
            {
                auto msg = list.front();
                list.pop_front();
                return msg;
            }
            return nullptr;
        }
        
        void MessageQueue::push(const Message::Ptr& msg)
        {
            LockGuard lock(mutex);
            list.push_back(msg);
        }
        
        class ReadBuffer
        {
        public:
            ReadBuffer();
            ~ReadBuffer();
            void push(void* data, size_t size);
            Message::Ptr pop();
            
        private:
            libra_membuf _buffer;
        };
        
        ReadBuffer::ReadBuffer()
        {
            membuf_init(&_buffer, nullptr, 1024);
        }
        
        ReadBuffer::~ReadBuffer()
        {
            membuf_finish(&_buffer);
        }
        
        void ReadBuffer::push(void* data, size_t size)
        {
            membuf_push(&_buffer, data, size);
        }
        
        Message::Ptr ReadBuffer::pop()
        {
            auto bufSize = membuf_size(&_buffer);
            if (bufSize < s_headPackageNumber())
            {
                return Message::Ptr();
            }
            
            auto* ptr = (uint8_t*)membuf_ptr(&_buffer, 0);
            auto size = s_getHeadSize(ptr);
            auto packedSize = size + s_headPackageNumber();
            if (packedSize <= bufSize)
            {
                auto msg = Message::unpack(ptr, packedSize);
                membuf_earse(&_buffer, 0, packedSize);
                return msg;
            }
            return Message::Ptr();
        }
    }
}


#endif /* defined(__boom__Message__) */
