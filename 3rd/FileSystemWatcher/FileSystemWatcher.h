/*
 The MIT License (MIT)
 
 Copyright (c) 2015 HJC
 
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

#ifndef __CLOVER_FILESYSTEMWATCHER_H__
#define __CLOVER_FILESYSTEMWATCHER_H__

#include <dispatch/dispatch.h>
#include <string>
#include <vector>
#include <functional>

namespace clover
{
    enum
    {
        WatchFlags_Delete = DISPATCH_VNODE_DELETE,
        WatchFlags_Write = DISPATCH_VNODE_WRITE,
        WatchFlags_Extend = DISPATCH_VNODE_EXTEND,
        WatchFlags_Rename = DISPATCH_VNODE_RENAME,
    };

    struct FileWatchInfo
    {
        std::string path;
        unsigned long flags;
        uint64_t Id;
    };

    class FileSystemWatcher
    {
    public:
        typedef uint64_t Id;
        static uint64_t nullId;

        typedef std::function<void(const FileWatchInfo& info)> CallbackType;
        static FileSystemWatcher* getInstance();

        Id peekNextId() const;
        Id watchFile(const std::string& path, const CallbackType& callback);
        bool hasPath(const std::string& path);

        void cancel(const Id& Id_);
        void cancel(const std::string& file);
        void cancelAll();

    private:
        FileSystemWatcher();
        void doFileChanged(const char* path, unsigned long flags);
        struct Record
        {
            struct Item
            {
                Id Id_;
                CallbackType callback;
            };
            std::string path;
            std::vector<Item> items;
            dispatch_source_t source;
        };
        Id genNextId();

        std::vector<Record>::iterator findRecord(const std::string& path);

    private:
        Id _nextId;
        std::vector<Record> _records;
    };
}

#endif
