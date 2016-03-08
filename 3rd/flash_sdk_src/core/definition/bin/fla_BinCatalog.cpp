//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_BinCatalog.h"

namespace fla
{
    void BinCatalog::writeToData(bin::Data& data) const
    {
        // 个数
        bin::writeUI16(data, _IdMap.size());
        for (auto& iter : _IdMap)
        {
            auto& item = *iter.second;
            bin::writeUI16(data, item.Id);
            bin::writeString(data, item.name);
            bin::writeUI32(data, item.offset);
        }
    }

    void BinCatalog::readData(const uint8_t*& ptr)
    {
        size_t numOfItems = bin::readUI16(ptr);
        for (size_t i = 0; i < numOfItems; i++)
        {
            uint16_t Id = bin::readUI16(ptr);
            std::string name = bin::readString(ptr);
            uint32_t offset = bin::readUI32(ptr);
            addItem(Id, name, offset);
        }
    }

    int BinCatalog::findOffset(int Id) const
    {
        auto iter = _IdMap.find(Id);
        if (iter != _IdMap.end())
        {
            return iter->second->offset;
        }
        return NotFound;
    }

    int BinCatalog::findOffset(const std::string& name) const
    {
        auto iter = _nameMap.find(name);
        if (iter != _nameMap.end())
        {
            return iter->second->offset;
        }
        return NotFound;
    }

    int BinCatalog::findId(const std::string& name) const
    {
        auto iter = _nameMap.find(name);
        if (iter != _nameMap.end())
        {
            return iter->second->Id;
        }
        return NotFound;
    }

    void BinCatalog::clearAllItems()
    {
        _IdMap.clear();
        _nameMap.clear();
    }

    bool BinCatalog::isEmpty() const
    {
        return _IdMap.empty();
    }

    void BinCatalog::addItem(int Id, int offset)
    {
        addItem(Id, std::string(""), offset);
    }

    void BinCatalog::addItem(int Id, const std::string& name, int offset)
    {
        auto item = Item::create(Id, offset, name);
        _IdMap[Id] = item;
        if (!name.empty())
        {
            _nameMap[name] = item;
        }
    }
}
