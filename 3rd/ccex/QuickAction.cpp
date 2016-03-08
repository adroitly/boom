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

#include "QuickAction.h"

namespace ccex
{
    namespace
    {
        class CallFuncBlock : public ActionInstant
        {
        public:
            static CallFuncBlock* create(const std::function<void(void)>& fun);
            virtual void update(float time) override;

        private:
            CallFuncBlock(const std::function<void(void)>& fun);
            std::function<void(void)> _fun;
        };

        CallFuncBlock* CallFuncBlock::create(const std::function<void(void)>& fun)
        {
            CallFuncBlock* block = new CallFuncBlock(fun);
            block->autorelease();
            return block;
        }

        void CallFuncBlock::update(float time)
        {
            (void)time;
            _fun();
        }

        CallFuncBlock::CallFuncBlock(const std::function<void(void)>& fun) : _fun(fun)
        {
        }
    }

    namespace q_action
    {
        QuickAction& QuickAction::link(FiniteTimeAction* action)
        {
            _linkCount++;
            if (_action == nullptr)
            {
                _action = action;
            }
            else
            {
                if (_groupType == GroupType::Sequence)
                {
                    _action = Sequence::createWithTwoActions(_action, action);
                }
                else
                {
                    _action = Spawn::createWithTwoActions(_action, action);
                }
            }
            return *this;
        }

        QuickAction& QuickAction::callFunc(const std::function<void(void)>& fun)
        {
            return link(CallFuncBlock::create(fun));
        }
    }
}