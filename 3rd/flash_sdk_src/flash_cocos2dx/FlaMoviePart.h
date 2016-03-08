//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLAMOVIEPART_H__
#define __FLAMOVIEPART_H__

#include "FlaConfig.h"
#include "FlaDefinition.h"

namespace fla
{
    class MoviePart;
}

class FlaMoviePart final
{
public:
    FlaMoviePart();
    ~FlaMoviePart();

    FlaMoviePart(const FlaMoviePart& rhs);
    FlaMoviePart& operator=(const FlaMoviePart& rhs);

    explicit FlaMoviePart(fla::MoviePart* impl);
    fla::MoviePart* getRaw() const;

    bool isNull() const;

    void hide();
    void show();

    void replaceDefinition(const FlaDefinition& definition);
    void resetDefinition();

    bool changeState(const std::string& name);
    bool changeState(int index);

    void setTranslation(float tx, float ty);

    FlaMoviePart findMoviePart(int Id);
    FlaMoviePart findMoviePart(const std::string& name);

private:
    fla::MoviePart* _impl;
};

#endif
