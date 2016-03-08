//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_AsynManager.h"
#include "../../core/platform/fla_PlatformTraits.h"
#include "fla_cocos2d_Texture.h"
#include <functional>
using namespace cocos2d;

namespace fla
{
#define kSaveBitmapTag 1
#define kCallbackTag 2
    struct SaveBitmapOperation : public async::Operation
    {
        SaveBitmapOperation(const BitmapData::Ptr& bitmapData_, const std::string& filePath_)
            : bitmapData(bitmapData_), filePath(filePath_)
        {
            setTag(kSaveBitmapTag);
        }

        virtual void action() override
        {
            saveBitmapToPngFile(bitmapData, filePath);
        }

        BitmapData::Ptr bitmapData;
        std::string filePath;
    };

    AsyncManager& AsyncManager::getInstance()
    {
        static AsyncManager saver;
        return saver;
    }

    void AsyncManager::removeAllItems()
    {
        _queue.cancelAll();
    }

    bool AsyncManager::saveBitmapAsync(const BitmapData::Ptr& bitmap, const std::string& filePath)
    {
        if (bitmap == nullptr)
        {
            return false;
        }

        if (_savingPaths.count(filePath) > 0)
        {
            return false;
        }

        auto operation = std::make_shared<SaveBitmapOperation>(bitmap, filePath);
        operation->setTag(kSaveBitmapTag);
        addOperation(operation);
        return true;
    }

    void AsyncManager::addOperation(const async::Operation::Ptr& operation)
    {
        if (_queue.isEmpty())
        {
            cocos2d_bridge::Director_schedule(schedule_selector(AsyncManager::asyncCallBackUpdate), this, 0, false);
        }
        _queue.addOperation(operation, this);
    }

    void AsyncManager::addCallbackOperation(const async::CallBackOperation::Ptr& op)
    {
        op->setTag(kCallbackTag);
        addOperation(op);
    }

    AsyncManager::AsyncManager() : _queue(4)
    {
    }

    AsyncManager::~AsyncManager()
    {
    }

    void AsyncManager::asyncCallBackUpdate(float t)
    {
        FLA_UNUSED(t);
        _queue.dispatchCallbacks(50);
    }

    void AsyncManager::suspendFuture()
    {
        _queue.suspendFuture();
    }

    void AsyncManager::resumeAll()
    {
        _queue.resumeAll();
    }

    void AsyncManager::operationOnCompletion(const async::Operation::Ptr& operation, async::OperationResultType type)
    {
        FLA_UNUSED(type);
        if (_queue.isEmpty())
        {
            cocos2d_bridge::Director_unschedule(schedule_selector(AsyncManager::asyncCallBackUpdate), this);
        }

        if (operation->getTag() == kSaveBitmapTag)
        {
            auto saveOp = std::static_pointer_cast<SaveBitmapOperation>(operation);
            _savingPaths.erase(saveOp->filePath);
        }
        else if (operation->getTag() == kCallbackTag)
        {
            auto op = std::static_pointer_cast<async::CallBackOperation>(operation);
            op->callBack();
        }
    }
}
