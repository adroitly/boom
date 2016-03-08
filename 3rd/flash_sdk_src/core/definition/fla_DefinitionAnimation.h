//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_DEFINESPRITE_H__
#define __FLA_DEFINESPRITE_H__

#include <vector>
#include <map>
#include "fla_Definition.h"
#include "fla_DefinitionMap.h"
#include "fla_PlaceObject.h"
#include "../base/fla_RefPtrVector.h"

namespace fla
{
    class AnimationFrame : public std::vector<PlaceObject>
    {
    public:
        const_iterator findWithDepth(uint16_t depth) const;
        iterator findWithDepth(uint16_t depth);
    };

    class DefinitionAnimation : public DefinitionHelper<DefinitionAnimation>
    {
    public:
        Definition* findDefinition(int Id) const;

        void setDefinitions(const DefinitionMap<int>& defs);

        size_t getFrameCount() const
        {
            return _frames.size();
        }

        virtual void accept(DefinitionVisitor& visitor) const override
        {
            visitor.visit(*this);
        }

        virtual Rect getBounds() const override;

        const RefPtrVector<Definition>::type& getDefinitions() const
        {
            return _definitions;
        }

        std::vector<AnimationFrame>& getFrames()
        {
            return _frames;
        }

        void addSpriteFrame(const AnimationFrame& frame)
        {
            _frames.push_back(frame);
        }

        const std::vector<AnimationFrame>& getFrames() const
        {
            return _frames;
        }

        // 将一个动画序列进行拆分，从第offset开始，总共有frameCount这样多帧
        DefinitionAnimation::Ptr split(int offset, int frameCount) const;

        AnimationFrame gotoFrame(int index) const;
        void gotoFrame(int index, AnimationFrame& frame) const;

        void onFinishParse() override;

    protected:
        friend class DefinitionHelper<DefinitionAnimation>;
        DefinitionAnimation() : DefinitionAnimation(DefinitionType::Animation)
        {
        }

        DefinitionAnimation(DefinitionType type) : DefinitionHelper<DefinitionAnimation>(type), _bounds(Rect::makeNull())
        {
        }

    private:
        RefPtrVector<Definition>::type _definitions;
        std::vector<AnimationFrame> _frames;
        mutable Rect _bounds;
    };
};

#endif
