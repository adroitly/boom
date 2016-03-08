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

#include "FileSystemWatcher.h"
#include <stdlib.h>

static dispatch_source_t s_watchFile(const std::string& path, void (^callback)(const char* path, unsigned long flags))
{
    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    int file = open(path.c_str(), O_EVTONLY);
    unsigned int mask = DISPATCH_VNODE_DELETE | DISPATCH_VNODE_WRITE | DISPATCH_VNODE_EXTEND | DISPATCH_VNODE_RENAME;
    auto source = dispatch_source_create(DISPATCH_SOURCE_TYPE_VNODE, file, mask, queue);

    const char* tmpPath = strdup(path.c_str());
    dispatch_source_set_event_handler(source,
                                      ^{
                                        unsigned long flags = dispatch_source_get_data(source);
                                        if (flags)
                                        {
                                            dispatch_async(dispatch_get_main_queue(),
                                                           ^{
                                                             callback(tmpPath, flags);
                                                           });
                                        }
                                      });

    auto closeFile = ^(void) {
      free((void*)tmpPath);
      close(file);
    };

    dispatch_source_set_cancel_handler(source, closeFile);
    dispatch_resume(source);
    return source;
}

namespace clover
{
    FileSystemWatcher* FileSystemWatcher::getInstance()
    {
        static FileSystemWatcher s_watcher;
        return &s_watcher;
    }

    uint64_t FileSystemWatcher::nullId = 0;

    FileSystemWatcher::FileSystemWatcher()
    {
        _nextId = FileSystemWatcher::nullId;
    }

    FileSystemWatcher::Id FileSystemWatcher::peekNextId() const
    {
        return _nextId + 1;
    }

    FileSystemWatcher::Id FileSystemWatcher::genNextId()
    {
        _nextId++;
        return _nextId;
    }

    std::vector<FileSystemWatcher::Record>::iterator FileSystemWatcher::findRecord(const std::string& path)
    {
        auto iter = std::lower_bound(_records.begin(),
                                     _records.end(),
                                     path,
                                     [](const Record& record, const std::string& path)
                                     {
                                         return record.path < path;
                                     });
        return iter;
    }

    void FileSystemWatcher::doFileChanged(const char* path, unsigned long flags)
    {
        auto iter = findRecord(path);
        if (iter != _records.end() && iter->path == path)
        {
            // cancel的时候会清除path, 需要先复制
            FileWatchInfo info;
            info.path = path;
            info.flags = flags;

            dispatch_source_cancel(iter->source);
            dispatch_release(iter->source);
            iter->source = s_watchFile(path,
                                       ^(const char* tmpPath, unsigned long flags) {
                                         this->doFileChanged(tmpPath, flags);
                                       });

            // 遍历时候有可能修改数组，先复制一份
            auto items = iter->items;
            for (auto& item : items)
            {
                info.Id = item.Id_;
                item.callback(info);
            }
        }
    }

    bool FileSystemWatcher::hasPath(const std::string& path)
    {
        auto iter = findRecord(path);
        return iter != _records.end() && iter->path == path;
    }

    FileSystemWatcher::Id FileSystemWatcher::watchFile(const std::string& path, const CallbackType& callback)
    {
        auto iter = findRecord(path);

        Record::Item item = { genNextId(), callback };
        if (iter != _records.end() && iter->path == path)
        {
            iter->items.push_back(item);
        }
        else
        {
            dispatch_source_t source = s_watchFile(path,
                                                   ^(const char* tmpPath, unsigned long flags) {
                                                     this->doFileChanged(tmpPath, flags);
                                                   });
            Record record;
            record.path = path;
            record.source = source;
            record.items.push_back(item);

            _records.insert(iter, record);
        }
        return item.Id_;
    }

    void FileSystemWatcher::cancelAll()
    {
        for (auto& record : _records)
        {
            dispatch_source_cancel(record.source);
            dispatch_release(record.source);
        }
        _records.clear();
    }

    void FileSystemWatcher::cancel(const std::string& path)
    {
        auto iter = findRecord(path);
        if (iter != _records.end() && iter->path == path)
        {
            dispatch_source_cancel(iter->source);
            dispatch_release(iter->source);
            _records.erase(iter);
        }
    }

    void FileSystemWatcher::cancel(const Id& Id_)
    {
        for (auto iter = _records.begin(); iter != _records.end(); ++iter)
        {
            auto& items = iter->items;
            auto itemIter = std::find_if(items.begin(),
                                         items.end(),
                                         [&](const Record::Item& item)
                                         {
                                             return item.Id_ == Id_;
                                         });
            if (itemIter != items.end())
            {
                if (items.size() == 1)
                {
                    dispatch_source_cancel(iter->source);
                    dispatch_release(iter->source);
                    _records.erase(iter);
                }
                else
                {
                    items.erase(itemIter);
                }
                break;
            }
        }
    }
}
