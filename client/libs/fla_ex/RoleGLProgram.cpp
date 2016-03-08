//
//  BWShaderProgram.cpp
//  Game
//
//  Created by HJC on 14-6-30.
//
//

#include "RoleGLProgram.h"
#include "clover/KeyValue.h"
using namespace cocos2d;

namespace fla_ex
{
    RoleGLProgram* RoleGLProgram::s_defaultProgram = nullptr;
    RoleGLProgram* RoleGLProgram::getDefaultProgram()
    {
        return s_defaultProgram;
    }

    void RoleGLProgram::loadDefaultProgram(const char* fragString)
    {
        if (fragString == nullptr)
        {
            s_defaultProgram->release();
            s_defaultProgram = nullptr;
            return;
        }

        auto program = new RoleGLProgram();
        if (!program->initWithByteArrays(FlaGLProgram::defaultVertextShaderBytes(), fragString))
        {
            delete program;
            return;
        }

        program->setup();
        program->setupUniformLocation();

        if (s_defaultProgram)
        {
            s_defaultProgram->release();
        }
        s_defaultProgram = program;
    }

    void RoleGLProgram::setupUniformLocation()
    {
        _shaderFlagsLocation = glGetUniformLocation(this->getProgram(), "shader_flags");
    }

    void RoleGLProgram::setShaderFlags(GLint flags[4])
    {
        glUniform4i(_shaderFlagsLocation, flags[0], flags[1], flags[2], flags[3]);
    }

    void RoleGLProgram::setAdditionalInfo(void* info)
    {
        assert(info);
        setShaderFlags((GLint*)info);
    }
}
