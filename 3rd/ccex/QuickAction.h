/*
 The MIT License (MIT)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#ifndef __CCEX_QUICKACTION_H__
#define __CCEX_QUICKACTION_H__

#include "cocos2d.h"
#include <functional>

namespace ccex
{
    using namespace cocos2d;
    /*
     实现了cocos2d中runAction的简写
     比如
     CCSequence* seq = CCSequence::create(
     CCScaleTo::create(0.1f, 1.2f), CCScaleTo::create(0.1f, 0.0f), NULL);
     this->runAction(seq);

     可以简写成
     QSequence().scaleTo(0.1, 1.2).scaleTo(0.1, 0.0).run(this);
     */
    namespace q_action
    {
        class QuickAction
        {
        public:
            enum class GroupType
            {
                Sequence,
                Spawn,
            };

            QuickAction& moveTo(float duration, const Point& position)
            {
                return link(MoveTo::create(duration, position));
            }

            QuickAction& moveBy(float duration, const Point& deltaPosition)
            {
                return link(MoveBy::create(duration, deltaPosition));
            }

            QuickAction& rotateBy(float fDuration, float fDeltaAngle)
            {
                return link(RotateBy::create(fDuration, fDeltaAngle));
            }

            QuickAction& rotateTo(float duration, float angle)
            {
                return link(RotateTo::create(duration, angle));
            }

            QuickAction& scaleTo(float duration, float s)
            {
                return link(ScaleTo::create(duration, s));
            }

            QuickAction& scaleTo(float duration, float sx, float sy)
            {
                return link(ScaleTo::create(duration, sx, sy));
            }

            QuickAction& scaleBy(float duration, float s)
            {
                return link(ScaleBy::create(duration, s));
            }

            QuickAction& scaleBy(float duration, float sx, float sy)
            {
                return link(ScaleBy::create(duration, sx, sy));
            }

            QuickAction& fadeTo(float duration, GLubyte opacity)
            {
                return link(FadeTo::create(duration, opacity));
            }

            QuickAction& fadeIn(float d)
            {
                return link(FadeIn::create(d));
            }

            QuickAction& fadeOut(float d)
            {
                return link(FadeOut::create(d));
            }

            QuickAction& delayTime(float d)
            {
                return link(DelayTime::create(d));
            }

            QuickAction& easeOut(const QuickAction& action, float fRate)
            {
                return easeOut(static_cast<ActionInterval*>(action._action), fRate);
            }

            QuickAction& easeOut(ActionInterval* pAction, float fRate)
            {
                return link(EaseOut::create(pAction, fRate));
            }

            QuickAction& repeat(const QuickAction& action, unsigned int times)
            {
                return link(Repeat::create(action._action, times));
            }

            QuickAction& action(const QuickAction& action)
            {
                return link(static_cast<ActionInterval*>(action._action));
            }

            QuickAction& action(ActionInterval* action)
            {
                return link(action);
            }

            template <typename T, typename B>
            QuickAction& callFunc(T* object, void (B::*selector)())
            {
                static_assert(std::is_base_of<Ref, T>::value, "");
                static_assert(std::is_base_of<B, T>::value, "");
                return link(CallFunc::create(object, static_cast<SEL_CallFunc>(selector)));
            }

            QuickAction& callFunc(const std::function<void(void)>& fun);

            void run(Node* node)
            {
                node->runAction(_action);
            }

            Spawn* getSpawn() const
            {
                assert(_linkCount >= 2 && _groupType == GroupType::Spawn);
                return static_cast<Spawn*>(_action);
            }

            Sequence* getSequence() const
            {
                assert(_linkCount >= 2 && _groupType == GroupType::Sequence);
                return static_cast<Sequence*>(_action);
            }

        private:
            friend QuickAction make_QuickAction(GroupType type);
            QuickAction(GroupType type) : _action(nullptr), _groupType(type)
            {
                _linkCount = 0;
            }
            QuickAction& link(FiniteTimeAction* action);

        private:
            FiniteTimeAction* _action;
            GroupType _groupType;
            int _linkCount;
        };

        inline QuickAction make_QuickAction(QuickAction::GroupType type)
        {
            return QuickAction(type);
        }
    }

    inline q_action::QuickAction QSequence()
    {
        return q_action::make_QuickAction(q_action::QuickAction::GroupType::Sequence);
    }

    inline q_action::QuickAction QSpawn()
    {
        return q_action::make_QuickAction(q_action::QuickAction::GroupType::Spawn);
    }
}

#endif
