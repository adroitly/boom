//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../FlaDefinition.h"
#include "../../core/definition/bin/fla_BinaryReader.h"
#include "../../core/definition/fla_DefinitionUtils.h"
#include "../../core/definition/fla_Definition.h"
#include "../../core/definition/fla_DefinitionAnimation.h"
#include "fla_cocos2d_Texture.h"
#include "fla_Settings.h"
#include "cocos2d_bridge.h"
using namespace cocos2d;

FlaDefinition::FlaDefinition(const FlaDefinition& rhs)
{
    _impl = rhs._impl;
    clover::intrusive_ptr_safe_retain(_impl);
}

FlaDefinition& FlaDefinition::operator=(const FlaDefinition& rhs)
{
    clover::intrusive_ptr_safe_assign(_impl, rhs._impl);
    return *this;
}

FlaDefinition::~FlaDefinition()
{
    clover::intrusive_ptr_safe_release(_impl);
}

FlaDefinition::FlaDefinition(fla::Definition* impl)
{
    _impl = impl;
    clover::intrusive_ptr_safe_retain(impl);
}

FlaDefinition::FlaDefinition() : FlaDefinition(nullptr)
{
}

template <typename T>
static FlaDefinition inline s_loadData(const void* data, size_t dataLen, const T& value, FlaErrorCode* error)
{
    fla::ErrorCode errorCode;
    fla::LoadDataInfo info = { fla::settings::getIgnorePlaceHolde(), fla::settings::getCheckAuthorizedFunc() };
    auto ptr = fla::Definition_loadData(data, dataLen, info, value, &errorCode);
    if (error)
    {
        *error = static_cast<FlaErrorCode>(errorCode);
    }
    return FlaDefinition(ptr.get());
}

FlaDefinition FlaDefinition::loadData(const void* data, size_t dataLen, FlaErrorCode* error)
{
    return s_loadData(data, dataLen, fla::NullType(), error);
}

FlaDefinition FlaDefinition::loadData(const void* data, size_t dataLen, int Id, FlaErrorCode* error)
{
    return s_loadData(data, dataLen, Id, error);
}

FlaDefinition FlaDefinition::loadData(const void* data, size_t dataLen, const std::string& name, FlaErrorCode* error)
{
    return s_loadData(data, dataLen, name, error);
}

bool FlaDefinition::isNull() const
{
    return _impl == nullptr;
}

FlaDefinition FlaDefinition::findState(const std::string& name) const
{
    if (_impl)
    {
        return FlaDefinition(fla::Definition_findState(_impl, name).get());
    }
    return FlaDefinition();
}

FlaDefinition FlaDefinition::stateAt(int index) const
{
    if (_impl)
    {
        return FlaDefinition(fla::Definition_stateAt(_impl, index).get());
    }
    return FlaDefinition();
}

cocos2d_bridge::Color4F FlaDefinition::getSceneColor() const
{
    if (_impl)
    {
        auto color = fla::Definition_getSceneColor(_impl);
        return cocos2d_bridge::Color4F_Make(color.red, color.green, color.blue, color.alpha);
    }
    return cocos2d_bridge::Color4F_Make(0, 0, 0, 0);
}

cocos2d_bridge::Rect FlaDefinition::getBounds() const
{
    if (_impl)
    {
        auto rt = _impl->getBounds();
        return cocos2d_bridge::Rect(rt.x, rt.y, rt.width, rt.height);
    }
    return cocos2d_bridge::Rect(0, 0, 0, 0);
}

std::vector<std::string> FlaDefinition::getStateNames() const
{
    std::vector<std::string> v;
    if (_impl)
    {
        v = fla::Definition_getStateNames(_impl);
    }
    return v;
}

cocos2d_bridge::Texture2D* FlaDefinition::transToTexture(FlaPixelFormat format) const
{
    return transToTexture(1.0, 0.0, format);
}

cocos2d_bridge::Texture2D* FlaDefinition::transToTexture(float scale, FlaPixelFormat format) const
{
    return transToTexture(scale, 0.0, format);
}

cocos2d_bridge::Texture2D* FlaDefinition::transToTexture(float scale, float ratio, FlaPixelFormat format) const
{
    if (isNull())
    {
        return nullptr;
    }
    return fla::definition_transToTexture(_impl, scale, ratio, (fla::PixelFormat)format);
}

FlaBitmapData FlaDefinition::transToBitmap(FlaPixelFormat format) const
{
    return transToBitmap(1.0, 0.0, format);
}

FlaBitmapData FlaDefinition::transToBitmap(float scale, FlaPixelFormat format) const
{
    return transToBitmap(scale, 0.0, format);
}

FlaBitmapData FlaDefinition::transToBitmap(float scale, float ratio, FlaPixelFormat format) const
{
    if (isNull())
    {
        return FlaBitmapData();
    }
    auto bitmapData = fla::transToBitmapData(_impl, scale, ratio, (fla::PixelFormat)format);
    return FlaBitmapData(bitmapData.get());
}

void FlaDefinition::walkChildren(const std::function<void(const FlaDefinition&, int)>& fun) const
{
    if (_impl)
    {
        fla::Definition_walkChildren(_impl,
                                     [&](const fla::Definition::Ptr& child, int level)
                                     {
                                         fun(FlaDefinition(child.get()), level);
                                     });
    }
}

std::vector<FlaPlacement> FlaDefinition::getChildPlacements(float scale) const
{
    std::vector<FlaPlacement> placements;
    if (!_impl || !fla::Definition_isAnimation(_impl))
    {
        return placements;
    }

    auto sprite = static_cast<fla::DefinitionAnimation*>(_impl);
    auto spriteFrame = sprite->getFrames()[0];
    placements.reserve(spriteFrame.size());

    auto bounds = this->getBounds();
    fla::Matrix wholeTrans(1, 0, 0, -1, 0, bounds.size.height * scale);
    for (auto& obj : spriteFrame)
    {
        if (obj.isRemoveObject() && !obj.hasCharacterID())
        {
            continue;
        }

        auto child = sprite->findDefinition(obj.characterID());
        if (child)
        {
            placements.push_back(FlaPlacement());
            auto& back = placements.back();

            if (obj.hasTrans())
            {
                auto trans = obj.trans();
                trans.tx *= scale;
                trans.ty *= scale;

                trans = wholeTrans * trans;

                trans.get(back.transform.a,
                          back.transform.b,
                          back.transform.c,
                          back.transform.d,
                          back.transform.tx,
                          back.transform.ty);
            }
            else
            {
#if COCOS2D_VERSION >= 0x00030000
                back.transform = cocos2d::AffineTransformMakeIdentity();
#else
                back.transform = cocos2d::CCAffineTransformMakeIdentity();
#endif
            }

            back.depth = obj.depth();
            back.definition = FlaDefinition(child);
        }
    }

    return placements;
}

std::string FlaDefinition::getName() const
{
    return _impl ? _impl->getName() : "";
}

int FlaDefinition::getId() const
{
    return _impl ? _impl->getId() : 0;
}

float FlaDefinition::getFrameRate() const
{
    if (_impl)
    {
        auto dataInfo = _impl->getDataInfo();
        return dataInfo ? dataInfo->getFrameRate() : 24;
    }
    return 24;
}

std::string FlaDefinition::getDataMd5() const
{
    if (_impl)
    {
        auto dataInfo = _impl->getDataInfo();
        return dataInfo ? dataInfo->getMd5String() : "";
    }
    return "";
}

fla::Definition* FlaDefinition::getRaw() const
{
    return _impl;
}

FlaMovieType FlaDefinition::getMovieType() const
{
    return _impl ? static_cast<FlaMovieType>(_impl->getType()) : FlaMovieType::Null;
}
