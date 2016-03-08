//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../FlaMovieNode.h"
#include "../../core/definition/fla_DefinitionUtils.h"
#include "../FlaGLProgram.h"
#include "./fla_MovieClip.h"
#include "./fla_MovieShareData.h"
#include <vector>
using namespace cocos2d;

namespace fla
{
    class MovieClipBridge final : public MovieClipListener, public MovieClipDataSource, boost::noncopyable
    {
    public:
        MovieClipBridge(FlaMovieNode* node, const fla::Definition::Ptr& definition, fla::MovieGlobalData* globalData)
        {
            _globalData = globalData;
            _outterNode = node;
            _nodeListener = nullptr;
            _rootClip.init(definition, this);
            _rootClip.setListener(this);
        }

        virtual void movieClipDidStartMovie(fla::MovieClip* node) override;
        virtual void movieClipDidFinishMovie(fla::MovieClip* node) override;
        virtual void movieClipDidStepFrame(fla::MovieClip* node) override;

        virtual MovieGlobalData* getMovieGlobalData(const Definition::Ptr& node) override
        {
            return _globalData;
        }

        virtual MoviePartShareData* getMoviePartShareData(const Definition::Ptr& node) override;
        virtual MoviePartShareData* getMoviePartShareDataForce(const Definition::Ptr& node) override;

        void setNodeListener(FlaMovieNodeListener* listener)
        {
            _nodeListener = listener;
        }

        FlaMovieNodeListener* getNodeListener() const
        {
            return _nodeListener;
        }

        MovieClip* getRootClip()
        {
            return &_rootClip;
        }

    private:
        MovieClip _rootClip;
        MoviePartShareData _partShareData;
        MovieGlobalData* _globalData;
        FlaMovieNodeListener* _nodeListener;
        FlaMovieNode* _outterNode;
        std::vector<MoviePartShareData> _partShareDatas;
    };

    MoviePartShareData* MovieClipBridge::getMoviePartShareData(const Definition::Ptr& node)
    {
        if (Definition_isSamePackage(node, _rootClip.getDefinition()))
        {
            return &_partShareData;
        }

        auto& md5 = node->getDataInfo()->getMd5String();
        for (auto& data : _partShareDatas)
        {
            if (md5 == data.md5str)
            {
                return &data;
            }
        }
        return nullptr;
    }

    MoviePartShareData* MovieClipBridge::getMoviePartShareDataForce(const Definition::Ptr& node)
    {
        MoviePartShareData* data = getMoviePartShareData(node);
        if (data == nullptr)
        {
            auto& md5 = node->getDataInfo()->getMd5String();
            _partShareDatas.push_back(fla::MoviePartShareData());
            data = &_partShareDatas.back();
            data->md5str = md5;
        }
        return data;
    }

    void MovieClipBridge::movieClipDidStartMovie(MovieClip* node)
    {
        if (node == &_rootClip)
        {
            if (_outterNode->onMovieStart)
            {
                _outterNode->onMovieStart(_outterNode);
            }

            if (_nodeListener)
            {
                _nodeListener->FlaMovieNodeDidStartMovie(_outterNode);
            }
        }
    }

    void MovieClipBridge::movieClipDidFinishMovie(fla::MovieClip* node)
    {
        if (node == &_rootClip)
        {
            if (_outterNode->onMovieFinish)
            {
                _outterNode->onMovieFinish(_outterNode);
            }

            if (_nodeListener)
            {
                _nodeListener->FlaMovieNodeDidFinishMovie(_outterNode);
            }
        }
    }

    void MovieClipBridge::movieClipDidStepFrame(fla::MovieClip* node)
    {
        if (node == &_rootClip)
        {
            if (_outterNode->onMovieStepFrame)
            {
                _outterNode->onMovieStepFrame(_outterNode);
            }

            if (_nodeListener)
            {
                _nodeListener->FlaMovieNodeDidStepFrame(_outterNode);
            }
        }
    }
}

FlaMovieNode* FlaMovieNode::createWithDefinition(const FlaDefinition& definition)
{
    return FlaMovieNode::createWithDefinition(definition, 1);
}

FlaMovieNode* FlaMovieNode::createWithDefinition(const FlaDefinition& definition, float scale)
{
    if (definition.isNull())
    {
        return nullptr;
    }
    FlaMovieNode* node = new FlaMovieNode(definition, scale);
    node->autorelease();
    return node;
}

static fla::MovieGlobalData* s_globalShareData;

FlaMovieNode::FlaMovieNode(const FlaDefinition& definition, float scale)
{
    // MovieShareData的分配需要最前面
    if (s_globalShareData == nullptr)
    {
        s_globalShareData = new fla::MovieGlobalData();
    }
    _movieGlobalData = s_globalShareData;
    _movieGlobalData->retain();

    _movieClipBridge = new fla::MovieClipBridge(this, definition.getRaw(), _movieGlobalData);
    _movieClip = _movieClipBridge->getRootClip();
    assert(_movieClip);
    _movieScale = scale;
    _cacheStrategy = nullptr;
    _blendFunc = { CC_BLEND_SRC, CC_BLEND_DST };
    _glProgram = nullptr;
    setFlaGLProgram(FlaGLProgram::getDefaultProgram());
    refreshMovieBounds();
    setAnchorPoint(cocos2d_bridge::Point(0.5, 0.5));
    _drawSceneColor = false;
    _glAdditionalInfo = nullptr;
    _glAddtionFreeFun = nullptr;
    _blurClipLevel = -1;
    _autoFlipY = true;
}

FlaMovieNode::~FlaMovieNode()
{
    CC_SAFE_RELEASE(_glProgram);
    if (_movieClipBridge)
    {
        delete _movieClipBridge;
    }

    if (_glAddtionFreeFun && _glAdditionalInfo)
    {
        _glAddtionFreeFun(_glAdditionalInfo);
    }

    // MovieShareData的释放需要放最后面
    assert(_movieGlobalData == s_globalShareData);
    _movieGlobalData->release();
    if (s_globalShareData->isUnique())
    {
        s_globalShareData->release();
        s_globalShareData = nullptr;
    }
}

void FlaMovieNode::setListener(FlaMovieNodeListener* listener)
{
    _movieClipBridge->setNodeListener(listener);
}

FlaMovieNodeListener* FlaMovieNode::getListener() const
{
    return _movieClipBridge->getNodeListener();
}

FlaMoviePart FlaMovieNode::findMoviePart(int Id)
{
    auto ptr = s_findMoviePart(_movieClipBridge,
                               _movieClip->getDefinition(),
                               _movieClip,
                               Id,
                               [](fla::MovieClip* clip, int Id)
                               {
                                   return clip->getDefinition()->getId() == Id;
                               });
    return FlaMoviePart(ptr);
}

FlaMoviePart FlaMovieNode::findMoviePart(const std::string& name)
{
    auto ptr = s_findMoviePart(_movieClipBridge,
                               _movieClip->getDefinition(),
                               _movieClip,
                               name,
                               [](fla::MovieClip* clip, const std::string& name)
                               {
                                   return clip->getDefinition()->getName() == name;
                               });
    return FlaMoviePart(ptr);
}

void FlaMovieNode::setAutoFlipY(bool flag)
{
    _autoFlipY = flag;
}

void FlaMovieNode::refreshMovieBounds()
{
#if COCOS2D_VERSION >= 0x00030000
    _transformDirty = true;
#else
    m_bTransformDirty = true;
#endif

    auto rt = _movieClip->getDefinition()->getBounds();
    rt *= _movieScale;
    _movieBounds = cocos2d_bridge::Rect(rt.x, rt.y, rt.width, rt.height);
    setContentSize(cocos2d_bridge::Size(rt.width, rt.height));
}

void FlaMovieNode::setBlendFunc(const cocos2d_bridge::BlendFunc& fun)
{
    _blendFunc = fun;
}

void FlaMovieNode::setFlaGLProgram(FlaGLProgram* program)
{
    assert(program);
    clover::intrusive_ptr_safe_assign(_glProgram, program);
}

void FlaMovieNode::setFlaGLProgramAdditionalInfo(void* info, void (*freeFun)(void* info))
{
    _glAdditionalInfo = info;
    _glAddtionFreeFun = freeFun;
}

FlaGLProgram* FlaMovieNode::getFlaGLProgram() const
{
    return _glProgram;
}

void FlaMovieNode::setCacheStrategy(FlaCacheStrategy* cacheStrategy)
{
    _cacheStrategy = cacheStrategy;
}

FlaCacheStrategy* FlaMovieNode::getCacheStrategy() const
{
    return _cacheStrategy;
}

void FlaMovieNode::stepFrame()
{
    assert(_movieClip);
    _movieClip->stepFrame(true, true);
}

void FlaMovieNode::stepFrameRatio(float ratio)
{
    assert(_movieClip);
    _movieClip->stepFrameRatio(ratio);
}

void FlaMovieNode::pauseStep()
{
    assert(_movieClip);
    _movieClip->setPause(true);
}

void FlaMovieNode::pauseStep(int Id)
{
    assert(_movieClip);
    _movieClip->setPause(true, Id);
}

void FlaMovieNode::pauseStep(const std::string& name)
{
    assert(_movieClip);
    _movieClip->setPause(true, name);
}

void FlaMovieNode::resumeStep()
{
    assert(_movieClip);
    _movieClip->setPause(false);
}

void FlaMovieNode::resumeStep(int Id)
{
    assert(_movieClip);
    _movieClip->setPause(false, Id);
}

void FlaMovieNode::resumeStep(const std::string& name)
{
    assert(_movieClip);
    _movieClip->setPause(false, name);
}

void FlaMovieNode::goToFrame(int N)
{
    assert(_movieClip);
    _movieClip->goToFrame(N);
}

int FlaMovieNode::getCurrentFrame() const
{
    assert(_movieClip);
    return _movieClip->getCurrentFrame();
}

int FlaMovieNode::getFrameCount() const
{
    assert(_movieClip);
    return _movieClip->getFrameCount();
}

bool FlaMovieNode::hasState(const std::string& stateName)
{
    assert(_movieClip);
    return _movieClip->hasState(stateName);
}

bool FlaMovieNode::changeState(const std::string& stateName)
{
    assert(_movieClip);
    return _movieClip->changeState(stateName);
}

bool FlaMovieNode::changeState(int index)
{
    assert(_movieClip);
    return _movieClip->changeState(index);
}

FlaDefinition FlaMovieNode::getDefinition() const
{
    assert(_movieClip);
    return FlaDefinition(_movieClip->getDefinition().get());
}

void FlaMovieNode::setDefinition(const FlaDefinition& definition)
{
    assert(_movieClip);
    _movieClip->setDefinition(definition.getRaw());
    refreshMovieBounds();
}

float FlaMovieNode::getMovieScale() const
{
    return _movieScale;
}

void FlaMovieNode::setDrawSceneColor(bool sceneColor)
{
    _drawSceneColor = sceneColor;
}

void FlaMovieNode::setMovieScale(float scale)
{
    if (_movieScale != scale)
    {
        assert(_movieClip);
        _movieScale = scale;
        _movieClip->refreshSprites();
        refreshMovieBounds();
    }
}

FlaMovieType FlaMovieNode::getMovieType() const
{
    assert(_movieClip);
    return (FlaMovieType)_movieClip->getDefinition()->getType();
}

std::string FlaMovieNode::getMovieName() const
{
    assert(_movieClip);
    return _movieClip->getMovieName();
}

std::string FlaMovieNode::getStateName() const
{
    assert(_movieClip);
    return _movieClip->getStateName();
}

int FlaMovieNode::getMovieId() const
{
    assert(_movieClip);
    return _movieClip->getDefinition()->getId();
}

cocos2d_bridge::Size FlaMovieNode::getMovieSize() const
{
    return _movieBounds.size;
}

void FlaMovieNode::refreshSprites()
{
    assert(_movieClip);
    _movieClip->refreshSprites();
}

void FlaMovieNode::setOpacity(GLubyte opacity)
{
    cocos2d::Node::setOpacity(opacity);
    refreshColorTransform();
}

void FlaMovieNode::updateDisplayedOpacity(GLubyte parentOpacity)
{
    cocos2d::Node::updateDisplayedOpacity(parentOpacity);
    refreshColorTransform();
}

void FlaMovieNode::setColor(const cocos2d_bridge::Color3B& color)
{
    cocos2d::Node::setColor(color);
    refreshColorTransform();
}

void FlaMovieNode::updateDisplayedColor(const cocos2d_bridge::Color3B& parentColor)
{
    cocos2d::Node::updateDisplayedColor(parentColor);
    refreshColorTransform();
}

void FlaMovieNode::refreshColorTransform()
{
    const auto kFactor = 1.0 / 255.0;
    auto r = _displayedColor.r * kFactor;
    auto g = _displayedColor.g * kFactor;
    auto b = _displayedColor.b * kFactor;
    auto a = _displayedOpacity * kFactor;
    auto trans = fla::ColorTransform::make(r, g, b, a, 0, 0, 0, 0);
    _movieClip->setColorTransform(trans);
}

void FlaMovieNode::setColorTransform(GLfloat colorMult[4], GLfloat colorAdd[4])
{
    assert(_movieClip);
    auto trans = fla::ColorTransform::make(colorMult[0],
                                           colorMult[1],
                                           colorMult[2],
                                           colorMult[3],
                                           colorAdd[0],
                                           colorAdd[1],
                                           colorAdd[2],
                                           colorAdd[3]);
    _movieClip->setColorTransform(trans);
}

static void s_drawBackground(const void* context, const fla::Rect& bounds, const fla::Color4& tmpColor)
{
    // std::cout << "Hello, World" << std::endl;
    auto color = cocos2d_bridge::Color4F_Make(tmpColor.red, tmpColor.green, tmpColor.blue, tmpColor.alpha);
    auto p0 = fla::Point(bounds.x, bounds.y);
    auto p1 = fla::Point(bounds.x + bounds.width, bounds.y + bounds.height);

#if COCOS2D_VERSION >= 0x00030000
    auto matrix = (fla::Matrix*)context;

    p0 = *matrix * p0;
    p1 = *matrix * p1;

    DrawPrimitives::drawSolidRect(cocos2d_bridge::Point(p0.x, p0.y), cocos2d_bridge::Point(p1.x, p1.y), color);

#else
    FLA_UNUSED(context);
    ccDrawSolidRect(cocos2d_bridge::Point(p0.x, p0.y), cocos2d_bridge::Point(p1.x, p1.y), color);
#endif
}

void FlaMovieNode::innerDraw(const void* context)
{
    assert(_movieClip);
    if (_drawSceneColor)
    {
        auto definitionType = _movieClip->getDefinition()->getType();
        if (definitionType == fla::DefinitionType::Scene)
        {
            auto scene = fla::ptr_case<fla::DefinitionScene>(_movieClip->getDefinition());
            fla::Rect rt;
            rt.width = scene->getSize().width * _movieScale;
            rt.height = scene->getSize().height * _movieScale;
            s_drawBackground(context, rt, scene->getColor());
        }
        else if (definitionType == fla::DefinitionType::Package)
        {
            auto package = fla::ptr_case<fla::DefinitionPackage>(_movieClip->getDefinition());
            auto pts = package->getScenePositions();
            auto& screens = package->getScenes();

            for (size_t idx = 0; idx < pts.size(); idx++)
            {
                auto& scene = screens[idx];
                fla::Rect rt(pts[idx].x, pts[idx].y, scene->getSize().width, scene->getSize().height);
                rt *= _movieScale;
                s_drawBackground(context, rt, scene->getColor());
            }
        }
    }

#if COCOS2D_VERSION >= 0x00030000
    auto winSize = Director::getInstance()->getWinSize();
    _movieGlobalData->renderer.setClipEnable(true, _blurClipLevel, fla::Rect(0, 0, winSize.width, winSize.height));
#endif

    auto matrix = reinterpret_cast<const fla::Matrix*>(context);
    fla::BatchRenderInfo info;
    info.blendFunc = _blendFunc;
    info.glProgram = _glProgram;
    info.shaderInfo = _glAdditionalInfo;
    info.movieScale = _movieScale;
    info.root = getDefinition();
    info.cacheStrategy = (_cacheStrategy ? _cacheStrategy : this);
    _movieGlobalData->renderer.visit(_movieClip, *matrix, info);
}

void FlaMovieNode::setBlurLevelClip(bool flag, int level)
{
    if (flag)
    {
        _blurClipLevel = level;
    }
    else
    {
        _blurClipLevel = -1;
    }
}

#if COCOS2D_VERSION >= 0x00030000
#include "math/TransformUtils.h"
static void GLToMatrix(const GLfloat* m, fla::Matrix* t)
{
    t->a = m[0];
    t->b = m[1];
    t->c = m[4];
    t->d = m[5];
    t->tx = m[12];
    t->ty = m[13];
}

void FlaMovieNode::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = [=]
    {
        fla::Matrix t;
        GLToMatrix(transform.m, &t);
        innerDraw(&t);
    };
    renderer->addCommand(&_customCommand);
}

const cocos2d::Mat4& FlaMovieNode::getNodeToParentTransform() const
{
    if (_transformDirty)
    {
        AffineTransform trans;
        GLToCGAffine(cocos2d_bridge::NodeRGBA::getNodeToParentTransform().m, &trans);

        if (_autoFlipY)
        {
            auto flashTrans = cocos2d::AffineTransformMake(1, 0, 0, -1, 0, _movieBounds.size.height);
            flashTrans = cocos2d::AffineTransformTranslate(flashTrans, -_movieBounds.origin.x, -_movieBounds.origin.y);
            trans = cocos2d::AffineTransformConcat(flashTrans, trans);
        }

        _transformDirty = false;
        cocos2d::CGAffineToGL(trans, _transform.m);
    }
    return _transform;
}
#else
void FlaMovieNode::draw()
{
    fla::Matrix matrix;
    innerDraw(&matrix);
}

CCAffineTransform FlaMovieNode::nodeToParentTransform()
{
    if (m_bTransformDirty)
    {
        CCAffineTransform trans = CCNode::nodeToParentTransform();
        if (_autoFlipY)
        {
            CCAffineTransform flashTrans = CCAffineTransformMake(1, 0, 0, -1, 0, _movieBounds.size.height);
            flashTrans = CCAffineTransformTranslate(flashTrans, -_movieBounds.origin.x, -_movieBounds.origin.y);
            trans = CCAffineTransformConcat(flashTrans, trans);
        }
        m_bTransformDirty = false;
        m_sTransform = trans;
    }
    return m_sTransform;
}
#endif

bool FlaMovieNode::isAtomHitted(const cocos2d_bridge::Point& pt) const
{
    assert(_movieClip);
    auto matrix = _movieClip->nodeToParentTransformTranslatePoint(_movieScale);
    matrix.invert();
    auto hitPt = matrix * fla::Point(pt.x, pt.y);
    return _movieClip->hitAtom(hitPt, _movieScale) != nullptr;
}

FlaTimeMovieNode* FlaTimeMovieNode::createWithDefinition(const FlaDefinition& definition)
{
    return createWithDefinition(definition, 1.0);
}

FlaTimeMovieNode* FlaTimeMovieNode::createWithDefinition(const FlaDefinition& definition, float scale)
{
    if (definition.isNull())
    {
        return nullptr;
    }
    FlaTimeMovieNode* node = new FlaTimeMovieNode(definition, scale);
    node->autorelease();
    return node;
}

FlaTimeMovieNode::FlaTimeMovieNode(const FlaDefinition& definition, float scale) : FlaMovieNode(definition, scale)
{
    _stepTime = 0;
    _enableRatio = false;
    _frameTime = 1.0 / definition.getFrameRate();
}

FlaTimeMovieNode::~FlaTimeMovieNode()
{
    _enableRatio = false;
}

void FlaTimeMovieNode::time_update(float time)
{
    this->retain();
    _stepTime += time;
    while (_stepTime >= _frameTime)
    {
        if (cocos2d_bridge::Object_getReferenceCount(this) > 1)
        {
            this->stepFrame();
        }
        _stepTime -= _frameTime;
    }

    if (_enableRatio)
    {
        float ratio = _stepTime / _frameTime;
        this->stepFrameRatio(ratio);
    }
    this->release();
}

void FlaTimeMovieNode::time_setEnableRatio(bool flag)
{
    _enableRatio = flag;
}

void FlaTimeMovieNode::time_setFrameRate(float frameRate)
{
    _frameTime = 1.0 / frameRate;
}
