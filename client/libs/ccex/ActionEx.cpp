//
//  ActionEx.cpp
//  big-devil
//
//  Created by PatGame on 15/6/1.
//
//

#include "ActionEx.h"
#include <functional>
#include <stdlib.h>

namespace ccex
{
    typedef cocos2d::Vec2 Vec2;

    class BaseAction
    {
    public:
        virtual ~BaseAction()
        {
        }

        virtual void update(cocos2d::Node* node, float t) = 0;
        virtual void start(cocos2d::Node* node) = 0;
        virtual size_t sizeOfObject() const = 0;

        float duration;
    };

    namespace
    {
        class MoveBy : public BaseAction
        {
        public:
            void init(const cocos2d::Vec2& position)
            {
                _positionDelta = position;
            }

            virtual void update(cocos2d::Node* target, float t) override
            {
                Vec2 currentPos = target->getPosition();
                Vec2 diff = currentPos - _previousPosition;
                _startPosition = _startPosition + diff;
                Vec2 newPos = _startPosition + (_positionDelta * t);
                target->setPosition(newPos);
                _previousPosition = newPos;
            }

            virtual void start(cocos2d::Node* target) override
            {
                _previousPosition = _startPosition = target->getPosition();
            }

            virtual size_t sizeOfObject() const override
            {
                return sizeof(MoveBy);
            }

        protected:
            cocos2d::Vec2 _previousPosition;
            cocos2d::Vec2 _startPosition;
            cocos2d::Vec2 _positionDelta;
        };

        class MoveTo : public MoveBy
        {
        public:
            void init(const cocos2d::Vec2& position)
            {
                _endPosition = position;
            }

            virtual void start(cocos2d::Node* target) override
            {
                MoveBy::start(target);
                _positionDelta = _endPosition - target->getPosition();
            }

            virtual size_t sizeOfObject() const override
            {
                return sizeof(MoveTo);
            }

        public:
            cocos2d::Vec2 _endPosition;
        };

        class ScaleTo : public BaseAction
        {
        public:
            void init(float s)
            {
                _endScaleX = s;
                _endScaleY = s;
            }

            virtual void start(cocos2d::Node* target) override
            {
                _startScaleX = target->getScaleX();
                _startScaleY = target->getScaleY();
                _deltaX = _endScaleX - _startScaleX;
                _deltaY = _endScaleY - _startScaleY;
            }

            virtual void update(cocos2d::Node* target, float time) override
            {
                if (target)
                {
                    target->setScaleX(_startScaleX + _deltaX * time);
                    target->setScaleY(_startScaleY + _deltaY * time);
                }
            }

            virtual size_t sizeOfObject() const override
            {
                return sizeof(ScaleTo);
            }

        private:
            float _startScaleX;
            float _startScaleY;
            float _endScaleX;
            float _endScaleY;
            float _deltaX;
            float _deltaY;
        };

        class DelayTime : public BaseAction
        {
        public:
            virtual void start(cocos2d::Node* target) override
            {
            }

            virtual void update(cocos2d::Node* target, float time) override
            {
            }

            virtual size_t sizeOfObject() const override
            {
                return sizeof(DelayTime);
            }
        };

        class FadeTo : public BaseAction
        {
        public:
            void init(GLubyte opacity)
            {
                _toOpacity = opacity;
            }

            virtual void start(cocos2d::Node* target) override
            {
                _fromOpacity = target->getOpacity();
            }

            virtual void update(cocos2d::Node* target, float time) override
            {
                target->setOpacity(_fromOpacity + (_toOpacity - _fromOpacity) * time);
            }

            virtual size_t sizeOfObject() const override
            {
                return sizeof(FadeTo);
            }

        private:
            GLubyte _toOpacity;
            GLubyte _fromOpacity;
        };

        class CallFunc : public BaseAction
        {
        public:
            ~CallFunc()
            {
                delete _func;
            }

            CallFunc()
            {
                _func = nullptr;
                _call = false;
            }

            void init(const std::function<void()>& func)
            {
                assert(_func == nullptr);
                if (func)
                {
                    _func = new std::function<void()>(func);
                }
                _call = false;
            }

            virtual void update(cocos2d::Node* target, float t) override
            {
                if (!_call && _func)
                {
                    (*_func)();
                }
            }

            virtual void start(cocos2d::Node*) override
            {
                _call = false;
            }

            virtual size_t sizeOfObject() const override
            {
                return sizeof(CallFunc);
            }

        private:
            std::function<void()>* _func;
            bool _call;
        };
    }

    class OtherAction : public BaseAction
    {
    public:
        ~OtherAction()
        {
            _action->release();
        }

        void init(cocos2d::FiniteTimeAction* action)
        {
            _action = action;
            _action->retain();
        }

        virtual void update(cocos2d::Node* target, float t) override
        {
            _action->update(t);
        }

        virtual void start(cocos2d::Node* target) override
        {
            _action->startWithTarget(target);
        }

        virtual size_t sizeOfObject() const override
        {
            return sizeof(OtherAction);
        }

    private:
        cocos2d::RefPtr<cocos2d::FiniteTimeAction> _action;
    };

    ActionGroup::ActionGroup()
    {
        _numberOfCallFunc = 0;
    }

    ActionGroup::~ActionGroup()
    {
        char* begin = &_buff[0];
        char* end = begin + _buff.size();
        while (begin < end)
        {
            BaseAction* ptr = (BaseAction*)begin;
            auto size = ptr->sizeOfObject();
            ptr->~BaseAction();
            begin += size;
        }
    }

    BaseAction* ActionGroup::nextAction(BaseAction* action)
    {
        char* end = &_buff[_buff.size()];
        char* ptr = (char*)action;

        if (ptr == nullptr)
        {
            ptr = &_buff[0];
        }
        else
        {
            ptr += action->sizeOfObject();
        }

        if (ptr >= end)
        {
            ptr = nullptr;
        }
        return (BaseAction*)ptr;
    }

    template <typename T>
    T* ActionGroup::pushAction(float duration)
    {
        size_t size = _buff.size();
        _buff.resize(size + sizeof(T));

        T* ptr = new (&_buff[size]) T();
        ptr->duration = duration;
        doUpdateDuration(duration);

        return ptr;
    }

    void ActionGroup::moveTo(float duration, const cocos2d::Vec2& position)
    {
        MoveTo* ptr = pushAction<MoveTo>(duration);
        ptr->init(position);
    }

    void ActionGroup::moveBy(float duration, const cocos2d::Vec2& position)
    {
        MoveBy* ptr = pushAction<MoveBy>(duration);
        ptr->init(position);
    }

    void ActionGroup::scaleTo(float duration, float scale)
    {
        auto ptr = pushAction<ScaleTo>(duration);
        ptr->init(scale);
    }

    void ActionGroup::delayTime(float duration)
    {
        pushAction<DelayTime>(duration);
    }

    void ActionGroup::fadeTo(float duration, GLubyte opacity)
    {
        auto ptr = pushAction<FadeTo>(duration);
        ptr->init(opacity);
    }

    void ActionGroup::fadeOut(float duration)
    {
        auto ptr = pushAction<FadeTo>(duration);
        ptr->init(0.0);
    }

    void ActionGroup::callFunc(const std::function<void()>& func)
    {
        CallFunc* ptr = pushAction<CallFunc>(0.0);
        ptr->init(func);
        _numberOfCallFunc++;
    }

    void ActionGroup::action(cocos2d::FiniteTimeAction* action)
    {
        OtherAction* ptr = pushAction<OtherAction>(action->getDuration());
        ptr->init(action);
    }

    void ActionGroup::run(cocos2d::Node* node)
    {
        node->runAction(this);
    }

    Sequence::Sequence()
    {
        _currentEndT = 0.0;
        _currentStartT = 0.0;
        _currentAction = nullptr;
    }

    Sequence* Sequence::create()
    {
        auto p = new Sequence();
        p->initWithDuration(0.0);
        p->autorelease();
        return p;
    }

    void Sequence::startWithTarget(cocos2d::Node* target)
    {
        _currentAction = nullptr;
        _currentEndT = 0.0;
        _currentStartT = 0.0;
        cocos2d::ActionInterval::startWithTarget(target);
    }

    void Sequence::doUpdateDuration(float d)
    {
        float duration = getDuration();
        duration += d;
        setDuration(duration);
    }

    void Sequence::update(float t)
    {
        float duration = getDuration();
        while (t >= _currentEndT)
        {
            _currentAction = nextAction(_currentAction);
            if (!_currentAction)
            {
                return;
            }

            _currentAction->start(getTarget());
            _currentAction->update(getTarget(), 0.0);

            _currentStartT = _currentEndT;
            _currentEndT += _currentAction->duration / duration;
        }

        assert(t >= _currentStartT);
        float newT = (t - _currentStartT) * duration / _currentAction->duration;
        _currentAction->update(getTarget(), newT);
    }

    Spawn* Spawn::create()
    {
        auto p = new Spawn();
        p->initWithDuration(0.0);
        p->autorelease();
        return p;
    }

    void Spawn::startWithTarget(cocos2d::Node* target)
    {
        BaseAction* action = nextAction(nullptr);
        while (action)
        {
            action->start(target);
            action = nextAction(action);
        }
        cocos2d::ActionInterval::startWithTarget(target);
    }

    void Spawn::doUpdateDuration(float d)
    {
        float duration = getDuration();
        setDuration(MAX(duration, d));
    }

    void Spawn::update(float time)
    {
        BaseAction* action = nextAction(nullptr);
        float currentTime = time * getDuration();
        while (action)
        {
            if (action->duration >= currentTime)
            {
                action->update(getTarget(), time);
            }
            action = nextAction(action);
        }
    }
}
