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

#ifndef __CCEX_ITERATOR_H__
#define __CCEX_ITERATOR_H__

#include "cocos2d.h"

namespace ccex
{
    using namespace cocos2d;
    /////////////////////////////////////
    // 遍历CCNode的子节点，包括子节点的子节点
    // 需要传入一个遍历的函数，类型为 bool(int level, CCNode* child),
    // int level,     表示现在正遍历第几层，子节点为level=1，子节点的子节点level=2, ....
    // CCNode* child，正在遍历的子节点
    // 函数返回值为 true,
    // 表示需要遍历此节点的子节点，返回为false,表示停止遍历此节点的子节点
    void node_walkChildren(Node* node, const std::function<bool(Node* child, int level)>& fun);
    void node_walkChildren(Node* node, const std::function<bool(Node* child)>& fun);
}

#endif
