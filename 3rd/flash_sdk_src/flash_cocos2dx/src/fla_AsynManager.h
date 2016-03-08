//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_ASYNMANAGER_H__
#define __FLA_ASYNMANAGER_H__

#include <string>
#include "./cocos2d_bridge.h"
#include "async/OperationQueue.h"
#include "../../core/base/fla_BitmapData.h"
#include "../../core/definition/fla_Definition.h"

namespace fla
{
    class AsyncManager : public cocos2d_bridge::Object, public async::OperationCallBack, boost::noncopyable
    {
    public:
        static AsyncManager& getInstance();
        ~AsyncManager();

        bool saveBitmapAsync(const BitmapData::Ptr& bitmap, const std::string& filePath);

        template <typename Fun, typename Callback>
        void async(const Fun& fun, const Callback& callback)
        {
            auto op = async::MakeOperation(fun, callback);
            addCallbackOperation(op);
        }

        void suspendFuture();
        void resumeAll();
        void removeAllItems();
        
        bool isEmpty() const
        {
            return _queue.isEmpty();
        }
        
    private:
        void asyncCallBackUpdate(float t);
        void operationOnCompletion(const async::Operation::Ptr& operation, async::OperationResultType type);
        void addOperation(const async::Operation::Ptr& operation);
        void addCallbackOperation(const async::CallBackOperation::Ptr& op);

    private:
        AsyncManager();
        std::set<std::string> _savingPaths;
        async::OperationQueue _queue;
    };
}

#endif
