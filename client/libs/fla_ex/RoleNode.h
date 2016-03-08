//
//  FlaRoleNode.h
//  WeAreHeros
//
//  Created by HJC on 14/11/21.
//
//

#ifndef __FLAROLENODE_H__
#define __FLAROLENODE_H__

#include "FlaMovieNode.h"
#include "RoleCacheStrategy.h"
#include "RoleGLProgram.h"

namespace fla_ex
{
    class RoleNode : public FlaTimeMovieNode
    {
    public:
        static RoleNode* createWithDefinition(const FlaDefinition& definition, float scale);

        void setShaderFlags(GLint flags[4]);
        
        void setPixelFormat(FlaPixelFormat format);

    private:
        RoleNode(const FlaDefinition& define, float scale);
        RoleCacheStrategy _cacheStrategy;
        cocos2d::RefPtr<fla_ex::RoleGLProgram> _program;
        GLint _flags[4];
    };
}

#endif
