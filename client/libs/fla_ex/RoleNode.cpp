//
//  FlaRoleNode.cpp
//  WeAreHeros
//
//  Created by HJC on 14/11/21.
//
//

#include "RoleNode.h"
#include "SDKWrapper.h"
#include "core/base/fla_Base.h"

namespace fla_ex
{
    RoleNode* RoleNode::createWithDefinition(const FlaDefinition& definition, float scale)
    {
        if (definition.isNull() || definition.getMovieType() != FlaMovieType::Role)
        {
            return nullptr;
        }
        RoleNode* node = new RoleNode(definition, scale);
        node->autorelease();
        return node;
    }

    void RoleNode::setPixelFormat(FlaPixelFormat format)
    {
        _cacheStrategy.setPixelFormat(format);
    }

    RoleNode::RoleNode(const FlaDefinition& define, float scale) : FlaTimeMovieNode(define, scale)
    {
        _cacheStrategy.setPixelFormat(FlaPixelFormat::RGBA4444);
        setCacheStrategy(&_cacheStrategy);
        _cacheStrategy.setRoot(define);
        memset(_flags, 0, sizeof(_flags));

        /*
        _program = fla_ex::RoleGLProgram::getDefaultProgram();
        if (_program)
        {
            setFlaGLProgram(_program);
        }
         */
    }

    void RoleNode::setShaderFlags(GLint flags[4])
    {
        if (_program)
        {
            memcpy(_flags, flags, sizeof(_flags));
            setFlaGLProgramAdditionalInfo(_flags, nullptr);
        }
    }
}
