//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_SCALEMAP__
#define __FLA_SCALEMAP__

#include <map>
#include "../fla_Definition.h"
#include "../fla_DefinitionAnimation.h"
#include "../fla_DefinitionShape.h"

namespace fla
{
    class ScaleMap
    {
    public:
        // 导出的时候需要考虑缩放比例，比如角色原始尺寸是100 * 100,
        // 它放到场景上面，
        // 被缩放成50 * 50, 这样角色的缩放比例就为0.5,
        // 假如导出场景时候设置了缩放比例0.5, 角色的比例就应该为 0.5 * 0.5 =
        // 0.25.
        // 这样，可以让载入矢量数据的时候，生成的图片的质量最省最优
        void exportBestScale(const Definition::Ptr& rootDefine, float scale);

        void adjustImageScale(const Definition::Ptr& rootDefine);

        float getScale(int Id) const;

        void setScale(int Id, float scale);

        void unionMap(const ScaleMap& map);

        void clear();

        const std::map<int, float>& getScales() const;

        std::string toString() const;
        
    private:
        void exportSpriteFrameScales(const DefinitionAnimation::Ptr& sprite, float scale);
        void exportShapeImageScales(const DefinitionShape::Ptr& shape, float scale);

    private:
        std::map<int, float> _scales;
    };
}

#endif
