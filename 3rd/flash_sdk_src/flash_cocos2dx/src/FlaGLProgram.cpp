//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../FlaGLProgram.h"
#include "../FlaResourceCache.h"
#include "clover/ScopeGuard.h"
#include "cocos2d_bridge.h"
using namespace cocos2d;

#ifndef STRINGIFY
#define STRINGIFY(A) #A
#endif

static const char* s_fragmentShaderIncludes = STRINGIFY(

    varying vec2 v_texCoord;
    uniform vec4 flash_colorMult;
    uniform vec4 flash_colorAdd;
    uniform int flash_blendMode;

    vec4 fla_getColor()
    {
        vec4 color = texture2D(CC_Texture0, v_texCoord);
        color = color * flash_colorMult + flash_colorAdd * color.a;
        color = color * flash_colorMult.a;
        return color;
    }

    vec4 fla_useBlendMode(vec4 color)
    {
        if (flash_blendMode == 10)
        {
            return vec4(1.0, 1.0, 1.0, 1.0) * color.a;
        }
        else if (flash_blendMode == 6)
        {
            return vec4(1.0, 1.0, 1.0, 1.0) * (1.0 - color.a) + color;
        }
        return color;
    });

static const char* s_defaultFragmentShaderBytes = STRINGIFY(

    void main()
    {
        vec4 color = fla_getColor();
        gl_FragColor = color;
        //  gl_FragColor = fla_useBlendMode(color);
    });

static const char* s_defaultVertextShaderBytes = STRINGIFY(

    varying vec2 v_texCoord;
    attribute vec4 a_position;
    attribute vec2 a_texCoord;
    void main()
    {
        gl_Position = CC_MVPMatrix * a_position;
        v_texCoord = a_texCoord;
    });

FlaGLProgram::FlaGLProgram()
{
    _colorMultLocation = 0;
    _colorAddLocation = 0;
    _program = 0;
    _vertShader = 0;
    _fragShader = 0;
    _MVPMatrixLocation = 0;
    _texture0Location = 0;
    _colorBlendMode = 0;
}

FlaGLProgram::~FlaGLProgram()
{
    if (_vertShader)
    {
        glDeleteShader(_vertShader);
    }

    if (_fragShader)
    {
        glDeleteShader(_fragShader);
    }

    _vertShader = _fragShader = 0;

    if (_program)
    {
        cocos2d_bridge::GLDeleteProgram(_program);
    }
}

const GLchar* FlaGLProgram::defaultVertextShaderBytes()
{
    return s_defaultVertextShaderBytes;
}

const GLchar* FlaGLProgram::defaultFragmentShaderBytes()
{
    return s_defaultFragmentShaderBytes;
}

FlaGLProgram* FlaGLProgram::create(const GLchar* vertextShaderBytes, const GLchar* fragmentShaderBytes)
{
    FlaGLProgram* program = new FlaGLProgram();
    if (!program->initWithByteArrays(vertextShaderBytes, fragmentShaderBytes))
    {
        delete program;
        return nullptr;
    }

    program->autorelease();
    program->setup();

    return program;
}

std::string FlaGLProgram::logForOpenGLObject(GLuint object, GLInfoFunction infoFunc, GLLogFunction logFunc)
{
    GLint logLength = 0, charsWritten = 0;

    infoFunc(object, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength < 1)
    {
        return "";
    }

    char* logBytes = (char*)malloc(logLength);
    CLOVER_SCOPE_EXIT
    {
        free(logBytes);
    };

    logFunc(object, logLength, &charsWritten, logBytes);
    return logBytes;
}

std::string FlaGLProgram::vertexShaderLog()
{
    return logForOpenGLObject(_vertShader, (GLInfoFunction)&glGetShaderiv, (GLLogFunction)&glGetShaderInfoLog);
}

std::string FlaGLProgram::fragmentShaderLog()
{
    return logForOpenGLObject(_fragShader, (GLInfoFunction)&glGetShaderiv, (GLLogFunction)&glGetShaderInfoLog);
}

bool FlaGLProgram::compileShader(GLuint* shader, GLenum type, const GLchar* source)
{
    GLint status;

    if (!source)
    {
        return false;
    }

    const GLchar* sources[] =
    {
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32 && CC_TARGET_PLATFORM != CC_PLATFORM_LINUX && \
     CC_TARGET_PLATFORM != CC_PLATFORM_MAC && CC_TARGET_PLATFORM != CC_PLATFORM_QT)
        (type == GL_VERTEX_SHADER ? "precision highp float;\n" : "precision mediump float;\n"),
#endif
        "uniform mat4 CC_MVPMatrix;\n"
        "uniform sampler2D CC_Texture0;\n"
        "//CC INCLUDES END\n\n",
        (type == GL_VERTEX_SHADER) ? "" : s_fragmentShaderIncludes,
        source,
    };

    *shader = glCreateShader(type);
    glShaderSource(*shader, sizeof(sources) / sizeof(*sources), sources, NULL);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        GLsizei length;
        glGetShaderiv(*shader, GL_SHADER_SOURCE_LENGTH, &length);
        GLchar* src = (GLchar*)malloc(sizeof(GLchar) * length);
        CLOVER_SCOPE_EXIT
        {
            free(src);
        };

        glGetShaderSource(*shader, length, NULL, src);
        CCLOG("cocos2d: ERROR: Failed to compile shader:\n%s", src);

        if (type == GL_VERTEX_SHADER)
        {
            CCLOG("cocos2d: %s", vertexShaderLog().c_str());
        }
        else
        {
            CCLOG("cocos2d: %s", fragmentShaderLog().c_str());
        }
    }
    return (status == GL_TRUE);
}

bool FlaGLProgram::initWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray)
{
    _program = glCreateProgram();
    CHECK_GL_ERROR_DEBUG();

    _vertShader = _fragShader = 0;

    if (vShaderByteArray)
    {
        if (!compileShader(&_vertShader, GL_VERTEX_SHADER, vShaderByteArray))
        {
            CCLOG("cocos2d: ERROR: Failed to compile vertex shader");
            return false;
        }
    }

    // Create and compile fragment shader
    if (fShaderByteArray)
    {
        if (!compileShader(&_fragShader, GL_FRAGMENT_SHADER, fShaderByteArray))
        {
            CCLOG("cocos2d: ERROR: Failed to compile fragment shader");
            return false;
        }
    }

    if (_vertShader)
    {
        glAttachShader(_program, _vertShader);
    }
    CHECK_GL_ERROR_DEBUG();

    if (_fragShader)
    {
        glAttachShader(_program, _fragShader);
    }
    CHECK_GL_ERROR_DEBUG();

    return true;
}

void FlaGLProgram::setup()
{
    glBindAttribLocation(_program, cocos2d_bridge::kVertexAttrib_Position, kCCBrightAttributeNamePosition);
    glBindAttribLocation(_program, cocos2d_bridge::kVertexAttrib_TexCoords, kCCBrightAttributeNameTexCoord);

    this->link();
    this->setupUniformLocation();
    CHECK_GL_ERROR_DEBUG();
}

bool FlaGLProgram::link()
{
    assert(_program != 0);
    GLint status = GL_TRUE;
    glLinkProgram(_program);

    if (_vertShader)
    {
        glDeleteShader(_vertShader);
    }

    if (_fragShader)
    {
        glDeleteShader(_fragShader);
    }

    _vertShader = _fragShader = 0;
    return (status == GL_TRUE);
}

FlaGLProgram* FlaGLProgram::getDefaultProgram()
{
    const char* shaderKey = "__flash://Shader_Default";
    auto program = FlaResourceCache::getInstance().programForKey(shaderKey);
    if (program == nullptr)
    {
        program = FlaGLProgram::create(s_defaultVertextShaderBytes, s_defaultFragmentShaderBytes);
        FlaResourceCache::getInstance().setGLProgram(program, shaderKey);
    }
    return program;
}

void FlaGLProgram::setupUniformLocation()
{
    _colorMultLocation = glGetUniformLocation(_program, "flash_colorMult");
    _colorAddLocation = glGetUniformLocation(_program, "flash_colorAdd");
    _colorBlendMode = glGetUniformLocation(_program, "flash_blendMode");
    _texture0Location = glGetUniformLocation(_program, "CC_Texture0");
    _MVPMatrixLocation = glGetUniformLocation(_program, "CC_MVPMatrix");
}

void FlaGLProgram::setColorTransform(const GLfloat colorMult[4], const GLfloat colorAdd[4])
{
    glUniform4fv((GLint)_colorMultLocation, (GLsizei)1, colorMult);
    glUniform4fv((GLint)_colorAddLocation, (GLsizei)1, colorAdd);
}

void FlaGLProgram::setBlendMode(GLuint blendMode)
{
    glUniform1i(_colorBlendMode, blendMode);
}

void FlaGLProgram::setAdditionalInfo(void* info)
{
    (void)info;
}

void FlaGLProgram::use()
{
    cocos2d_bridge::GLUseProgram(_program);
}

#if COCOS2D_VERSION >= 0x00030000
inline void GLSetMVPMatrix(int mvpLocation)
{
    auto director = cocos2d::Director::getInstance();
    auto matrixP = director->getMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    auto matrixMV = director->getMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    auto matrixMVP = matrixP * matrixMV;
    glUniformMatrix4fv(mvpLocation, (GLsizei)1, GL_FALSE, matrixMVP.m);
}
#else
inline void GLSetMVPMatrix(int mvpLocation)
{
    kmMat4 matrixP;
    kmMat4 matrixMV;
    kmMat4 matrixMVP;

    kmGLGetMatrix(KM_GL_PROJECTION, &matrixP);
    kmGLGetMatrix(KM_GL_MODELVIEW, &matrixMV);

    kmMat4Multiply(&matrixMVP, &matrixP, &matrixMV);
    glUniformMatrix4fv(mvpLocation, (GLsizei)1, GL_FALSE, matrixMVP.mat);
}
#endif

void FlaGLProgram::setUniformsForBuiltins()
{
    GLSetMVPMatrix(_MVPMatrixLocation);
}
