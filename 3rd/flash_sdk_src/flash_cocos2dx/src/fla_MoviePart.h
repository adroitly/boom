//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_MOVIEPART_H__
#define __FLA_MOVIEPART_H__

#include <string>
#include <vector>
#include "core/base/fla_Ref.h"
#include "core/definition/fla_Definition.h"
#include "clover/ptr_vector.h"
#include "fla_MovieClip.h"

namespace fla
{
    class MoviePart;
    class MovieClip;
    typedef boost::intrusive_ptr<MoviePart> MoviePartPtr;

    class MoviePartShareData final
    {
    public:
        void addPart(MoviePart* part);
        MoviePart* find(int Id) const;
        MoviePart* find(const std::string& name) const;

        std::string md5str;

    private:
        std::vector<MoviePartPtr> _idParts;
        std::vector<MoviePartPtr> _nameParts;
    };

    class MoviePart : public fla::Ref<MoviePart>
    {
    public:
        static MoviePart::Ptr create(const Definition::Ptr& definition, MovieClipDataSource* dataSource);

        void hide()
        {
            _isHidden = true;
        }
        void show()
        {
            _isHidden = false;
        }
        bool isHidden() const
        {
            return _isHidden;
        }

        void replaceDefinition(const Definition::Ptr& definition);
        void resetDefinition();

        bool isChangeDefintion() const
        {
            return _isChangeDefintion;
        }
        const Definition::Ptr& getOriginDefinition() const
        {
            return _originDefintion;
        }
        const Definition::Ptr& getDefintion() const
        {
            return _definition;
        }

        void addClip(MovieClip* clip);
        void removeClip(MovieClip* clip);

        const char* getName() const
        {
            return _originDefintion->getName();
        }
        int getId() const
        {
            return _originDefintion->getId();
        }

        bool changeState(const std::string& stateName);
        bool changeState(int index);

        int getStateIndex() const
        {
            return _stateIndex;
        }

        void setTranslation(real_t tx, real_t ty)
        {
            _trans.tx = tx;
            _trans.ty = ty;
        }

        const Matrix& getTransform() const
        {
            return _trans;
        }

        MoviePart* findMoviePart(int Id);
        MoviePart* findMoviePart(const std::string& name);

    private:
        MoviePart(const Definition::Ptr& definition, MovieClipDataSource* dataSource);

    private:
        typedef clover::ptr_vector<MovieClip, clover::ptr_raw_policy<MovieClip>> vector_t;
        Definition::Ptr _definition;
        Definition::Ptr _originDefintion;
        MovieClipDataSource* _dataSource;
        vector_t _clips;
        Matrix _trans;
        int _stateIndex;
        bool _isHidden;
        bool _isChangeDefintion;
    };

    template <typename Fun, typename VT>
    static fla::MoviePart* s_findMoviePart(MovieClipDataSource* dataSource,
                                           const Definition::Ptr& definition,
                                           fla::MovieClip* rootClip,
                                           VT&& key,
                                           Fun&& fun)
    {
        auto partShareData = dataSource->getMoviePartShareDataForce(definition);
        auto part = partShareData->find(key);
        if (part)
        {
            return part;
        }

        std::vector<fla::MovieClip*> clips;
        rootClip->walk([&](fla::MovieClip* clip)
                       {
                           if (fun(clip, key))
                           {
                               clips.push_back(clip);
                               return false;
                           }
                           return true;
                       });

        if (clips.empty())
        {
            return nullptr;
        }

        auto partPtr = fla::MoviePart::create(clips[0]->getDefinition(), dataSource);
        part = partPtr.get();

        for (auto ptr : clips)
        {
            assert(ptr->getDefinition() == partPtr->getOriginDefinition());
            part->addClip(ptr);
        }

        partShareData->addPart(part);
        return part;
    }
}

#endif
