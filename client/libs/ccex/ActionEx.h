//
//  ActionEx.h
//  big-devil
//
//  Created by PatGame on 15/6/1.
//
//

#ifndef __CCEX_ACTIONEX_H__
#define __CCEX_ACTIONEX_H__

#include "cocos2d.h"
#include <functional>

namespace ccex
{
    class BaseAction;
    class ActionGroup : public cocos2d::ActionInterval
    {
    public:
        ~ActionGroup();

        void moveTo(float duration, const cocos2d::Vec2& position);
        void moveBy(float duration, const cocos2d::Vec2& position);
        void scaleTo(float duration, float scale);
        void delayTime(float duration);
        void fadeTo(float duration, GLubyte opacity);
        void fadeOut(float duration);
        void callFunc(const std::function<void()>& func);
        void action(cocos2d::FiniteTimeAction* action);

        BaseAction* nextAction(BaseAction* action);
        size_t numberOfCallFunc() const
        {
            return _numberOfCallFunc;
        }

        void run(cocos2d::Node* node);

    protected:
        ActionGroup();
        virtual void doUpdateDuration(float duration) = 0;

        template <typename T>
        T* pushAction(float duration);

    private:
        std::vector<char> _buff;
        size_t _numberOfCallFunc;
    };

    class Sequence : public ActionGroup
    {
    public:
        Sequence();
        static Sequence* create();

        virtual void startWithTarget(cocos2d::Node* target) override;
        virtual void update(float time) override;

    private:
        virtual void doUpdateDuration(float duration) override;

    private:
        BaseAction* _currentAction;
        float _currentEndT;
        float _currentStartT;
    };

    class Spawn : public ActionGroup
    {
    public:
        static Spawn* create();

        virtual void startWithTarget(cocos2d::Node* target) override;
        virtual void update(float time) override;

    private:
        virtual void doUpdateDuration(float duration) override;

    };
}

#endif
