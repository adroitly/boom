//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_BINCATALOG__
#define __FLA_BINCATALOG__

#include <string>
#include <map>
#include <memory>
#include <iterator>
#include "fla_BinaryFormat.h"
#include "clover/IntrusiveObject.h"

namespace fla
{
    // 用于存放一个目录表，可以快速查找对应定义在文件中的位置（解压之后）
    // 每个目录为三项 (id, name, offset)
    // 表示 对应id 的定义，在文件偏移为offset的位置
    // 表示 名字为name的定义，在文件偏移为offset的位置，
    // 这样就可以通过，id或者name迅速定义，其中Id字段一定要有，name字段可以为空
    class BinCatalog
    {
    public:
        const static int NotFound = -1;

        // 加入目录项
        void addItem(int Id, const std::string& name, int offset);
        void addItem(int Id, int offset);

        // 找对对应的偏移, NotFound, 表示找不到
        int findOffset(int Id) const;
        int findOffset(const std::string& name) const;

        // 查找名字对应的Id, 找不到返回 NotFound
        int findId(const std::string& name) const;

        void clearAllItems();

        void writeToData(bin::Data& data) const;
        void readData(const uint8_t*& ptr);

        bool isEmpty() const;

    private:
        class Item : public clover::IntrusiveObject<Item>
        {
        public:
            static Item::Ptr create(int Id, int offset, const std::string& name)
            {
                return Item::Ptr(new Item(Id, offset, name), false);
            }
            
            int Id;
            int offset;
            std::string name;
            
        private:
            Item(int Id_, int offset_, const std::string& name_)
            : Id(Id_), offset(offset_), name(name_)
            {
            }
        };
        std::map<int, Item::Ptr> _IdMap;            // 从Id查找对应项
        std::map<std::string, Item::Ptr> _nameMap;  // 从名字查找对应项目
    };
}

#endif
