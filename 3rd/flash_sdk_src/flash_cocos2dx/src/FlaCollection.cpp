//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../FlaCollection.h"
#include "../../core/definition/bin/fla_BinaryReader.h"
#include "../../core/definition/fla_Definition.h"
#include "clover/IntrusiveObject.h"
#include "../../core/definition/fla_Collection.h"
#include "fla_Settings.h"

static inline FlaDefinition s_make(const fla::Definition::Ptr& root)
{
    return FlaDefinition(root.get());
}

FlaCollection::FlaCollection()
{
    _impl = nullptr;
}

fla::Collection* FlaCollection::getRaw() const
{
    return _impl;
}

FlaCollection::~FlaCollection()
{
    clover::intrusive_ptr_safe_release(_impl);
}

FlaCollection::FlaCollection(const FlaCollection& rhs)
{
    _impl = rhs._impl;
    clover::intrusive_ptr_safe_retain(_impl);
}

FlaCollection& FlaCollection::operator=(const FlaCollection& rhs)
{
    clover::intrusive_ptr_safe_assign(_impl, rhs._impl);
    return *this;
}

FlaCollection::FlaCollection(fla::Collection* impl)
{
    _impl = impl;
    clover::intrusive_ptr_safe_retain(_impl);
}

float FlaCollection::getFrameRate() const
{
    return _impl ? _impl->getFrameRate() : 24;
}

std::string FlaCollection::getDataMd5() const
{
    return _impl && _impl->rootDefinition() ? _impl->rootDefinition()->getDataInfo()->getMd5String() : "";
}

bool FlaCollection::isNull() const
{
    return !_impl;
}

static bool s_loadData(fla::BinaryReader& reader, const void* data, size_t dataLen, FlaErrorCode* error)
{
    fla::ErrorCode code = fla::ErrorCode::Success;
    if (!reader.loadData(data, dataLen, &code))
    {
        if (error)
        {
            *error = static_cast<FlaErrorCode>(code);
        }
        return false;
    }
    if (error)
    {
        *error = FlaErrorCode::Success;
    }
    return true;
}

void FlaCollection::walk(const std::function<void(const FlaDefinition& def)>& fun) const
{
    if (_impl)
    {
        _impl->walk([&](const fla::Definition::Ptr& def)
                    {
                        fun(s_make(def));
                    });
    }
}

void FlaCollection::walkName(const WalkFunType& fun) const
{
    if (_impl)
    {
        _impl->walkName([&](const fla::Definition::Ptr& def)
                        {
                            fun(s_make(def));
                        });
    }
}

void FlaCollection::walk(FlaMovieType movieType, const std::function<void(const FlaDefinition& def)>& fun) const
{
    if (_impl)
    {
        _impl->walk(static_cast<fla::DefinitionType>(movieType),
                    [&](const fla::Definition::Ptr& def)
                    {
                        fun(s_make(def));
                    });
    }
}

FlaCollection FlaCollection::loadData(const void* data, size_t dataLen, FlaErrorCode* error)
{
    fla::BinaryReader reader;
    reader.setCheckAuthorizedFunc(fla::settings::getCheckAuthorizedFunc());
    reader.setIgnorePlaceHolde(fla::settings::getIgnorePlaceHolde());
    if (s_loadData(reader, data, dataLen, error))
    {
        reader.readAllDefinitions();
        auto ptr = fla::Collection::create(reader.dict(), reader.getFrameRate(), reader.getRootId());
        return FlaCollection(ptr.get());
    }
    return FlaCollection();
}

FlaCollection FlaCollection::loadData(const void* data,
                                      size_t dataLen,
                                      const std::vector<int>& Ids,
                                      FlaErrorCode* error)
{
    fla::BinaryReader reader;
    reader.setCheckAuthorizedFunc(fla::settings::getCheckAuthorizedFunc());
    reader.setIgnorePlaceHolde(fla::settings::getIgnorePlaceHolde());
    if (s_loadData(reader, data, dataLen, error))
    {
        for (auto Id : Ids)
        {
            reader.readDefinition(Id);
        }
        auto ptr = fla::Collection::create(reader.dict(), reader.getFrameRate(), reader.getRootId());
        return FlaCollection(ptr.get());
    }
    return FlaCollection();
}

FlaCollection FlaCollection::loadData(const void* data,
                                      size_t dataLen,
                                      const std::vector<std::string>& names,
                                      FlaErrorCode* error)
{
    fla::BinaryReader reader;
    reader.setCheckAuthorizedFunc(fla::settings::getCheckAuthorizedFunc());
    reader.setIgnorePlaceHolde(fla::settings::getIgnorePlaceHolde());
    if (s_loadData(reader, data, dataLen, error))
    {
        for (auto name : names)
        {
            reader.readDefinition(name);
        }
        auto ptr = fla::Collection::create(reader.dict(), reader.getFrameRate(), reader.getRootId());
        return FlaCollection(ptr.get());
    }
    return FlaCollection();
}

FlaDefinition FlaCollection::rootDefinition() const
{
    return _impl ? s_make(_impl->rootDefinition()) : FlaDefinition();
}

FlaDefinition FlaCollection::findDefinition(const std::string& name) const
{
    return _impl ? s_make(_impl->findDefinition(name)) : FlaDefinition();
}

FlaDefinition FlaCollection::findDefinition(int ID) const
{
    return _impl ? s_make(_impl->findDefinition(ID)) : FlaDefinition();
}

bool FlaCollection::isUnique() const
{
    return _impl && _impl->isUnique();
}
