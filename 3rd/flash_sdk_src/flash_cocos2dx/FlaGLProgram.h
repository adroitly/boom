//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLAPROGRAM_H__
#define __FLAPROGRAM_H__

#include "FlaConfig.h"

class FlaGLProgram : public cocos2d_bridge::Object
{
public:
    ~FlaGLProgram();
    static const GLchar* defaultVertextShaderBytes();
    static const GLchar* defaultFragmentShaderBytes();

    static FlaGLProgram* create(const GLchar* vertextShaderBytes, const GLchar* fragmentShaderBytes);
    static FlaGLProgram* getDefaultProgram();

    void setColorTransform(const GLfloat colorMult[4], const GLfloat colorAdd[4]);
    void setBlendMode(GLuint blendMode);
    virtual void setAdditionalInfo(void* info);

    void use();
    void setUniformsForBuiltins();

protected:
    bool initWithByteArrays(const GLchar* vertextShaderBytes, const GLchar* fragmentShaderBytes);
    void setup();
    GLuint getProgram() const
    {
        return _program;
    }
    FlaGLProgram();

private:
    void setupUniformLocation();
    bool compileShader(GLuint* shader, GLenum type, const GLchar* source);
    bool link();
    std::string logForOpenGLObject(GLuint object, cocos2d::GLInfoFunction infoFunc, cocos2d::GLLogFunction logFunc);
    std::string vertexShaderLog();
    std::string fragmentShaderLog();

private:
    GLuint _program;
    GLuint _vertShader;
    GLuint _fragShader;
    int _MVPMatrixLocation;
    int _texture0Location;
    int _colorMultLocation;
    int _colorAddLocation;
    int _colorBlendMode;
};

#endif
