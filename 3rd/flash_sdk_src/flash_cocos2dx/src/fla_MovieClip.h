//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_MOVIECLIP_H__
#define __FLA_MOVIECLIP_H__

#include <memory>
#include "cocos2d.h"
#include "fla_TextureFrame.h"
#include "../FlaCacheStrategy.h"
#include "../../core/definition/fla_Definition.h"
#include "../../core/definition/fla_PlaceObject.h"
#include "../../core/definition/fla_DefinitionUtils.h"
#include "../../core/base/fla_ColorTransform.h"

class FlaGLProgram;

namespace fla
{
    class MovieClip;
    class MovieGlobalData;
    class MoviePartShareData;
    class MovieClipListener
    {
    public:
        virtual void movieClipDidStartMovie(MovieClip* node) = 0;
        virtual void movieClipDidFinishMovie(MovieClip* node) = 0;
        virtual void movieClipDidStepFrame(MovieClip* node) = 0;
    };

    class MovieClipDataSource
    {
    public:
        virtual MovieGlobalData* getMovieGlobalData(const Definition::Ptr& node) = 0;
        virtual MoviePartShareData* getMoviePartShareData(const Definition::Ptr& node) = 0;
        virtual MoviePartShareData* getMoviePartShareDataForce(const Definition::Ptr& node) = 0;
    };

    class BatchMoviewRender;
    class MoviePart;
    class MovieClip final : public MovieClipListener, public boost::noncopyable
    {
    public:
        typedef boost::intrusive_ptr<MovieClip> Ptr;

        MovieClip();
        void init(const Definition::Ptr& definition, MovieClipDataSource* dataSource);

        virtual ~MovieClip();

        void setListener(MovieClipListener* listener)
        {
            _listener = listener;
        }

        void setColorTransform(const ColorTransform& colorTransform);

        void setPause(bool isPause);
        void setPause(bool isPause, int Id);
        void setPause(bool isPause, const std::string& name);

        void stepFrame(bool isRoot, bool isAuto);
        void stepFrameRatio(float ratio);

        void goToFrame(int N);

        int getCurrentFrame() const;

        int getFrameCount() const;

        bool changeState(const std::string& stateName);
        bool changeState(int index);
        bool hasState(const std::string& stateName);

        Definition::Ptr getDefinition() const
        {
            return _definition;
        }
        void setDefinition(const Definition::Ptr& definition);

        void refreshSprites();

        std::string getMovieName() const;
        std::string getStateName() const;

        int getMovieId() const;

        int getDepth() const
        {
            return _depth;
        }

        Matrix nodeToParentTransformTranslatePoint(float scale) const;
        Matrix nodeToParentTransform(float scale) const;
        Point getLeafTranslatePoint(float scale) const;
        Rect getBounds() const;

        const MovieClip* hitAtom(const Point& pt, float scale) const;

        void movieClipDidFinishMovie(MovieClip* node) override;
        void movieClipDidStartMovie(MovieClip* node) override;
        void movieClipDidStepFrame(MovieClip* node) override;

        void setMoviePart(MoviePart* part)
        {
            _moviePart = part;
        }

        MoviePart* getMoviePart()
        {
            return _moviePart;
        }

        void walk(const std::function<bool(MovieClip* clip)>& fun);

        void retain();
        void release();

    private:
        MovieGlobalData* getMovieGlobalData();
        MoviePartShareData* getMoviePartShareData();

        template <typename Fun>
        bool changeState_impl(Fun findState);
        void refreshNodes(const Definition::Ptr& oldDefintion);
        void resetToFirstFrame();
        void placeFrame(int frameIndex);
        void placeFrame(const AnimationFrame& frame, int frameIndex);
        void placeFrame(const AnimationFrame& currentFrame, const AnimationFrame& nextFrame, float factor);
        void resetStatus(const MovieClip* node);
        MovieClip* findChildWithDepth(int depth);
        void placeChildNode(const PlaceObject& obj);
        MovieClip::Ptr newClipWithObject(const PlaceObject& obj);
        void setQuickSprite(TextureFrame* sprite);

        MovieClip* getMainSubNode() const;
        friend class BatchMoviewRender;

        void clear(bool isTree);

        float getFloatRatio() const
        {
            return _ratio / 65535.0;
        }
        bool isTree() const
        {
            return Definition_isAnimation(_state);
        }
        bool isLeaf() const
        {
            return !isTree();
        }

    private:
        clover::RefCounter _refCounter;
        MoviePart* _moviePart;
        Definition::Ptr _definition;
        Definition::Ptr _state;

        // 为压缩存储空间，将树数据和叶数据放进union中
        union
        {
            struct
            {
                PodRefPtrVector<MovieClip>::type subMovieClips;
            } _tree;
            struct
            {
                TextureFrame* sprite;
                struct Point
                {
                    fla::real_t x;
                    fla::real_t y;
                };
                static_assert(sizeof(Point) == sizeof(fla::Point), "");
                mutable Point translatePoint;
            } _leaf;
        };

        MovieClipListener* _listener;
        MovieClipDataSource* _dataSource;
        ColorTransform _colorTransform;
        Matrix _flashTransform;

        uint16_t _curFrame;
        uint16_t _depth;
        uint16_t _ratio;

        BlendMode _blendMode;  // 8 bit

        enum
        {
            Bit_Pause = (1 << 0),
            Bit_HasBlendMode = (1 << 1),
            Bit_HasColorTransform = (1 << 2),
        };
        uint8_t _flags;  // 8 bit
    };

    inline void intrusive_ptr_add_ref(MovieClip* obj)
    {
        obj->retain();
    }

    inline void intrusive_ptr_release(MovieClip* obj)
    {
        obj->release();
    }
}

#endif
