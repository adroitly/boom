//
//  BWShaderProgram.h
//  Game
//
//  Created by HJC on 14-6-30.
//
//

#ifndef __BWSHADERPROGRAM__
#define __BWSHADERPROGRAM__

#include "FlaSDK.h"

namespace fla_ex
{
    class RoleGLProgram : public FlaGLProgram
    {
    public:
        static RoleGLProgram* getDefaultProgram();
        static void loadDefaultProgram(const char* fragString);

        void setShaderFlags(GLint flags[4]);

    private:
        virtual void setAdditionalInfo(void* info) override;
        void setupUniformLocation();
        int _shaderFlagsLocation;
        static RoleGLProgram* s_defaultProgram;
    };
}

#endif
