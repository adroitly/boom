//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_DefinitionAnimation.h"
#include <algorithm>
#include <assert.h>

namespace fla
{
    AnimationFrame::iterator AnimationFrame::findWithDepth(uint16_t depth)
    {
        return std::find_if(begin(),
                            end(),
                            [=](const PlaceObject& obj)
                            {
                                return obj.depth() == depth;
                            });
    }

    AnimationFrame::const_iterator AnimationFrame::findWithDepth(uint16_t depth) const
    {
        return const_cast<AnimationFrame*>(this)->findWithDepth(depth);
    }

    Definition* DefinitionAnimation::findDefinition(int Id) const
    {
        auto iter = std::lower_bound(_definitions.begin(),
                                     _definitions.end(),
                                     Id,
                                     [=](const Definition* ptr, int Id)
                                     {
                                         return ptr->getId() < Id;
                                     });
        if (iter != _definitions.end() && (*iter)->getId() == Id)
        {
            return *iter;
        }
        return nullptr;
    }

    void DefinitionAnimation::setDefinitions(const DefinitionMap<int>& defs)
    {
        _definitions.reserve(defs.size());
        for (auto& def : defs)
        {
            _definitions.push_back(def.second.get());
        }

        std::sort(_definitions.begin(),
                  _definitions.end(),
                  [=](const Definition* lhs, const Definition* rhs)
                  {
                      return lhs->getId() < rhs->getId();
                  });
    }

    Rect DefinitionAnimation::getBounds() const
    {
        if (_frames.empty())
        {
            return Rect();
        }

        if (!_bounds.isNull())
        {
            return _bounds;
        }

        auto& frame = _frames[0];
        Rect bounds;
        bool first = true;
        for (auto& obj : frame)
        {
            if (!obj.isRemoveObject() && obj.hasCharacterID())
            {
                auto child = findDefinition(obj.characterID());
                if (child)
                {
                    auto rt = child->getBounds();
                    if (obj.hasTrans())
                    {
                        rt = obj.trans() * rt;
                    }

                    if (first)
                    {
                        bounds = rt;
                    }
                    else
                    {
                        bounds.unionRect(rt);
                    }
                    first = false;
                }
            }
        }

        _bounds = bounds;
        return bounds;
    }

    DefinitionAnimation::Ptr DefinitionAnimation::split(int offset, int frameCount) const
    {
        auto sprite = DefinitionAnimation::create();
        DefinitionMap<int> defintions;
        for (auto i = 0; i < frameCount; i++)
        {
            if (i == 0)
            {
                sprite->addSpriteFrame(gotoFrame(offset));
            }
            else
            {
                sprite->addSpriteFrame(_frames[i + offset]);
            }

            auto& frame = sprite->getFrames()[i];
            for (auto& obj : frame)
            {
                if (obj.hasCharacterID())
                {
                    auto define = findDefinition(obj.characterID());
                    if (define)
                    {
                        defintions.push_back(define);
                    }
                }
            }
        }
        sprite->setDefinitions(defintions);
        return sprite;
    }

    void DefinitionAnimation::gotoFrame(int index, AnimationFrame& frame) const
    {
        for (auto& obj : _frames[index])
        {
            auto iter = frame.findWithDepth(obj.depth());
            if (obj.isRemoveObject())
            {
                frame.erase(iter);
            }
            else
            {
                if (obj.hasCharacterID() && iter != frame.end() && obj.characterID() != iter->characterID())
                {
                    iter->setCharacterID(obj.characterID());
                }

                if (iter == frame.end())
                {
                    frame.push_back(obj);
                    iter = frame.begin() + (frame.size() - 1);
                }

                if (obj.hasTrans())
                {
                    iter->setTrans(obj.trans());
                }

                if (obj.hasColorTrans())
                {
                    iter->setColorTrans(obj.colorTrans());
                }
            }
        }
    }
    
    AnimationFrame DefinitionAnimation::gotoFrame(int index) const
    {
        AnimationFrame frame;
        for (int i = 0; i <= index; i++)
        {
            gotoFrame(i, frame);
        }
        return frame;
    }

    void DefinitionAnimation::onFinishParse()
    {
        _frames.shrink_to_fit();
        for (auto& frame : _frames)
        {
            frame.shrink_to_fit();
        }
    }
}
