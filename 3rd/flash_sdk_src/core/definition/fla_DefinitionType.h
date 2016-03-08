//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_DEFINITIONYPE_H__
#define __FLA_DEFINITIONYPE_H__

#include <stdint.h>

namespace fla
{
    enum class DefinitionType : uint8_t
    {
        Null        = 0, // 空定义
        Image       = 1, // 图片
        Shape       = 2, // 形状
        MorphShape  = 3, // 形变
        Animation   = 4, // 动画
        Scene       = 5, // 场景
        Role        = 6, // 角色，可以有多种状态
        Font        = 7, // 字体
        Text        = 8, // 文字

        // 考虑到绘画矢量图需要一定时间，特别是做游戏，大量的零碎图片会占更多资源
        // 在导出时候，提供一个选择，预先将形状或者形变导出成图片，
        // 这样做游戏就可以将所有图片合并，载入成同一个纹理，速度会更快
        // 此功能已被废弃
        ImageRef    = 9, // 此类型已被废弃，但保留编号
        Placeholder = 10, // 占位符
        Package     = 11, // 包，包含多个场景
    };

    template <typename T>
    struct DefinitionTraits
    {
        enum
        {
            type = (int)DefinitionType::Null
        };
    };

#define DefinitionStatement(ClassT, Type) \
    class ClassT;                         \
    template <>                           \
    struct DefinitionTraits<ClassT>       \
    {                                     \
        enum                              \
        { type = (int)Type };             \
    };

    DefinitionStatement(DefinitionShape,            DefinitionType::Shape);
    DefinitionStatement(DefinitionMorphShape,       DefinitionType::MorphShape);
    DefinitionStatement(DefinitionAnimation,        DefinitionType::Animation);
    DefinitionStatement(DefinitionScene,            DefinitionType::Scene);
    DefinitionStatement(DefinitionRole,             DefinitionType::Role);
    DefinitionStatement(DefinitionFont,             DefinitionType::Font);
    DefinitionStatement(DefinitionText,             DefinitionType::Text);
    DefinitionStatement(DefinitionImage,            DefinitionType::Image);
    DefinitionStatement(DefinitionPlaceholder,      DefinitionType::Placeholder);
    DefinitionStatement(DefinitionPackage,          DefinitionType::Package);

    class DefinitionVisitor
    {
    public:
        virtual void visit(const DefinitionShape&)       = 0;
        virtual void visit(const DefinitionAnimation&)   = 0;
        virtual void visit(const DefinitionScene&)       = 0;
        virtual void visit(const DefinitionRole&)        = 0;
        virtual void visit(const DefinitionFont&)        = 0;
        virtual void visit(const DefinitionText&)        = 0;
        virtual void visit(const DefinitionMorphShape&)  = 0;
        virtual void visit(const DefinitionImage&)       = 0;
        virtual void visit(const DefinitionPlaceholder&) = 0;
        virtual void visit(const DefinitionPackage&)     = 0;
    };
}

#endif
