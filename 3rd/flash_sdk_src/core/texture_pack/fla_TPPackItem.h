//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_TPRECTDEFINE_H__
#define __FLA_TPRECTDEFINE_H__

#include "../definition/fla_Definition.h"
#include "../definition/fla_DefinitionUtils.h"
#include "rbp/rbp_PackItem.h"

namespace fla
{
    namespace tp
    {
        // 用户表示纹理合并的每一部分
        class PackItem : public rbp::PackItem
        {
        public:
            static Ptr create(const Definition::Ptr& ptr, float padding, float scale);
            PackItem(const Definition::Ptr& ptr, float padding, float scale);

            rbp::Rect getOutpuPackRect() const;

            template <typename Graphics>
            void renderInGraphics(Graphics& graphics) const;

            int getItemId() const;
            
            std::string computeItemCacheKey() const;

        private:
            Definition::Ptr _definition;
            float _scale;
            float _padding;
        };

        template <typename Graphics>
        void PackItem::renderInGraphics(Graphics& graphics) const
        {
            auto& packRect = getPackRect();
            auto& bounds = getBounds();

            graphics.translateCTM(packRect.x, packRect.y);
            if (isRotation())
            {
                graphics.translateCTM(packRect.width - _padding, 0);
                graphics.rotateCTM(libra_degree_to_radian(90.0));  // 旋转90度
            }
            graphics.scaleCTM(_scale, _scale);
            graphics.translateCTM(-bounds.x, -bounds.y);
            Definition_drawInGraphics(*_definition, graphics);
        }
    }
}

#endif
