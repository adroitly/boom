//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_MovieClip.h"
#include "fla_ReusableMoviewSet.h"
#include "clover/ScopeGuard.h"
#include "libra/libra_bits.h"
#include "fla_MovieShareData.h"
#include "../../core/definition/fla_DefinitionRole.h"
#include "../../core/definition/fla_DefinitionScene.h"
#include "../../core/base/fla_Utils.h"
#include "../FlaResourceCache.h"
using namespace cocos2d;

namespace fla
{
    typedef PodRefPtrVector<MovieClip>::type MovieClipArray;

    // 查找应该插入的位置，保持depth从小到大
    static MovieClipArray::iterator s_findIterator(MovieClipArray& array, int depth)
    {
        // 关键查找，不使用std::lower_bound，避免多余的调用
        auto first = array.begin();
        auto size = array.size();
        while (size != 0)
        {
            auto half_size = size / 2;
            auto middle = first + half_size;
            if ((*middle)->getDepth() < depth)
            {
                first = middle + 1;
                size -= half_size + 1;
            }
            else
                size = half_size;
        }
        return first;
    }

    inline MovieClip* s_getClip(const MovieClipArray& array, const MovieClipArray::iterator& iter, int depth)
    {
        if (iter != array.end() && (*iter)->getDepth() == depth)
        {
            return (*iter);
        }
        return nullptr;
    }

    static void s_removeClip(MovieClipArray& array, int depth)
    {
        auto iter = s_findIterator(array, depth);
        if (iter != array.end() && (*iter)->getDepth() == depth)
        {
            (*iter)->setListener(nullptr);
            array.erase(iter);
        }
    }

    static void s_safeReleaseSprite(TextureFrame** sprite)
    {
        if (*sprite)
        {
            (*sprite)->release();
            *sprite = nullptr;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    MovieClip::MovieClip()
    {
        _curFrame = 0;
        _ratio = 0;
        _depth = 0;
        _listener = nullptr;
        _dataSource = nullptr;
        _flags = 0;
        _moviePart = nullptr;
        _blendMode = BlendMode::Normal;
        _colorTransform.setIdentity();
        _leaf.sprite = nullptr;
    }

    void MovieClip::init(const Definition::Ptr& definition, MovieClipDataSource* dataSource)
    {
        assert(definition);
        assert(dataSource);
        _dataSource = dataSource;
        setDefinition(definition);
    }

    void MovieClip::clear(bool isTree)
    {
        if (isTree)
        {
            _tree.subMovieClips.obj_finish();
        }
        else
        {
            s_safeReleaseSprite(&_leaf.sprite);
        }
    }

    MovieClip::~MovieClip()
    {
        assert(_state);
        assert(_definition);
        clear(isTree());
    }

    void MovieClip::setDefinition(const Definition::Ptr& definition)
    {
        assert(definition);
        auto oldState = _state;
        if (_definition != definition)
        {
            _definition = definition;
            _state = definition;
            if (definition->getType() == DefinitionType::Role)
            {
                auto role = fla::ptr_case<DefinitionRole>(definition);
                _state = role->defaultState();
            }
            assert(_definition);
            assert(_state);
        }
        refreshNodes(oldState);
    }

    void MovieClip::setColorTransform(const ColorTransform& colorTransform)
    {
        _colorTransform = colorTransform;
        libra::bit_set(&_flags, Bit_HasColorTransform, !colorTransform.isIdentity());
    }

    void MovieClip::refreshNodes(const Definition::Ptr& oldState)
    {
        if (oldState)
        {
            bool oldIsSprite = Definition_isAnimation(oldState);
            clear(oldIsSprite);
        }

        _curFrame = 0;

        if (isTree())
        {
            _tree.subMovieClips.obj_init();
            resetToFirstFrame();
        }
        else
        {
            _leaf.sprite = nullptr;
            *((fla::Point*)&_leaf.translatePoint) = Point::makeNull();
        }
    }

    void MovieClip::resetToFirstFrame()
    {
        assert(isTree());
        placeFrame(0);
        for (auto& ptr : _tree.subMovieClips)
        {
            if (ptr->isTree())
            {
                ptr->resetToFirstFrame();
            }
        }
    }

    void MovieClip::placeFrame(int frameIndex)
    {
        assert(isTree());
        auto& sprite = static_cast<const DefinitionAnimation&>(*_state);
        auto& frame = sprite.getFrames()[frameIndex];
        _curFrame = frameIndex;
        placeFrame(frame, frameIndex);
    }

    void MovieClip::resetStatus(const MovieClip* node)
    {
        if (node)
        {
            _ratio = node->_ratio;
            _flags = node->_flags;
            libra::bit_clear(&_flags, Bit_Pause);
            _blendMode = node->_blendMode;
            _colorTransform = node->_colorTransform;
            _flashTransform = node->_flashTransform;
        }
        else
        {
            _ratio = 0;
            _flags = 0;
            _blendMode = BlendMode::Normal;
            _colorTransform.setIdentity();
            _flashTransform = Matrix();
        }
    }

    Rect MovieClip::getBounds() const
    {
        return _state->getBounds();
    }

    Point MovieClip::getLeafTranslatePoint(float movieScale) const
    {
        assert(isLeaf());
        auto translatePoint = (fla::Point*)&_leaf.translatePoint;
        if (translatePoint->isNull())
        {
            auto rt = _state->getBounds();
            *translatePoint = adjustPointForRender(rt);
        }
        return *translatePoint * movieScale;
    }

    Matrix MovieClip::nodeToParentTransform(float movieScale) const
    {
        auto flashTrans = _flashTransform;
        if (_moviePart)
        {
            flashTrans = _flashTransform * _moviePart->getTransform();
        }
        flashTrans.tx *= movieScale;
        flashTrans.ty *= movieScale;
        return flashTrans;
    }

    Matrix MovieClip::nodeToParentTransformTranslatePoint(float scale) const
    {
        auto matrix = nodeToParentTransform(scale);
        if (isLeaf())
        {
            auto pt = getLeafTranslatePoint(scale);
            matrix.translate(pt.x, pt.y);
        }
        return matrix;
    }

    const MovieClip* MovieClip::hitAtom(const Point& pt, float scale) const
    {
        if (isTree())
        {
            for (auto& node : _tree.subMovieClips)
            {
                auto matrix = node->nodeToParentTransformTranslatePoint(scale);
                matrix.invert();
                auto hitPt = matrix * pt;
                auto result = node->hitAtom(hitPt, scale);
                if (result)
                {
                    return result;
                }
            }
        }
        else
        {
            auto rt = _state->getBounds();
            rt *= scale;
            rt.x = 0;
            rt.y = 0;
            if (rt.isContainsPoint(pt))
            {
                return this;
            }
        }
        return nullptr;
    }

    void MovieClip::refreshSprites()
    {
        if (isTree())
        {
            for (auto& node : _tree.subMovieClips)
            {
                node->refreshSprites();
            }
        }
        else
        {
            s_safeReleaseSprite(&_leaf.sprite);
        }
    }

    void MovieClip::stepFrame(bool isRoot, bool isAuto)
    {
        if (!isTree())
        {
            return;
        }

        // 先处理子节点，再处理父节点
        if (!_tree.subMovieClips.empty())
        {
            // root节点，需要复制，防止外面修改
            if (isRoot)
            {
                RefPtrVector<MovieClip>::type array;
                array.assign(_tree.subMovieClips.begin(), _tree.subMovieClips.end());
                for (auto node : _tree.subMovieClips)
                {
                    node->stepFrame(false, isAuto);
                }
            }
            else
            {
                for (auto& node : _tree.subMovieClips)
                {
                    node->stepFrame(false, isAuto);
                }
            }
        }

        auto& sprite = static_cast<const DefinitionAnimation&>(*_state);
        if (sprite.getFrameCount() > 1 && !(libra::bit_test(_flags, Bit_Pause) && isAuto))
        {
            auto curFrame = libra_mode_inc(_curFrame, (int)sprite.getFrameCount());
            if (isAuto && _listener && curFrame == 0)
            {
                _listener->movieClipDidStartMovie(this);
            }
            _curFrame = curFrame;
            this->placeFrame(_curFrame);
        }

        if (isAuto && _listener)
        {
            _listener->movieClipDidStepFrame(this);
            if (sprite.getFrameCount() > 1 && _curFrame + 1 == sprite.getFrameCount())
            {
                _listener->movieClipDidFinishMovie(this);
            }
        }
    }

    void MovieClip::walk(const std::function<bool(MovieClip* clip)>& fun)
    {
        if (isTree())
        {
            for (auto& child : _tree.subMovieClips)
            {
                if (fun(child))
                {
                    child->walk(fun);
                }
            }
        }
    }

    void MovieClip::movieClipDidStepFrame(MovieClip*)
    {
    }

    void MovieClip::movieClipDidFinishMovie(MovieClip* node)
    {
        if (_listener != nullptr)
        {
            _listener->movieClipDidFinishMovie(node);
            assert(isTree());
            if (node->_listener == this && getMainSubNode() == node)
            {
                _listener->movieClipDidFinishMovie(this);
            }
        }
    }

    MovieGlobalData* MovieClip::getMovieGlobalData()
    {
        assert(_dataSource);
        return _dataSource->getMovieGlobalData(_definition);
    }
    

    MoviePartShareData* MovieClip::getMoviePartShareData()
    {
        assert(_dataSource);
        return _dataSource->getMoviePartShareData(_definition);
    }

    void MovieClip::movieClipDidStartMovie(MovieClip* node)
    {
        if (_listener != nullptr)
        {
            _listener->movieClipDidStartMovie(node);
            assert(isTree());
            if (node->_listener == this && getMainSubNode() == node)
            {
                _listener->movieClipDidStartMovie(this);
            }
        }
    }

    void MovieClip::stepFrameRatio(float ratio)
    {
        assert(ratio >= 0 && ratio <= 1);
        if (libra::bit_test(_flags, Bit_Pause) || !isTree())
        {
            return;
        }

        auto& sprite = static_cast<const DefinitionAnimation&>(*_state);
        if (sprite.getFrameCount() > 1)
        {
            auto nextFrameIndex = libra_mode_inc(_curFrame, (int)sprite.getFrameCount());
            auto& frame = sprite.getFrames()[_curFrame];
            auto& nextFrame = sprite.getFrames()[nextFrameIndex];
            placeFrame(frame, nextFrame, ratio);
        }

        for (auto& node : _tree.subMovieClips)
        {
            node->stepFrameRatio(ratio);
        }
    }

    MovieClip* MovieClip::getMainSubNode() const
    {
        assert(isTree());
        auto sprite = fla::ptr_case<DefinitionAnimation>(_state);
        if (sprite->getFrameCount() == 1)
        {
            auto& v = _tree.subMovieClips;
            if (!v.empty())
            {
                MovieClip* lastTree = nullptr;
                for (auto& node : v)
                {
                    if (node->isTree())
                    {
                        lastTree = node;
                        if (node->_tree.subMovieClips.size() > 1)
                        {
                            break;
                        }
                    }
                }
                return lastTree;
            }
        }
        return nullptr;
    }

    void MovieClip::goToFrame(int N)
    {
        assert(N < getFrameCount());
        if (!isTree())
        {
            return;
        }

        // 获取当前帧，假如就是第N帧，返回
        int curFrame = getCurrentFrame();
        if (curFrame == N)
        {
            return;
        }

        // 假如当前帧大于第N帧，需要跳回第0帧，在重新调用stepFrame
        if (curFrame > N)
        {
            resetToFirstFrame();
            curFrame = 0;
            assert(getCurrentFrame() == 0);
        }

        // 连续调用stepFrame, 进入第N帧
        for (int i = curFrame; i < N; i++)
        {
            stepFrame(true, false);
        }
        assert(getCurrentFrame() == N);
    }

    int MovieClip::getCurrentFrame() const
    {
        if (isTree())
        {
            auto node = getMainSubNode();
            if (node)
            {
                return node->getCurrentFrame();
            }
        }
        return _curFrame;
    }

    int MovieClip::getFrameCount() const
    {
        if (isTree())
        {
            auto node = getMainSubNode();
            if (node)
            {
                return node->getFrameCount();
            }
            auto sprite = fla::ptr_case<DefinitionAnimation>(_state);
            return (int)sprite->getFrameCount();
        }
        return 1;
    }

    template <typename Fun>
    bool MovieClip::changeState_impl(Fun findState)
    {
        if (_definition->getType() != DefinitionType::Role)
        {
            return false;
        }

        auto role = fla::ptr_case<DefinitionRole>(_definition);
        auto state = findState(role);
        if (state && _state != state)
        {
            auto oldState = _state;
            _state = state;

            auto movieShardData = getMovieGlobalData();
            MovieClip* node = this;
            for (;;)
            {
                if (node->isLeaf())
                {
                    break;
                }

                auto& subMoviewNodes = node->_tree.subMovieClips;
                if (subMoviewNodes.empty())
                {
                    break;
                }

                if (subMoviewNodes.size() > 1)
                {
                    for (auto& node : subMoviewNodes)
                    {
                        movieShardData->reusableMovieSet.add(node->_definition.get(), node);
                    }
                    break;
                }
                node = subMoviewNodes[0];
            }
            refreshNodes(oldState);
            movieShardData->reusableMovieSet.clear();
            return true;
        }
        return false;
    }

    void MovieClip::setPause(bool isPause)
    {
        libra::bit_set(&_flags, Bit_Pause, isPause);
        if (isTree())
        {
            for (auto& node : _tree.subMovieClips)
            {
                node->setPause(isPause);
            }
        }
    }

    void MovieClip::setPause(bool isPause, int Id)
    {
        if (_definition->getId() == Id)
        {
            setPause(isPause);
        }
        else
        {
            if (isTree())
            {
                for (auto& node : _tree.subMovieClips)
                {
                    node->setPause(isPause, Id);
                }
            }
        }
    }

    void MovieClip::setPause(bool isPause, const std::string& name)
    {
        assert(!name.empty());
        if (_definition->getName() == name)
        {
            setPause(isPause);
        }
        else
        {
            if (isTree())
            {
                for (auto& node : _tree.subMovieClips)
                {
                    node->setPause(isPause, name);
                }
            }
        }
    }

    bool MovieClip::hasState(const std::string& stateName)
    {
        if (_definition->getType() != DefinitionType::Role)
        {
            return false;
        }
        auto role = fla::ptr_case<DefinitionRole>(_definition);
        for (auto& state : role->getStates())
        {
            if (state.name == stateName)
            {
                return true;
            }
        }
        return false;
    }

    bool MovieClip::changeState(const std::string& stateName)
    {
        if (stateName.empty())
        {
            return false;
        }
        return changeState_impl([&](const DefinitionRole::Ptr& role)
                                {
                                    return role->findDefinition(stateName);
                                });
    }

    bool MovieClip::changeState(int index)
    {
        return changeState_impl([&](const DefinitionRole::Ptr& role)
                                {
                                    Definition::Ptr state;
                                    if (static_cast<size_t>(index) < role->getStates().size())
                                    {
                                        state = role->getStates()[index].definition;
                                    }
                                    return state;
                                });
    }

    void MovieClip::placeFrame(const AnimationFrame& currentFrame, const AnimationFrame& nextFrame, float ratio)
    {
        for (auto& obj : currentFrame)
        {
            if (obj.isRemoveObject())
            {
                continue;
            }

            MovieClip* node = findChildWithDepth(obj.depth());
            if (node == nullptr)
            {
                continue;
            }

            auto iter = nextFrame.findWithDepth(obj.depth());
            if (iter == nextFrame.end())
            {
                continue;
            }

            auto& nextObj = *iter;
            if (nextObj.hasCharacterID())
            {
                if (node->getMovieId() != nextObj.characterID())
                {
                    continue;
                }
            }

            if (obj.hasTrans() && nextObj.hasTrans())
            {
                auto trans = lerp(obj.trans(), nextObj.trans(), ratio);
                node->_flashTransform = trans;
            }

            if (obj.hasColorTrans() && nextObj.hasColorTrans())
            {
                auto colorTrans = lerp(obj.colorTrans(), nextObj.colorTrans(), ratio);
                node->_flags |= Bit_HasColorTransform;
                node->_colorTransform = colorTrans;
            }
        }
    }

    MovieClip* MovieClip::findChildWithDepth(int depth)
    {
        auto iter = s_findIterator(_tree.subMovieClips, depth);
        return s_getClip(_tree.subMovieClips, iter, depth);
    }

    std::string MovieClip::getMovieName() const
    {
        return _definition ? _definition->getName() : "";
    }

    std::string MovieClip::getStateName() const
    {
        if (!_state)
        {
            return "";
        }

        if (_definition->getType() != DefinitionType::Role)
        {
            return "default";
        }

        auto role = fla::ptr_case<DefinitionRole>(_definition);
        return role->stateName(_state);
    }

    int MovieClip::getMovieId() const
    {
        return _definition ? _definition->getId() : 0;
    }

    void MovieClip::setQuickSprite(TextureFrame* sprite)
    {
        assert(_leaf.sprite == nullptr);
        assert(isLeaf());

        if (sprite != nullptr)
        {
            _leaf.sprite = sprite;
            sprite->retain();
        }
    }

    MovieClip::Ptr MovieClip::newClipWithObject(const PlaceObject& obj)
    {
        assert(isTree());
        auto sprite = fla::ptr_case<DefinitionAnimation>(_state);
        Definition::Ptr definition = sprite->findDefinition(obj.characterID());
        MovieClip::Ptr newClip;

        if (!definition)
        {
            return newClip;
        }

        auto partShareData = getMoviePartShareData();
        MoviePart* moviePart = nullptr;

        if (partShareData)
        {
            moviePart = partShareData->find(definition->getId());
            if (moviePart)
            {
                assert(moviePart->getOriginDefinition() == definition);
                definition = moviePart->getDefintion();
            }
        }

        auto movieShareData = getMovieGlobalData();
        newClip = movieShareData->reusableMovieSet.reuseMoview(definition.get());
        if (newClip)
        {
            newClip->resetStatus(nullptr);
            if (newClip->isTree())
            {
                newClip->resetToFirstFrame();
            }
        }
        else
        {
            newClip = Ptr(movieShareData->allocMovieClip(definition, _dataSource), false);
            if (moviePart)
            {
                moviePart->addClip(newClip.get());
                if (moviePart->getStateIndex() != -1)
                {
                    newClip->changeState(moviePart->getStateIndex());
                }
            }
        }

        assert(moviePart == newClip->_moviePart);
        newClip->setListener(this);
        newClip->_flashTransform = Matrix();
        newClip->_depth = obj.depth();
        return newClip;
    }

    void MovieClip::placeChildNode(const PlaceObject& obj)
    {
        assert(isTree());
        if (obj.isRemoveObject())
        {
            s_removeClip(_tree.subMovieClips, obj.depth());
            return;
        }

        auto clip_iter = s_findIterator(_tree.subMovieClips, obj.depth());
        MovieClip* sub_clip = s_getClip(_tree.subMovieClips, clip_iter, obj.depth());

        if (obj.hasCharacterID())
        {
            if (sub_clip && (obj.characterID() != sub_clip->getMovieId() && !sub_clip->_moviePart))
            {
                MovieClip::Ptr newClip = newClipWithObject(obj);
                if (newClip)
                {
                    _tree.subMovieClips.assign(clip_iter, newClip.get());
                    newClip->resetStatus(sub_clip);
                }
                sub_clip = newClip.get();
            }

            if (sub_clip == nullptr)
            {
                MovieClip::Ptr newClip = newClipWithObject(obj);
                if (newClip)
                {
                    _tree.subMovieClips.insert(clip_iter, newClip.get());
                }
                sub_clip = newClip.get();
            }
        }

        if (sub_clip)
        {
            if (obj.hasTrans())
            {
                sub_clip->_flashTransform = obj.trans();
            }

            if (obj.hasBlendMode())
            {
                sub_clip->_blendMode = obj.blendMode();
                sub_clip->_flags |= Bit_HasBlendMode;
            }

            if (obj.hasColorTrans())
            {
                sub_clip->_colorTransform = obj.colorTrans();
                sub_clip->_flags |= Bit_HasColorTransform;
            }

            if (obj.hasRatio())
            {
                auto ratio = obj.ratio();
                if (sub_clip->_ratio != ratio && sub_clip->isLeaf())
                {
                    sub_clip->_ratio = ratio;
                    s_safeReleaseSprite(&sub_clip->_leaf.sprite);
                }
            }
        }
    }

    void MovieClip::retain()
    {
        _refCounter.add_fetch();
    }

    void MovieClip::release()
    {
        if (_refCounter.sub_fetch() == 0)
        {
            if (_moviePart)
            {
                _moviePart->removeClip(this);
            }
            getMovieGlobalData()->freeMovieClip(this);
        }
    }

    void MovieClip::placeFrame(const AnimationFrame& frame, int frameIndex)
    {
        assert(isTree());
        if (frameIndex == 0)
        {
            std::set<int> depthShouldRemove;
            for (auto& node : _tree.subMovieClips)
            {
                node->resetStatus(nullptr);
                depthShouldRemove.insert(node->getDepth());
            }

            for (auto& obj : frame)
            {
                placeChildNode(obj);
                depthShouldRemove.erase(obj.depth());
            }

            for (auto depth : depthShouldRemove)
            {
                s_removeClip(_tree.subMovieClips, depth);
            }
        }
        else
        {
            for (auto& obj : frame)
            {
                placeChildNode(obj);
            }
        }
    }
}
