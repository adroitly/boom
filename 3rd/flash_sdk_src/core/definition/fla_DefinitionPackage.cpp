//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_DefinitionPackage.h"

namespace fla
{
    DefinitionPackage::DefinitionPackage() : DefinitionAnimation(DefinitionType::Package)
    {
        _space = 4.0;
        _tileType = TileType::Square;
    }

    DefinitionPackage::Ptr DefinitionPackage::create()
    {
        return make_ptr<DefinitionPackage>();
    }

    Rect DefinitionPackage::getBounds() const
    {
        return DefinitionAnimation::getBounds();
    }

    void DefinitionPackage::setScenes(const std::vector<DefinitionScene::Ptr>& screns)
    {
        _scenes = screns;
        AnimationFrame spriteFrame;
        Point pt;
        int depth = 1;
        DefinitionMap<int> defintions;
        std::for_each(_scenes.begin(),
                      _scenes.end(),
                      [&](const DefinitionScene::Ptr& screen)
                      {
                          PlaceObject obj;
                          obj.setTrans(Matrix::makeTranslation(pt.x, pt.y));
                          obj.setDepth(depth);
                          obj.setCharacterID(screen->getId());
                          defintions.push_back(screen);
                          pt.y += screen->getSize().height + _space;
                          depth++;
                          spriteFrame.push_back(obj);
                      });
        this->setDefinitions(defintions);
        this->addSpriteFrame(spriteFrame);
    }

    const std::vector<DefinitionScene::Ptr>& DefinitionPackage::getScenes() const
    {
        return _scenes;
    }

    std::vector<Point> DefinitionPackage::getScenePositions() const
    {
        std::vector<Point> pts;
        Point pt;
        std::for_each(_scenes.rbegin(),
                      _scenes.rend(),
                      [&](const DefinitionScene::Ptr& screen)
                      {
                          pts.push_back(pt);
                          pt.y += screen->getSize().height + _space;
                      });

        return pts;
    }
}