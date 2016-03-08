//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLACOLLECTION_H__
#define __FLACOLLECTION_H__

#include "FlaDefinition.h"
#include <memory>

namespace fla
{
    class Collection;
}

// 从文件中读取多个定义
class FlaCollection
{
public:
    // 三个读取函数
    static FlaCollection loadData(const void* data, size_t dataLen, FlaErrorCode* error);
    static FlaCollection loadData(const void* data, size_t dataLen, const std::vector<int>& Ids, FlaErrorCode* error);
    static FlaCollection loadData(const void* data, size_t dataLen, const std::vector<std::string>& names, FlaErrorCode* error);

    FlaCollection();
    ~FlaCollection();
    FlaCollection(const FlaCollection& rhs);
    FlaCollection& operator=(const FlaCollection& rhs);
    
    explicit FlaCollection(fla::Collection* impl);
    fla::Collection* getRaw() const;

    // 用于判断是否为空
    bool isNull() const;

    // 根定义
    FlaDefinition rootDefinition() const;

    // 查找
    FlaDefinition findDefinition(const std::string& name) const;
    FlaDefinition findDefinition(int ID) const;

    float getFrameRate() const;
    
    std::string getDataMd5() const;

    // 遍历容器里面的定义
    typedef std::function<void(const FlaDefinition& def)> WalkFunType;

    void walk(const WalkFunType& fun) const;
    void walk(FlaMovieType movieType, const WalkFunType& fun) const;
    
    void walkName(const WalkFunType& fun) const;

    bool isUnique() const;

private:
    fla::Collection* _impl;
};

#endif
