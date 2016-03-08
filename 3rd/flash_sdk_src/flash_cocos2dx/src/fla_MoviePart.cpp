//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_MoviePart.h"
#include "fla_MovieClip.h"
#include "clover/Container.h"
#include "libra/libra_string.h"

namespace fla
{
    inline bool s_sortWithId(const MoviePart::Ptr& ptr, int Id)
    {
        return ptr->getId() < Id;
    }

    inline bool s_sortWithName(const MoviePart::Ptr& ptr, const char* name)
    {
        return strcmp(ptr->getName(), name) < 0;
    }

    void MoviePartShareData::addPart(MoviePart* part)
    {
        assert(!find(part->getId()));
        auto iter = std::lower_bound(_idParts.begin(), _idParts.end(), part->getId(), s_sortWithId);
        _idParts.insert(iter, part);

        if (!str_is_empty(part->getName()))
        {
            assert(!find(part->getName()));
            auto iter = std::lower_bound(_nameParts.begin(), _nameParts.end(), part->getName(), s_sortWithName);
            _nameParts.insert(iter, part);
        }
    }

    MoviePart* MoviePartShareData::find(int Id) const
    {
        auto iter = std::lower_bound(_idParts.begin(), _idParts.end(), Id, s_sortWithId);
        if (iter != _idParts.end() && (*iter)->getId() == Id)
        {
            return iter->get();
        }
        return nullptr;
    }

    MoviePart* MoviePartShareData::find(const std::string& name) const
    {
        auto iter = std::lower_bound(_nameParts.begin(), _nameParts.end(), name.c_str(), s_sortWithName);
        if (iter != _nameParts.end() && name == (*iter)->getName())
        {
            return iter->get();
        }
        return nullptr;
    }

    MoviePart::MoviePart(const Definition::Ptr& definition, MovieClipDataSource* dataSource)
        : _originDefintion(definition)
    {
        assert(definition);
        _dataSource = dataSource;
        _isHidden = false;
        _isChangeDefintion = false;
        _stateIndex = -1;
        _definition = definition;
    }

    MoviePart::Ptr MoviePart::create(const Definition::Ptr& definition, MovieClipDataSource* dataSource)
    {
        return MoviePart::Ptr(new MoviePart(definition, dataSource), false);
    }

    void MoviePart::addClip(MovieClip* clip)
    {
        assert(!clover::has_value(_clips, clip));
        _clips.push_back(clip);
        clip->setMoviePart(this);
    }

    void MoviePart::removeClip(MovieClip* clip)
    {
        clip->setMoviePart(nullptr);
        clover::erase_value(_clips, clip);
    }

    void MoviePart::replaceDefinition(const Definition::Ptr& definition)
    {
        assert(definition);
        if (_definition != definition)
        {
            _definition = definition;
            for (auto& clip : _clips)
            {
                clip->setDefinition(definition);
            }
            _isChangeDefintion = (_definition != _originDefintion);
        }
    }

    void MoviePart::resetDefinition()
    {
        replaceDefinition(_originDefintion);
        _isChangeDefintion = false;
    }

    bool MoviePart::changeState(const std::string& name)
    {
        if (_definition->getType() == DefinitionType::Role)
        {
            auto role = ptr_case<DefinitionRole>(_definition);
            auto idx = role->findStateIndex(name);
            if (idx != -1)
            {
                return changeState(idx);
            }
        }
        return false;
    }

    bool MoviePart::changeState(int index)
    {
        bool result = true;
        for (auto clip : _clips)
        {
            result = result && clip->changeState(index);
        }
        _stateIndex = index;
        return result;
    }

    MoviePart* MoviePart::findMoviePart(int Id)
    {
        auto clip = _clips.empty() ? nullptr : _clips.back();
        if (clip == nullptr)
        {
            return nullptr;
        }

        auto ptr = s_findMoviePart(_dataSource,
                                   _definition,
                                   clip,
                                   Id,
                                   [](fla::MovieClip* clip, int Id)
                                   {
                                       return clip->getDefinition()->getId() == Id;
                                   });
        return ptr;
    }

    MoviePart* MoviePart::findMoviePart(const std::string& name)
    {
        auto clip = _clips.empty() ? nullptr : _clips.back();
        if (clip == nullptr)
        {
            return nullptr;
        }
        auto ptr = s_findMoviePart(_dataSource,
                                   _definition,
                                   clip,
                                   name,
                                   [](fla::MovieClip* clip, const std::string& name)
                                   {
                                       return clip->getDefinition()->getName() == name;
                                   });
        return ptr;
    }
}
