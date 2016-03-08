//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../FlaMoviePart.h"
#include "./fla_MoviePart.h"

FlaMoviePart::FlaMoviePart()
{
    _impl = nullptr;
}

FlaMoviePart::~FlaMoviePart()
{
    clover::intrusive_ptr_safe_release(_impl);
}

FlaMoviePart::FlaMoviePart(const FlaMoviePart& rhs) : FlaMoviePart(rhs._impl)
{
}

FlaMoviePart& FlaMoviePart::operator=(const FlaMoviePart& rhs)
{
    clover::intrusive_ptr_safe_assign(_impl, rhs._impl);
    return *this;
}

FlaMoviePart::FlaMoviePart(fla::MoviePart* impl)
{
    _impl = impl;
    clover::intrusive_ptr_safe_retain(_impl);
}

fla::MoviePart* FlaMoviePart::getRaw() const
{
    return _impl;
}

bool FlaMoviePart::isNull() const
{
    return _impl == nullptr;
}

void FlaMoviePart::hide()
{
    if (_impl)
    {
        _impl->hide();
    }
}

void FlaMoviePart::show()
{
    if (_impl)
    {
        _impl->show();
    }
}

void FlaMoviePart::replaceDefinition(const FlaDefinition& definition)
{
    if (_impl)
    {
        _impl->replaceDefinition(definition.getRaw());
    }
}

void FlaMoviePart::resetDefinition()
{
    if (_impl)
    {
        _impl->resetDefinition();
    }
}

bool FlaMoviePart::changeState(const std::string& name)
{
    if (_impl)
    {
        return _impl->changeState(name);
    }
    return false;
}

void FlaMoviePart::setTranslation(float tx, float ty)
{
    if (_impl)
    {
        return _impl->setTranslation(tx, ty);
    }
}

bool FlaMoviePart::changeState(int index)
{
    if (_impl)
    {
        return _impl->changeState(index);
    }
    return false;
}

FlaMoviePart FlaMoviePart::findMoviePart(int Id)
{
    FlaMoviePart part;
    if (_impl)
    {
        part = FlaMoviePart(_impl->findMoviePart(Id));
    }
    return part;
}

FlaMoviePart FlaMoviePart::findMoviePart(const std::string& name)
{
    FlaMoviePart part;
    if (_impl)
    {
        part = FlaMoviePart(_impl->findMoviePart(name));
    }
    return part;
}
