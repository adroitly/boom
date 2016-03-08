//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_DEFINITIONPACKAGE_H__
#define __FLA_DEFINITIONPACKAGE_H__

#include "./fla_Definition.h"
#include "./fla_DefinitionScene.h"

namespace fla
{
    class DefinitionPackage : public DefinitionAnimation
    {
    public:
        enum TileType
        {
            XDir,
            YDir,
            Square,
        };

        typedef boost::intrusive_ptr<DefinitionPackage> Ptr;
        DefinitionPackage();

        static Ptr create();

        void setScenes(const std::vector<DefinitionScene::Ptr>& screns);

        const std::vector<DefinitionScene::Ptr>& getScenes() const;

        void setSpace(float space)
        {
            _space = space;
        }

        float getSpace() const
        {
            return _space;
        }

        TileType getTileType() const
        {
            return _tileType;
        }

        void setTileType(TileType type)
        {
            _tileType = type;
        }

        std::vector<Point> getScenePositions() const;
        void accept(DefinitionVisitor& visitor) const override
        {
            visitor.visit(*this);
        }
        
        virtual Rect getBounds() const override;

    private:
        std::vector<DefinitionScene::Ptr> _scenes;
        float _space;
        TileType _tileType;
    };
}

#endif
