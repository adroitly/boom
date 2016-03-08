/*
 The MIT License (MIT)
 
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

#include "ObjWeakable.h"
#include <algorithm>

namespace ccex
{
    typedef weak_detail::unique_id unique_id;

    struct WeakTable
    {
    public:
        struct Item
        {
            Item(const unique_id& Id_, Object* obj_) : Id(Id_), obj(obj_)
            {
            }
            unique_id Id;
            Object* obj;
        };

        static WeakTable* getInstance()
        {
            static WeakTable table;
            return &table;
        }

        unique_id add(Object* obj)
        {
            _table.push_back(Item(_nextId, obj));
            _nextId = _nextId + 1;

            return _table.back().Id;
        }

        void remove(const unique_id& Id)
        {
            auto iter = findItem(Id);
            if (iter != _table.end())
            {
                _table.erase(iter);
            }
        }

        Object* lock(const unique_id& Id) const
        {
            auto iter = const_cast<WeakTable*>(this)->findItem(Id);
            if (iter != _table.end())
            {
                return iter->obj;
            }
            return nullptr;
        }

        typedef std::vector<Item>::iterator iterator;

    private:
        iterator findItem(const unique_id& Id);
        WeakTable() : _nextId(1)
        {
        }

    private:
        unique_id _nextId;
        std::vector<Item> _table;  // 已排序
    };

    WeakTable::iterator WeakTable::findItem(const unique_id& Id)
    {
        auto comp = [=](const Item& item, const unique_id& Id)
        { return item.Id < Id; };

        auto iter = std::lower_bound(_table.begin(), _table.end(), Id, comp);
        if (iter != _table.end() && iter->Id == Id)
        {
            return iter;
        }
        return _table.end();
    }

    namespace weak_detail
    {
        unique_id weaktable_add(Object* obj)
        {
            return WeakTable::getInstance()->add(obj);
        }

        void weaktable_remove(const unique_id& Id)
        {
            WeakTable::getInstance()->remove(Id);
        }

        Object* weaktable_lock(const unique_id& Id)
        {
            if (Id == weaktable_nullId())
            {
                return nullptr;
            }
            return WeakTable::getInstance()->lock(Id);
        }
    }
}
