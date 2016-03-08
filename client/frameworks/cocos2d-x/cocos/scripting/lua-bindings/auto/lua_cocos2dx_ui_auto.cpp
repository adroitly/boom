#include "lua_cocos2dx_ui_auto.hpp"
#include "CocosGUI.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_ui_Widget_setLayoutComponentEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setLayoutComponentEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Widget:setLayoutComponentEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setLayoutComponentEnabled'", nullptr);
            return 0;
        }
        cobj->setLayoutComponentEnabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setLayoutComponentEnabled",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setLayoutComponentEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setSizePercent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setSizePercent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.Widget:setSizePercent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setSizePercent'", nullptr);
            return 0;
        }
        cobj->setSizePercent(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setSizePercent",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setSizePercent'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getCustomSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getCustomSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getCustomSize'", nullptr);
            return 0;
        }
        const cocos2d::Size& ret = cobj->getCustomSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getCustomSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getCustomSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getLeftBoundary(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getLeftBoundary'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getLeftBoundary'", nullptr);
            return 0;
        }
        double ret = cobj->getLeftBoundary();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getLeftBoundary",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getLeftBoundary'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setFlippedX(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setFlippedX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Widget:setFlippedX");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setFlippedX'", nullptr);
            return 0;
        }
        cobj->setFlippedX(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setFlippedX",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setFlippedX'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setCallbackName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setCallbackName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccui.Widget:setCallbackName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setCallbackName'", nullptr);
            return 0;
        }
        cobj->setCallbackName(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setCallbackName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setCallbackName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getVirtualRenderer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getVirtualRenderer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getVirtualRenderer'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->getVirtualRenderer();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getVirtualRenderer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getVirtualRenderer'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setPropagateTouchEvents(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setPropagateTouchEvents'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Widget:setPropagateTouchEvents");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setPropagateTouchEvents'", nullptr);
            return 0;
        }
        cobj->setPropagateTouchEvents(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setPropagateTouchEvents",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setPropagateTouchEvents'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_isUnifySizeEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_isUnifySizeEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_isUnifySizeEnabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isUnifySizeEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isUnifySizeEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_isUnifySizeEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getSizePercent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getSizePercent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getSizePercent'", nullptr);
            return 0;
        }
        const cocos2d::Vec2& ret = cobj->getSizePercent();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getSizePercent",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getSizePercent'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setPositionPercent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setPositionPercent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.Widget:setPositionPercent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setPositionPercent'", nullptr);
            return 0;
        }
        cobj->setPositionPercent(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setPositionPercent",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setPositionPercent'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setSwallowTouches(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setSwallowTouches'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Widget:setSwallowTouches");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setSwallowTouches'", nullptr);
            return 0;
        }
        cobj->setSwallowTouches(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setSwallowTouches",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setSwallowTouches'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getLayoutSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getLayoutSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getLayoutSize'", nullptr);
            return 0;
        }
        const cocos2d::Size& ret = cobj->getLayoutSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getLayoutSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getLayoutSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setHighlighted(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setHighlighted'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Widget:setHighlighted");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setHighlighted'", nullptr);
            return 0;
        }
        cobj->setHighlighted(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setHighlighted",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setHighlighted'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setPositionType(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setPositionType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ui::Widget::PositionType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.Widget:setPositionType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setPositionType'", nullptr);
            return 0;
        }
        cobj->setPositionType(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setPositionType",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setPositionType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_isIgnoreContentAdaptWithSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_isIgnoreContentAdaptWithSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_isIgnoreContentAdaptWithSize'", nullptr);
            return 0;
        }
        bool ret = cobj->isIgnoreContentAdaptWithSize();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isIgnoreContentAdaptWithSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_isIgnoreContentAdaptWithSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getVirtualRendererSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getVirtualRendererSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getVirtualRendererSize'", nullptr);
            return 0;
        }
        cocos2d::Size ret = cobj->getVirtualRendererSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getVirtualRendererSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getVirtualRendererSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_isHighlighted(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_isHighlighted'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_isHighlighted'", nullptr);
            return 0;
        }
        bool ret = cobj->isHighlighted();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isHighlighted",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_isHighlighted'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getLayoutParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getLayoutParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getLayoutParameter'", nullptr);
            return 0;
        }
        cocos2d::ui::LayoutParameter* ret = cobj->getLayoutParameter();
        object_to_luaval<cocos2d::ui::LayoutParameter>(tolua_S, "ccui.LayoutParameter",(cocos2d::ui::LayoutParameter*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getLayoutParameter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getLayoutParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getPositionType(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getPositionType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getPositionType'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getPositionType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getPositionType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getPositionType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getTopBoundary(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getTopBoundary'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getTopBoundary'", nullptr);
            return 0;
        }
        double ret = cobj->getTopBoundary();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getTopBoundary",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getTopBoundary'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_ignoreContentAdaptWithSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_ignoreContentAdaptWithSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Widget:ignoreContentAdaptWithSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_ignoreContentAdaptWithSize'", nullptr);
            return 0;
        }
        cobj->ignoreContentAdaptWithSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:ignoreContentAdaptWithSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_ignoreContentAdaptWithSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_findNextFocusedWidget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_findNextFocusedWidget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::ui::Widget::FocusDirection arg0;
        cocos2d::ui::Widget* arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.Widget:findNextFocusedWidget");

        ok &= luaval_to_object<cocos2d::ui::Widget>(tolua_S, 3, "ccui.Widget",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_findNextFocusedWidget'", nullptr);
            return 0;
        }
        cocos2d::ui::Widget* ret = cobj->findNextFocusedWidget(arg0, arg1);
        object_to_luaval<cocos2d::ui::Widget>(tolua_S, "ccui.Widget",(cocos2d::ui::Widget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:findNextFocusedWidget",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_findNextFocusedWidget'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_isEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_isEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_isEnabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_isEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_isFocused(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_isFocused'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_isFocused'", nullptr);
            return 0;
        }
        bool ret = cobj->isFocused();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isFocused",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_isFocused'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getTouchBeganPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getTouchBeganPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getTouchBeganPosition'", nullptr);
            return 0;
        }
        const cocos2d::Vec2& ret = cobj->getTouchBeganPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getTouchBeganPosition",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getTouchBeganPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_isTouchEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_isTouchEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_isTouchEnabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isTouchEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isTouchEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_isTouchEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getCallbackName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getCallbackName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getCallbackName'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getCallbackName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getCallbackName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getCallbackName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getActionTag(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getActionTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getActionTag'", nullptr);
            return 0;
        }
        int ret = cobj->getActionTag();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getActionTag",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getActionTag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getWorldPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getWorldPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getWorldPosition'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getWorldPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getWorldPosition",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getWorldPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_isFocusEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_isFocusEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_isFocusEnabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isFocusEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isFocusEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_isFocusEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setFocused(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setFocused'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Widget:setFocused");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setFocused'", nullptr);
            return 0;
        }
        cobj->setFocused(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setFocused",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setFocused'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setActionTag(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setActionTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.Widget:setActionTag");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setActionTag'", nullptr);
            return 0;
        }
        cobj->setActionTag(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setActionTag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setActionTag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setTouchEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setTouchEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Widget:setTouchEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setTouchEnabled'", nullptr);
            return 0;
        }
        cobj->setTouchEnabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setTouchEnabled",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setTouchEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setFlippedY(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setFlippedY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Widget:setFlippedY");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setFlippedY'", nullptr);
            return 0;
        }
        cobj->setFlippedY(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setFlippedY",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setFlippedY'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Widget:setEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setEnabled'", nullptr);
            return 0;
        }
        cobj->setEnabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setEnabled",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getRightBoundary(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getRightBoundary'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getRightBoundary'", nullptr);
            return 0;
        }
        double ret = cobj->getRightBoundary();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getRightBoundary",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getRightBoundary'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setBrightStyle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setBrightStyle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ui::Widget::BrightStyle arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.Widget:setBrightStyle");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setBrightStyle'", nullptr);
            return 0;
        }
        cobj->setBrightStyle(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setBrightStyle",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setBrightStyle'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setLayoutParameter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setLayoutParameter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ui::LayoutParameter* arg0;

        ok &= luaval_to_object<cocos2d::ui::LayoutParameter>(tolua_S, 2, "ccui.LayoutParameter",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setLayoutParameter'", nullptr);
            return 0;
        }
        cobj->setLayoutParameter(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setLayoutParameter",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setLayoutParameter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_clone(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_clone'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_clone'", nullptr);
            return 0;
        }
        cocos2d::ui::Widget* ret = cobj->clone();
        object_to_luaval<cocos2d::ui::Widget>(tolua_S, "ccui.Widget",(cocos2d::ui::Widget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:clone",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_clone'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setFocusEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setFocusEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Widget:setFocusEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setFocusEnabled'", nullptr);
            return 0;
        }
        cobj->setFocusEnabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setFocusEnabled",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setFocusEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getBottomBoundary(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getBottomBoundary'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getBottomBoundary'", nullptr);
            return 0;
        }
        double ret = cobj->getBottomBoundary();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getBottomBoundary",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getBottomBoundary'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_isBright(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_isBright'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_isBright'", nullptr);
            return 0;
        }
        bool ret = cobj->isBright();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isBright",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_isBright'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setUnifySizeEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setUnifySizeEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Widget:setUnifySizeEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setUnifySizeEnabled'", nullptr);
            return 0;
        }
        cobj->setUnifySizeEnabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setUnifySizeEnabled",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setUnifySizeEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_isPropagateTouchEvents(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_isPropagateTouchEvents'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_isPropagateTouchEvents'", nullptr);
            return 0;
        }
        bool ret = cobj->isPropagateTouchEvents();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isPropagateTouchEvents",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_isPropagateTouchEvents'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getCurrentFocusedWidget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getCurrentFocusedWidget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getCurrentFocusedWidget'", nullptr);
            return 0;
        }
        cocos2d::ui::Widget* ret = cobj->getCurrentFocusedWidget();
        object_to_luaval<cocos2d::ui::Widget>(tolua_S, "ccui.Widget",(cocos2d::ui::Widget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getCurrentFocusedWidget",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getCurrentFocusedWidget'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_hitTest(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_hitTest'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.Widget:hitTest");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_hitTest'", nullptr);
            return 0;
        }
        bool ret = cobj->hitTest(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:hitTest",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_hitTest'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_isLayoutComponentEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_isLayoutComponentEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_isLayoutComponentEnabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isLayoutComponentEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isLayoutComponentEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_isLayoutComponentEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_requestFocus(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_requestFocus'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_requestFocus'", nullptr);
            return 0;
        }
        cobj->requestFocus();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:requestFocus",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_requestFocus'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_updateSizeAndPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_updateSizeAndPosition'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.Widget:updateSizeAndPosition");

            if (!ok) { break; }
            cobj->updateSizeAndPosition(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cobj->updateSizeAndPosition();
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.Widget:updateSizeAndPosition",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_updateSizeAndPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getTouchMovePosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getTouchMovePosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getTouchMovePosition'", nullptr);
            return 0;
        }
        const cocos2d::Vec2& ret = cobj->getTouchMovePosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getTouchMovePosition",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getTouchMovePosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getSizeType(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getSizeType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getSizeType'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getSizeType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getSizeType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getSizeType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getCallbackType(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getCallbackType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getCallbackType'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getCallbackType();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getCallbackType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getCallbackType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getTouchEndPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getTouchEndPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getTouchEndPosition'", nullptr);
            return 0;
        }
        const cocos2d::Vec2& ret = cobj->getTouchEndPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getTouchEndPosition",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getTouchEndPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_getPositionPercent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_getPositionPercent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_getPositionPercent'", nullptr);
            return 0;
        }
        const cocos2d::Vec2& ret = cobj->getPositionPercent();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:getPositionPercent",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_getPositionPercent'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_isFlippedX(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_isFlippedX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_isFlippedX'", nullptr);
            return 0;
        }
        bool ret = cobj->isFlippedX();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isFlippedX",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_isFlippedX'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_isFlippedY(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_isFlippedY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_isFlippedY'", nullptr);
            return 0;
        }
        bool ret = cobj->isFlippedY();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isFlippedY",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_isFlippedY'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_isClippingParentContainsPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_isClippingParentContainsPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccui.Widget:isClippingParentContainsPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_isClippingParentContainsPoint'", nullptr);
            return 0;
        }
        bool ret = cobj->isClippingParentContainsPoint(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isClippingParentContainsPoint",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_isClippingParentContainsPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setSizeType(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setSizeType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ui::Widget::SizeType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.Widget:setSizeType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setSizeType'", nullptr);
            return 0;
        }
        cobj->setSizeType(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setSizeType",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setSizeType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setBright(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setBright'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Widget:setBright");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setBright'", nullptr);
            return 0;
        }
        cobj->setBright(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setBright",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setBright'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_setCallbackType(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_setCallbackType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccui.Widget:setCallbackType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_setCallbackType'", nullptr);
            return 0;
        }
        cobj->setCallbackType(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:setCallbackType",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_setCallbackType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_isSwallowTouches(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Widget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Widget_isSwallowTouches'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_isSwallowTouches'", nullptr);
            return 0;
        }
        bool ret = cobj->isSwallowTouches();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:isSwallowTouches",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_isSwallowTouches'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Widget_enableDpadNavigation(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        bool arg0;
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Widget:enableDpadNavigation");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_enableDpadNavigation'", nullptr);
            return 0;
        }
        cocos2d::ui::Widget::enableDpadNavigation(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Widget:enableDpadNavigation",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_enableDpadNavigation'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_ui_Widget_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_create'", nullptr);
            return 0;
        }
        cocos2d::ui::Widget* ret = cocos2d::ui::Widget::create();
        object_to_luaval<cocos2d::ui::Widget>(tolua_S, "ccui.Widget",(cocos2d::ui::Widget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.Widget:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_ui_Widget_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Widget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Widget_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::Widget();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.Widget");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Widget:Widget",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Widget_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_ui_Widget_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Widget)");
    return 0;
}

int lua_register_cocos2dx_ui_Widget(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccui.Widget");
    tolua_cclass(tolua_S,"Widget","ccui.Widget","cc.ProtectedNode",nullptr);

    tolua_beginmodule(tolua_S,"Widget");
        tolua_function(tolua_S,"new",lua_cocos2dx_ui_Widget_constructor);
        tolua_function(tolua_S,"setLayoutComponentEnabled",lua_cocos2dx_ui_Widget_setLayoutComponentEnabled);
        tolua_function(tolua_S,"setSizePercent",lua_cocos2dx_ui_Widget_setSizePercent);
        tolua_function(tolua_S,"getCustomSize",lua_cocos2dx_ui_Widget_getCustomSize);
        tolua_function(tolua_S,"getLeftBoundary",lua_cocos2dx_ui_Widget_getLeftBoundary);
        tolua_function(tolua_S,"setFlippedX",lua_cocos2dx_ui_Widget_setFlippedX);
        tolua_function(tolua_S,"setCallbackName",lua_cocos2dx_ui_Widget_setCallbackName);
        tolua_function(tolua_S,"getVirtualRenderer",lua_cocos2dx_ui_Widget_getVirtualRenderer);
        tolua_function(tolua_S,"setPropagateTouchEvents",lua_cocos2dx_ui_Widget_setPropagateTouchEvents);
        tolua_function(tolua_S,"isUnifySizeEnabled",lua_cocos2dx_ui_Widget_isUnifySizeEnabled);
        tolua_function(tolua_S,"getSizePercent",lua_cocos2dx_ui_Widget_getSizePercent);
        tolua_function(tolua_S,"setPositionPercent",lua_cocos2dx_ui_Widget_setPositionPercent);
        tolua_function(tolua_S,"setSwallowTouches",lua_cocos2dx_ui_Widget_setSwallowTouches);
        tolua_function(tolua_S,"getLayoutSize",lua_cocos2dx_ui_Widget_getLayoutSize);
        tolua_function(tolua_S,"setHighlighted",lua_cocos2dx_ui_Widget_setHighlighted);
        tolua_function(tolua_S,"setPositionType",lua_cocos2dx_ui_Widget_setPositionType);
        tolua_function(tolua_S,"isIgnoreContentAdaptWithSize",lua_cocos2dx_ui_Widget_isIgnoreContentAdaptWithSize);
        tolua_function(tolua_S,"getVirtualRendererSize",lua_cocos2dx_ui_Widget_getVirtualRendererSize);
        tolua_function(tolua_S,"isHighlighted",lua_cocos2dx_ui_Widget_isHighlighted);
        tolua_function(tolua_S,"getLayoutParameter",lua_cocos2dx_ui_Widget_getLayoutParameter);
        tolua_function(tolua_S,"getPositionType",lua_cocos2dx_ui_Widget_getPositionType);
        tolua_function(tolua_S,"getTopBoundary",lua_cocos2dx_ui_Widget_getTopBoundary);
        tolua_function(tolua_S,"ignoreContentAdaptWithSize",lua_cocos2dx_ui_Widget_ignoreContentAdaptWithSize);
        tolua_function(tolua_S,"findNextFocusedWidget",lua_cocos2dx_ui_Widget_findNextFocusedWidget);
        tolua_function(tolua_S,"isEnabled",lua_cocos2dx_ui_Widget_isEnabled);
        tolua_function(tolua_S,"isFocused",lua_cocos2dx_ui_Widget_isFocused);
        tolua_function(tolua_S,"getTouchBeganPosition",lua_cocos2dx_ui_Widget_getTouchBeganPosition);
        tolua_function(tolua_S,"isTouchEnabled",lua_cocos2dx_ui_Widget_isTouchEnabled);
        tolua_function(tolua_S,"getCallbackName",lua_cocos2dx_ui_Widget_getCallbackName);
        tolua_function(tolua_S,"getActionTag",lua_cocos2dx_ui_Widget_getActionTag);
        tolua_function(tolua_S,"getWorldPosition",lua_cocos2dx_ui_Widget_getWorldPosition);
        tolua_function(tolua_S,"isFocusEnabled",lua_cocos2dx_ui_Widget_isFocusEnabled);
        tolua_function(tolua_S,"setFocused",lua_cocos2dx_ui_Widget_setFocused);
        tolua_function(tolua_S,"setActionTag",lua_cocos2dx_ui_Widget_setActionTag);
        tolua_function(tolua_S,"setTouchEnabled",lua_cocos2dx_ui_Widget_setTouchEnabled);
        tolua_function(tolua_S,"setFlippedY",lua_cocos2dx_ui_Widget_setFlippedY);
        tolua_function(tolua_S,"setEnabled",lua_cocos2dx_ui_Widget_setEnabled);
        tolua_function(tolua_S,"getRightBoundary",lua_cocos2dx_ui_Widget_getRightBoundary);
        tolua_function(tolua_S,"setBrightStyle",lua_cocos2dx_ui_Widget_setBrightStyle);
        tolua_function(tolua_S,"setLayoutParameter",lua_cocos2dx_ui_Widget_setLayoutParameter);
        tolua_function(tolua_S,"clone",lua_cocos2dx_ui_Widget_clone);
        tolua_function(tolua_S,"setFocusEnabled",lua_cocos2dx_ui_Widget_setFocusEnabled);
        tolua_function(tolua_S,"getBottomBoundary",lua_cocos2dx_ui_Widget_getBottomBoundary);
        tolua_function(tolua_S,"isBright",lua_cocos2dx_ui_Widget_isBright);
        tolua_function(tolua_S,"setUnifySizeEnabled",lua_cocos2dx_ui_Widget_setUnifySizeEnabled);
        tolua_function(tolua_S,"isPropagateTouchEvents",lua_cocos2dx_ui_Widget_isPropagateTouchEvents);
        tolua_function(tolua_S,"getCurrentFocusedWidget",lua_cocos2dx_ui_Widget_getCurrentFocusedWidget);
        tolua_function(tolua_S,"hitTest",lua_cocos2dx_ui_Widget_hitTest);
        tolua_function(tolua_S,"isLayoutComponentEnabled",lua_cocos2dx_ui_Widget_isLayoutComponentEnabled);
        tolua_function(tolua_S,"requestFocus",lua_cocos2dx_ui_Widget_requestFocus);
        tolua_function(tolua_S,"updateSizeAndPosition",lua_cocos2dx_ui_Widget_updateSizeAndPosition);
        tolua_function(tolua_S,"getTouchMovePosition",lua_cocos2dx_ui_Widget_getTouchMovePosition);
        tolua_function(tolua_S,"getSizeType",lua_cocos2dx_ui_Widget_getSizeType);
        tolua_function(tolua_S,"getCallbackType",lua_cocos2dx_ui_Widget_getCallbackType);
        tolua_function(tolua_S,"getTouchEndPosition",lua_cocos2dx_ui_Widget_getTouchEndPosition);
        tolua_function(tolua_S,"getPositionPercent",lua_cocos2dx_ui_Widget_getPositionPercent);
        tolua_function(tolua_S,"isFlippedX",lua_cocos2dx_ui_Widget_isFlippedX);
        tolua_function(tolua_S,"isFlippedY",lua_cocos2dx_ui_Widget_isFlippedY);
        tolua_function(tolua_S,"isClippingParentContainsPoint",lua_cocos2dx_ui_Widget_isClippingParentContainsPoint);
        tolua_function(tolua_S,"setSizeType",lua_cocos2dx_ui_Widget_setSizeType);
        tolua_function(tolua_S,"setBright",lua_cocos2dx_ui_Widget_setBright);
        tolua_function(tolua_S,"setCallbackType",lua_cocos2dx_ui_Widget_setCallbackType);
        tolua_function(tolua_S,"isSwallowTouches",lua_cocos2dx_ui_Widget_isSwallowTouches);
        tolua_function(tolua_S,"enableDpadNavigation", lua_cocos2dx_ui_Widget_enableDpadNavigation);
        tolua_function(tolua_S,"create", lua_cocos2dx_ui_Widget_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::ui::Widget).name();
    g_luaType[typeName] = "ccui.Widget";
    g_typeCast["Widget"] = "ccui.Widget";
    return 1;
}

int lua_cocos2dx_ui_TextField_setAttachWithIME(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setAttachWithIME'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.TextField:setAttachWithIME");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setAttachWithIME'", nullptr);
            return 0;
        }
        cobj->setAttachWithIME(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setAttachWithIME",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setAttachWithIME'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_getFontSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_getFontSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_getFontSize'", nullptr);
            return 0;
        }
        int ret = cobj->getFontSize();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getFontSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_getFontSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_getString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_getString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_getString'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getString();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getString",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_getString'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setPasswordStyleText(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setPasswordStyleText'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccui.TextField:setPasswordStyleText"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setPasswordStyleText'", nullptr);
            return 0;
        }
        cobj->setPasswordStyleText(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setPasswordStyleText",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setPasswordStyleText'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_getDeleteBackward(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_getDeleteBackward'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_getDeleteBackward'", nullptr);
            return 0;
        }
        bool ret = cobj->getDeleteBackward();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getDeleteBackward",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_getDeleteBackward'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_getPlaceHolder(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_getPlaceHolder'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_getPlaceHolder'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getPlaceHolder();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getPlaceHolder",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_getPlaceHolder'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_getAttachWithIME(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_getAttachWithIME'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_getAttachWithIME'", nullptr);
            return 0;
        }
        bool ret = cobj->getAttachWithIME();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getAttachWithIME",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_getAttachWithIME'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setFontName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setFontName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccui.TextField:setFontName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setFontName'", nullptr);
            return 0;
        }
        cobj->setFontName(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setFontName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setFontName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_getInsertText(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_getInsertText'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_getInsertText'", nullptr);
            return 0;
        }
        bool ret = cobj->getInsertText();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getInsertText",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_getInsertText'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setInsertText(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setInsertText'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.TextField:setInsertText");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setInsertText'", nullptr);
            return 0;
        }
        cobj->setInsertText(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setInsertText",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setInsertText'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccui.TextField:setString");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setString'", nullptr);
            return 0;
        }
        cobj->setString(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setString",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setString'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_getDetachWithIME(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_getDetachWithIME'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_getDetachWithIME'", nullptr);
            return 0;
        }
        bool ret = cobj->getDetachWithIME();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getDetachWithIME",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_getDetachWithIME'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setTextVerticalAlignment(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setTextVerticalAlignment'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::TextVAlignment arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.TextField:setTextVerticalAlignment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setTextVerticalAlignment'", nullptr);
            return 0;
        }
        cobj->setTextVerticalAlignment(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setTextVerticalAlignment",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setTextVerticalAlignment'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_addEventListener(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_addEventListener'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void (cocos2d::Ref *, cocos2d::ui::TextField::EventType)> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_addEventListener'", nullptr);
            return 0;
        }
        cobj->addEventListener(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:addEventListener",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_addEventListener'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_didNotSelectSelf(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_didNotSelectSelf'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_didNotSelectSelf'", nullptr);
            return 0;
        }
        cobj->didNotSelectSelf();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:didNotSelectSelf",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_didNotSelectSelf'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_getFontName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_getFontName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_getFontName'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getFontName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getFontName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_getFontName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setTextAreaSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setTextAreaSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Size arg0;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.TextField:setTextAreaSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setTextAreaSize'", nullptr);
            return 0;
        }
        cobj->setTextAreaSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setTextAreaSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setTextAreaSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_attachWithIME(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_attachWithIME'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_attachWithIME'", nullptr);
            return 0;
        }
        cobj->attachWithIME();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:attachWithIME",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_attachWithIME'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_getStringLength(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_getStringLength'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_getStringLength'", nullptr);
            return 0;
        }
        int ret = cobj->getStringLength();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getStringLength",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_getStringLength'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_getAutoRenderSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_getAutoRenderSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_getAutoRenderSize'", nullptr);
            return 0;
        }
        cocos2d::Size ret = cobj->getAutoRenderSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getAutoRenderSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_getAutoRenderSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setPasswordEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setPasswordEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.TextField:setPasswordEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setPasswordEnabled'", nullptr);
            return 0;
        }
        cobj->setPasswordEnabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setPasswordEnabled",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setPasswordEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_getPlaceHolderColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_getPlaceHolderColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_getPlaceHolderColor'", nullptr);
            return 0;
        }
        const cocos2d::Color4B& ret = cobj->getPlaceHolderColor();
        color4b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getPlaceHolderColor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_getPlaceHolderColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_getPasswordStyleText(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_getPasswordStyleText'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_getPasswordStyleText'", nullptr);
            return 0;
        }
        const char* ret = cobj->getPasswordStyleText();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getPasswordStyleText",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_getPasswordStyleText'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setMaxLengthEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setMaxLengthEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.TextField:setMaxLengthEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setMaxLengthEnabled'", nullptr);
            return 0;
        }
        cobj->setMaxLengthEnabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setMaxLengthEnabled",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setMaxLengthEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_isPasswordEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_isPasswordEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_isPasswordEnabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isPasswordEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:isPasswordEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_isPasswordEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setDeleteBackward(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setDeleteBackward'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.TextField:setDeleteBackward");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setDeleteBackward'", nullptr);
            return 0;
        }
        cobj->setDeleteBackward(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setDeleteBackward",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setDeleteBackward'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setFontSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setFontSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.TextField:setFontSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setFontSize'", nullptr);
            return 0;
        }
        cobj->setFontSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setFontSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setFontSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setPlaceHolder(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setPlaceHolder'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccui.TextField:setPlaceHolder");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setPlaceHolder'", nullptr);
            return 0;
        }
        cobj->setPlaceHolder(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setPlaceHolder",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setPlaceHolder'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setPlaceHolderColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setPlaceHolderColor'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.TextField:setPlaceHolderColor");

            if (!ok) { break; }
            cobj->setPlaceHolderColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Color3B arg0;
            ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccui.TextField:setPlaceHolderColor");

            if (!ok) { break; }
            cobj->setPlaceHolderColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.TextField:setPlaceHolderColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setPlaceHolderColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setTextHorizontalAlignment(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setTextHorizontalAlignment'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::TextHAlignment arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.TextField:setTextHorizontalAlignment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setTextHorizontalAlignment'", nullptr);
            return 0;
        }
        cobj->setTextHorizontalAlignment(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setTextHorizontalAlignment",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setTextHorizontalAlignment'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setTextColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setTextColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4B arg0;

        ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.TextField:setTextColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setTextColor'", nullptr);
            return 0;
        }
        cobj->setTextColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setTextColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setTextColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_getMaxLength(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_getMaxLength'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_getMaxLength'", nullptr);
            return 0;
        }
        int ret = cobj->getMaxLength();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getMaxLength",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_getMaxLength'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_isMaxLengthEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_isMaxLengthEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_isMaxLengthEnabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isMaxLengthEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:isMaxLengthEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_isMaxLengthEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setDetachWithIME(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setDetachWithIME'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.TextField:setDetachWithIME");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setDetachWithIME'", nullptr);
            return 0;
        }
        cobj->setDetachWithIME(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setDetachWithIME",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setDetachWithIME'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setTouchAreaEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setTouchAreaEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.TextField:setTouchAreaEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setTouchAreaEnabled'", nullptr);
            return 0;
        }
        cobj->setTouchAreaEnabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setTouchAreaEnabled",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setTouchAreaEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setMaxLength(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setMaxLength'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.TextField:setMaxLength");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setMaxLength'", nullptr);
            return 0;
        }
        cobj->setMaxLength(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setMaxLength",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setMaxLength'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_setTouchSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_setTouchSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Size arg0;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.TextField:setTouchSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_setTouchSize'", nullptr);
            return 0;
        }
        cobj->setTouchSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:setTouchSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_setTouchSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_getTouchSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::TextField*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_TextField_getTouchSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_getTouchSize'", nullptr);
            return 0;
        }
        cocos2d::Size ret = cobj->getTouchSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:getTouchSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_getTouchSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_TextField_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 3)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccui.TextField:create");
            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccui.TextField:create");
            if (!ok) { break; }
            int arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccui.TextField:create");
            if (!ok) { break; }
            cocos2d::ui::TextField* ret = cocos2d::ui::TextField::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::ui::TextField>(tolua_S, "ccui.TextField",(cocos2d::ui::TextField*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::ui::TextField* ret = cocos2d::ui::TextField::create();
            object_to_luaval<cocos2d::ui::TextField>(tolua_S, "ccui.TextField",(cocos2d::ui::TextField*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccui.TextField:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_ui_TextField_createInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_createInstance'", nullptr);
            return 0;
        }
        cocos2d::Ref* ret = cocos2d::ui::TextField::createInstance();
        object_to_luaval<cocos2d::Ref>(tolua_S, "cc.Ref",(cocos2d::Ref*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.TextField:createInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_createInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_ui_TextField_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::TextField* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_TextField_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::TextField();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.TextField");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.TextField:TextField",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_TextField_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_ui_TextField_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (TextField)");
    return 0;
}

int lua_register_cocos2dx_ui_TextField(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccui.TextField");
    tolua_cclass(tolua_S,"TextField","ccui.TextField","ccui.Widget",nullptr);

    tolua_beginmodule(tolua_S,"TextField");
        tolua_function(tolua_S,"new",lua_cocos2dx_ui_TextField_constructor);
        tolua_function(tolua_S,"setAttachWithIME",lua_cocos2dx_ui_TextField_setAttachWithIME);
        tolua_function(tolua_S,"getFontSize",lua_cocos2dx_ui_TextField_getFontSize);
        tolua_function(tolua_S,"getString",lua_cocos2dx_ui_TextField_getString);
        tolua_function(tolua_S,"setPasswordStyleText",lua_cocos2dx_ui_TextField_setPasswordStyleText);
        tolua_function(tolua_S,"getDeleteBackward",lua_cocos2dx_ui_TextField_getDeleteBackward);
        tolua_function(tolua_S,"getPlaceHolder",lua_cocos2dx_ui_TextField_getPlaceHolder);
        tolua_function(tolua_S,"getAttachWithIME",lua_cocos2dx_ui_TextField_getAttachWithIME);
        tolua_function(tolua_S,"setFontName",lua_cocos2dx_ui_TextField_setFontName);
        tolua_function(tolua_S,"getInsertText",lua_cocos2dx_ui_TextField_getInsertText);
        tolua_function(tolua_S,"setInsertText",lua_cocos2dx_ui_TextField_setInsertText);
        tolua_function(tolua_S,"setString",lua_cocos2dx_ui_TextField_setString);
        tolua_function(tolua_S,"getDetachWithIME",lua_cocos2dx_ui_TextField_getDetachWithIME);
        tolua_function(tolua_S,"setTextVerticalAlignment",lua_cocos2dx_ui_TextField_setTextVerticalAlignment);
        tolua_function(tolua_S,"addEventListener",lua_cocos2dx_ui_TextField_addEventListener);
        tolua_function(tolua_S,"didNotSelectSelf",lua_cocos2dx_ui_TextField_didNotSelectSelf);
        tolua_function(tolua_S,"getFontName",lua_cocos2dx_ui_TextField_getFontName);
        tolua_function(tolua_S,"setTextAreaSize",lua_cocos2dx_ui_TextField_setTextAreaSize);
        tolua_function(tolua_S,"attachWithIME",lua_cocos2dx_ui_TextField_attachWithIME);
        tolua_function(tolua_S,"getStringLength",lua_cocos2dx_ui_TextField_getStringLength);
        tolua_function(tolua_S,"getAutoRenderSize",lua_cocos2dx_ui_TextField_getAutoRenderSize);
        tolua_function(tolua_S,"setPasswordEnabled",lua_cocos2dx_ui_TextField_setPasswordEnabled);
        tolua_function(tolua_S,"getPlaceHolderColor",lua_cocos2dx_ui_TextField_getPlaceHolderColor);
        tolua_function(tolua_S,"getPasswordStyleText",lua_cocos2dx_ui_TextField_getPasswordStyleText);
        tolua_function(tolua_S,"setMaxLengthEnabled",lua_cocos2dx_ui_TextField_setMaxLengthEnabled);
        tolua_function(tolua_S,"isPasswordEnabled",lua_cocos2dx_ui_TextField_isPasswordEnabled);
        tolua_function(tolua_S,"setDeleteBackward",lua_cocos2dx_ui_TextField_setDeleteBackward);
        tolua_function(tolua_S,"setFontSize",lua_cocos2dx_ui_TextField_setFontSize);
        tolua_function(tolua_S,"setPlaceHolder",lua_cocos2dx_ui_TextField_setPlaceHolder);
        tolua_function(tolua_S,"setPlaceHolderColor",lua_cocos2dx_ui_TextField_setPlaceHolderColor);
        tolua_function(tolua_S,"setTextHorizontalAlignment",lua_cocos2dx_ui_TextField_setTextHorizontalAlignment);
        tolua_function(tolua_S,"setTextColor",lua_cocos2dx_ui_TextField_setTextColor);
        tolua_function(tolua_S,"getMaxLength",lua_cocos2dx_ui_TextField_getMaxLength);
        tolua_function(tolua_S,"isMaxLengthEnabled",lua_cocos2dx_ui_TextField_isMaxLengthEnabled);
        tolua_function(tolua_S,"setDetachWithIME",lua_cocos2dx_ui_TextField_setDetachWithIME);
        tolua_function(tolua_S,"setTouchAreaEnabled",lua_cocos2dx_ui_TextField_setTouchAreaEnabled);
        tolua_function(tolua_S,"setMaxLength",lua_cocos2dx_ui_TextField_setMaxLength);
        tolua_function(tolua_S,"setTouchSize",lua_cocos2dx_ui_TextField_setTouchSize);
        tolua_function(tolua_S,"getTouchSize",lua_cocos2dx_ui_TextField_getTouchSize);
        tolua_function(tolua_S,"create", lua_cocos2dx_ui_TextField_create);
        tolua_function(tolua_S,"createInstance", lua_cocos2dx_ui_TextField_createInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::ui::TextField).name();
    g_luaType[typeName] = "ccui.TextField";
    g_typeCast["TextField"] = "ccui.TextField";
    return 1;
}

int lua_cocos2dx_ui_RichElement_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElement* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichElement",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichElement*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_RichElement_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElement:init");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElement:init");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElement:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichElement_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElement:init",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichElement_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_RichElement_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElement* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichElement_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::RichElement();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.RichElement");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElement:RichElement",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichElement_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_ui_RichElement_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RichElement)");
    return 0;
}

int lua_register_cocos2dx_ui_RichElement(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccui.RichElement");
    tolua_cclass(tolua_S,"RichElement","ccui.RichElement","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"RichElement");
        tolua_function(tolua_S,"new",lua_cocos2dx_ui_RichElement_constructor);
        tolua_function(tolua_S,"init",lua_cocos2dx_ui_RichElement_init);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::ui::RichElement).name();
    g_luaType[typeName] = "ccui.RichElement";
    g_typeCast["RichElement"] = "ccui.RichElement";
    return 1;
}

int lua_cocos2dx_ui_RichElementText_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElementText* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichElementText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichElementText*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_RichElementText_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 6) 
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string arg3;
        std::string arg4;
        double arg5;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:init");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:init");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:init");

        ok &= luaval_to_std_string(tolua_S, 5,&arg3, "ccui.RichElementText:init");

        ok &= luaval_to_std_string(tolua_S, 6,&arg4, "ccui.RichElementText:init");

        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichElementText_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementText:init",argc, 6);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichElementText_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_RichElementText_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.RichElementText",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 6)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string arg3;
        std::string arg4;
        double arg5;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementText:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementText:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementText:create");
        ok &= luaval_to_std_string(tolua_S, 5,&arg3, "ccui.RichElementText:create");
        ok &= luaval_to_std_string(tolua_S, 6,&arg4, "ccui.RichElementText:create");
        ok &= luaval_to_number(tolua_S, 7,&arg5, "ccui.RichElementText:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichElementText_create'", nullptr);
            return 0;
        }
        cocos2d::ui::RichElementText* ret = cocos2d::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5);
        object_to_luaval<cocos2d::ui::RichElementText>(tolua_S, "ccui.RichElementText",(cocos2d::ui::RichElementText*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.RichElementText:create",argc, 6);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichElementText_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_ui_RichElementText_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElementText* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichElementText_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::RichElementText();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.RichElementText");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementText:RichElementText",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichElementText_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_ui_RichElementText_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RichElementText)");
    return 0;
}

int lua_register_cocos2dx_ui_RichElementText(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccui.RichElementText");
    tolua_cclass(tolua_S,"RichElementText","ccui.RichElementText","ccui.RichElement",nullptr);

    tolua_beginmodule(tolua_S,"RichElementText");
        tolua_function(tolua_S,"new",lua_cocos2dx_ui_RichElementText_constructor);
        tolua_function(tolua_S,"init",lua_cocos2dx_ui_RichElementText_init);
        tolua_function(tolua_S,"create", lua_cocos2dx_ui_RichElementText_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::ui::RichElementText).name();
    g_luaType[typeName] = "ccui.RichElementText";
    g_typeCast["RichElementText"] = "ccui.RichElementText";
    return 1;
}

int lua_cocos2dx_ui_RichElementImage_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElementImage* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichElementImage",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichElementImage*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_RichElementImage_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string arg3;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementImage:init");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementImage:init");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementImage:init");

        ok &= luaval_to_std_string(tolua_S, 5,&arg3, "ccui.RichElementImage:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichElementImage_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementImage:init",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichElementImage_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_RichElementImage_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.RichElementImage",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string arg3;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementImage:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementImage:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementImage:create");
        ok &= luaval_to_std_string(tolua_S, 5,&arg3, "ccui.RichElementImage:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichElementImage_create'", nullptr);
            return 0;
        }
        cocos2d::ui::RichElementImage* ret = cocos2d::ui::RichElementImage::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::ui::RichElementImage>(tolua_S, "ccui.RichElementImage",(cocos2d::ui::RichElementImage*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.RichElementImage:create",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichElementImage_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_ui_RichElementImage_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElementImage* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichElementImage_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::RichElementImage();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.RichElementImage");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementImage:RichElementImage",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichElementImage_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_ui_RichElementImage_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RichElementImage)");
    return 0;
}

int lua_register_cocos2dx_ui_RichElementImage(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccui.RichElementImage");
    tolua_cclass(tolua_S,"RichElementImage","ccui.RichElementImage","ccui.RichElement",nullptr);

    tolua_beginmodule(tolua_S,"RichElementImage");
        tolua_function(tolua_S,"new",lua_cocos2dx_ui_RichElementImage_constructor);
        tolua_function(tolua_S,"init",lua_cocos2dx_ui_RichElementImage_init);
        tolua_function(tolua_S,"create", lua_cocos2dx_ui_RichElementImage_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::ui::RichElementImage).name();
    g_luaType[typeName] = "ccui.RichElementImage";
    g_typeCast["RichElementImage"] = "ccui.RichElementImage";
    return 1;
}

int lua_cocos2dx_ui_RichElementCustomNode_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElementCustomNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichElementCustomNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichElementCustomNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_RichElementCustomNode_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        cocos2d::Node* arg3;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementCustomNode:init");

        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementCustomNode:init");

        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementCustomNode:init");

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 5, "cc.Node",&arg3);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichElementCustomNode_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementCustomNode:init",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichElementCustomNode_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_RichElementCustomNode_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.RichElementCustomNode",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        cocos2d::Node* arg3;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichElementCustomNode:create");
        ok &= luaval_to_color3b(tolua_S, 3, &arg1, "ccui.RichElementCustomNode:create");
        ok &= luaval_to_uint16(tolua_S, 4,&arg2, "ccui.RichElementCustomNode:create");
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 5, "cc.Node",&arg3);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichElementCustomNode_create'", nullptr);
            return 0;
        }
        cocos2d::ui::RichElementCustomNode* ret = cocos2d::ui::RichElementCustomNode::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::ui::RichElementCustomNode>(tolua_S, "ccui.RichElementCustomNode",(cocos2d::ui::RichElementCustomNode*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.RichElementCustomNode:create",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichElementCustomNode_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_ui_RichElementCustomNode_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichElementCustomNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichElementCustomNode_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::RichElementCustomNode();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.RichElementCustomNode");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichElementCustomNode:RichElementCustomNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichElementCustomNode_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_ui_RichElementCustomNode_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RichElementCustomNode)");
    return 0;
}

int lua_register_cocos2dx_ui_RichElementCustomNode(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccui.RichElementCustomNode");
    tolua_cclass(tolua_S,"RichElementCustomNode","ccui.RichElementCustomNode","ccui.RichElement",nullptr);

    tolua_beginmodule(tolua_S,"RichElementCustomNode");
        tolua_function(tolua_S,"new",lua_cocos2dx_ui_RichElementCustomNode_constructor);
        tolua_function(tolua_S,"init",lua_cocos2dx_ui_RichElementCustomNode_init);
        tolua_function(tolua_S,"create", lua_cocos2dx_ui_RichElementCustomNode_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::ui::RichElementCustomNode).name();
    g_luaType[typeName] = "ccui.RichElementCustomNode";
    g_typeCast["RichElementCustomNode"] = "ccui.RichElementCustomNode";
    return 1;
}

int lua_cocos2dx_ui_RichText_insertElement(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_RichText_insertElement'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::ui::RichElement* arg0;
        int arg1;

        ok &= luaval_to_object<cocos2d::ui::RichElement>(tolua_S, 2, "ccui.RichElement",&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccui.RichText:insertElement");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichText_insertElement'", nullptr);
            return 0;
        }
        cobj->insertElement(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:insertElement",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichText_insertElement'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_RichText_pushBackElement(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_RichText_pushBackElement'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ui::RichElement* arg0;

        ok &= luaval_to_object<cocos2d::ui::RichElement>(tolua_S, 2, "ccui.RichElement",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichText_pushBackElement'", nullptr);
            return 0;
        }
        cobj->pushBackElement(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:pushBackElement",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichText_pushBackElement'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_RichText_setVerticalSpace(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_RichText_setVerticalSpace'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccui.RichText:setVerticalSpace");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichText_setVerticalSpace'", nullptr);
            return 0;
        }
        cobj->setVerticalSpace(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:setVerticalSpace",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichText_setVerticalSpace'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_RichText_formatText(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_RichText_formatText'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichText_formatText'", nullptr);
            return 0;
        }
        cobj->formatText();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:formatText",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichText_formatText'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_RichText_removeElement(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::RichText*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_RichText_removeElement'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::ui::RichElement* arg0;
            ok &= luaval_to_object<cocos2d::ui::RichElement>(tolua_S, 2, "ccui.RichElement",&arg0);

            if (!ok) { break; }
            cobj->removeElement(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.RichText:removeElement");

            if (!ok) { break; }
            cobj->removeElement(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.RichText:removeElement",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichText_removeElement'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_RichText_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.RichText",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichText_create'", nullptr);
            return 0;
        }
        cocos2d::ui::RichText* ret = cocos2d::ui::RichText::create();
        object_to_luaval<cocos2d::ui::RichText>(tolua_S, "ccui.RichText",(cocos2d::ui::RichText*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccui.RichText:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichText_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_ui_RichText_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::RichText* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_RichText_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::RichText();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.RichText");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.RichText:RichText",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_RichText_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_ui_RichText_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RichText)");
    return 0;
}

int lua_register_cocos2dx_ui_RichText(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccui.RichText");
    tolua_cclass(tolua_S,"RichText","ccui.RichText","ccui.Widget",nullptr);

    tolua_beginmodule(tolua_S,"RichText");
        tolua_function(tolua_S,"new",lua_cocos2dx_ui_RichText_constructor);
        tolua_function(tolua_S,"insertElement",lua_cocos2dx_ui_RichText_insertElement);
        tolua_function(tolua_S,"pushBackElement",lua_cocos2dx_ui_RichText_pushBackElement);
        tolua_function(tolua_S,"setVerticalSpace",lua_cocos2dx_ui_RichText_setVerticalSpace);
        tolua_function(tolua_S,"formatText",lua_cocos2dx_ui_RichText_formatText);
        tolua_function(tolua_S,"removeElement",lua_cocos2dx_ui_RichText_removeElement);
        tolua_function(tolua_S,"create", lua_cocos2dx_ui_RichText_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::ui::RichText).name();
    g_luaType[typeName] = "ccui.RichText";
    g_typeCast["RichText"] = "ccui.RichText";
    return 1;
}

int lua_cocos2dx_ui_Scale9Sprite_disableCascadeColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_disableCascadeColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_disableCascadeColor'", nullptr);
            return 0;
        }
        cobj->disableCascadeColor();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:disableCascadeColor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_disableCascadeColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_updateWithSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_updateWithSprite'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 6) {
            cocos2d::Sprite* arg0;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0);

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            cocos2d::Size arg4;
            ok &= luaval_to_size(tolua_S, 6, &arg4, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            cocos2d::Rect arg5;
            ok &= luaval_to_rect(tolua_S, 7, &arg5, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            bool ret = cobj->updateWithSprite(arg0, arg1, arg2, arg3, arg4, arg5);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 4) {
            cocos2d::Sprite* arg0;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0);

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            cocos2d::Rect arg3;
            ok &= luaval_to_rect(tolua_S, 5, &arg3, "ccui.Scale9Sprite:updateWithSprite");

            if (!ok) { break; }
            bool ret = cobj->updateWithSprite(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.Scale9Sprite:updateWithSprite",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_updateWithSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_isFlippedX(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_isFlippedX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_isFlippedX'", nullptr);
            return 0;
        }
        bool ret = cobj->isFlippedX();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:isFlippedX",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_isFlippedX'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_setScale9Enabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_setScale9Enabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Scale9Sprite:setScale9Enabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_setScale9Enabled'", nullptr);
            return 0;
        }
        cobj->setScale9Enabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setScale9Enabled",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_setScale9Enabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_setFlippedY(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_setFlippedY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Scale9Sprite:setFlippedY");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_setFlippedY'", nullptr);
            return 0;
        }
        cobj->setFlippedY(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setFlippedY",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_setFlippedY'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_setFlippedX(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_setFlippedX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccui.Scale9Sprite:setFlippedX");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_setFlippedX'", nullptr);
            return 0;
        }
        cobj->setFlippedX(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setFlippedX",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_setFlippedX'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_resizableSpriteWithCapInsets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_resizableSpriteWithCapInsets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Scale9Sprite:resizableSpriteWithCapInsets");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_resizableSpriteWithCapInsets'", nullptr);
            return 0;
        }
        cocos2d::ui::Scale9Sprite* ret = cobj->resizableSpriteWithCapInsets(arg0);
        object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:resizableSpriteWithCapInsets",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_resizableSpriteWithCapInsets'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_disableCascadeOpacity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_disableCascadeOpacity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_disableCascadeOpacity'", nullptr);
            return 0;
        }
        cobj->disableCascadeOpacity();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:disableCascadeOpacity",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_disableCascadeOpacity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_setState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_setState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ui::Scale9Sprite::State arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.Scale9Sprite:setState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_setState'", nullptr);
            return 0;
        }
        cobj->setState(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_setState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_setInsetBottom(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_setInsetBottom'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccui.Scale9Sprite:setInsetBottom");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_setInsetBottom'", nullptr);
            return 0;
        }
        cobj->setInsetBottom(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setInsetBottom",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_setInsetBottom'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_initWithSpriteFrameName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_initWithSpriteFrameName'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccui.Scale9Sprite:initWithSpriteFrameName");

            if (!ok) { break; }
            bool ret = cobj->initWithSpriteFrameName(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccui.Scale9Sprite:initWithSpriteFrameName");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:initWithSpriteFrameName");

            if (!ok) { break; }
            bool ret = cobj->initWithSpriteFrameName(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.Scale9Sprite:initWithSpriteFrameName",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_initWithSpriteFrameName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_getSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_getSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_getSprite'", nullptr);
            return 0;
        }
        cocos2d::Sprite* ret = cobj->getSprite();
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getSprite",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_getSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_setInsetTop(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_setInsetTop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccui.Scale9Sprite:setInsetTop");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_setInsetTop'", nullptr);
            return 0;
        }
        cobj->setInsetTop(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setInsetTop",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_setInsetTop'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_init'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 4) {
            cocos2d::Sprite* arg0;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0);

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            cocos2d::Rect arg3;
            ok &= luaval_to_rect(tolua_S, 5, &arg3, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            bool ret = cobj->init(arg0, arg1, arg2, arg3);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            bool ret = cobj->init();
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::Sprite* arg0;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0);

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            cocos2d::Rect arg2;
            ok &= luaval_to_rect(tolua_S, 4, &arg2, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            bool ret = cobj->init(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 6) {
            cocos2d::Sprite* arg0;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0);

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            bool arg2;
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            cocos2d::Size arg4;
            ok &= luaval_to_size(tolua_S, 6, &arg4, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            cocos2d::Rect arg5;
            ok &= luaval_to_rect(tolua_S, 7, &arg5, "ccui.Scale9Sprite:init");

            if (!ok) { break; }
            bool ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.Scale9Sprite:init",argc, 6);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_setPreferredSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_setPreferredSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Size arg0;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.Scale9Sprite:setPreferredSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_setPreferredSize'", nullptr);
            return 0;
        }
        cobj->setPreferredSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setPreferredSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_setPreferredSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_setSpriteFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_setSpriteFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::SpriteFrame* arg0;

        ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_setSpriteFrame'", nullptr);
            return 0;
        }
        cobj->setSpriteFrame(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::SpriteFrame* arg0;
        cocos2d::Rect arg1;

        ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0);

        ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:setSpriteFrame");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_setSpriteFrame'", nullptr);
            return 0;
        }
        cobj->setSpriteFrame(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setSpriteFrame",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_setSpriteFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_getBlendFunc'", nullptr);
            return 0;
        }
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getBlendFunc",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_getInsetBottom(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_getInsetBottom'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_getInsetBottom'", nullptr);
            return 0;
        }
        double ret = cobj->getInsetBottom();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getInsetBottom",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_getInsetBottom'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_getCapInsets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_getCapInsets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_getCapInsets'", nullptr);
            return 0;
        }
        cocos2d::Rect ret = cobj->getCapInsets();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getCapInsets",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_getCapInsets'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_isScale9Enabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_isScale9Enabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_isScale9Enabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isScale9Enabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:isScale9Enabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_isScale9Enabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_getInsetRight(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_getInsetRight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_getInsetRight'", nullptr);
            return 0;
        }
        double ret = cobj->getInsetRight();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getInsetRight",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_getInsetRight'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_getOriginalSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_getOriginalSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_getOriginalSize'", nullptr);
            return 0;
        }
        cocos2d::Size ret = cobj->getOriginalSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getOriginalSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_getOriginalSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_initWithFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_initWithFile'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccui.Scale9Sprite:initWithFile");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:initWithFile");

            if (!ok) { break; }
            bool ret = cobj->initWithFile(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccui.Scale9Sprite:initWithFile");

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:initWithFile");

            if (!ok) { break; }
            cocos2d::Rect arg2;
            ok &= luaval_to_rect(tolua_S, 4, &arg2, "ccui.Scale9Sprite:initWithFile");

            if (!ok) { break; }
            bool ret = cobj->initWithFile(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            cocos2d::Rect arg0;
            ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Scale9Sprite:initWithFile");

            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccui.Scale9Sprite:initWithFile");

            if (!ok) { break; }
            bool ret = cobj->initWithFile(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccui.Scale9Sprite:initWithFile");

            if (!ok) { break; }
            bool ret = cobj->initWithFile(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.Scale9Sprite:initWithFile",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_initWithFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "ccui.Scale9Sprite:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setBlendFunc",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_getInsetTop(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_getInsetTop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_getInsetTop'", nullptr);
            return 0;
        }
        double ret = cobj->getInsetTop();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getInsetTop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_getInsetTop'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_setInsetLeft(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_setInsetLeft'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccui.Scale9Sprite:setInsetLeft");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_setInsetLeft'", nullptr);
            return 0;
        }
        cobj->setInsetLeft(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setInsetLeft",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_setInsetLeft'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_initWithSpriteFrame(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_initWithSpriteFrame'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::SpriteFrame* arg0;
            ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0);

            if (!ok) { break; }
            bool ret = cobj->initWithSpriteFrame(arg0);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            cocos2d::SpriteFrame* arg0;
            ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0);

            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:initWithSpriteFrame");

            if (!ok) { break; }
            bool ret = cobj->initWithSpriteFrame(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.Scale9Sprite:initWithSpriteFrame",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_initWithSpriteFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_getPreferredSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_getPreferredSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_getPreferredSize'", nullptr);
            return 0;
        }
        cocos2d::Size ret = cobj->getPreferredSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getPreferredSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_getPreferredSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_setCapInsets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_setCapInsets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Scale9Sprite:setCapInsets");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_setCapInsets'", nullptr);
            return 0;
        }
        cobj->setCapInsets(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setCapInsets",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_setCapInsets'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_isFlippedY(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_isFlippedY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_isFlippedY'", nullptr);
            return 0;
        }
        bool ret = cobj->isFlippedY();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:isFlippedY",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_isFlippedY'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_getInsetLeft(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_getInsetLeft'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_getInsetLeft'", nullptr);
            return 0;
        }
        double ret = cobj->getInsetLeft();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:getInsetLeft",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_getInsetLeft'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_setInsetRight(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::Scale9Sprite*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_Scale9Sprite_setInsetRight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccui.Scale9Sprite:setInsetRight");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_setInsetRight'", nullptr);
            return 0;
        }
        cobj->setInsetRight(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:setInsetRight",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_setInsetRight'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 3)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccui.Scale9Sprite:create");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:create");
            if (!ok) { break; }
            cocos2d::Rect arg2;
            ok &= luaval_to_rect(tolua_S, 4, &arg2, "ccui.Scale9Sprite:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::create();
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            cocos2d::Rect arg0;
            ok &= luaval_to_rect(tolua_S, 2, &arg0, "ccui.Scale9Sprite:create");
            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccui.Scale9Sprite:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::create(arg0, arg1);
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccui.Scale9Sprite:create");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::create(arg0, arg1);
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccui.Scale9Sprite:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::create(arg0);
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccui.Scale9Sprite:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_createWithSpriteFrameName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccui.Scale9Sprite:createWithSpriteFrameName");
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:createWithSpriteFrameName");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName(arg0, arg1);
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccui.Scale9Sprite:createWithSpriteFrameName");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName(arg0);
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccui.Scale9Sprite:createWithSpriteFrameName",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_createWithSpriteFrameName'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_createWithSpriteFrame(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.Scale9Sprite",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            cocos2d::SpriteFrame* arg0;
            ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0);
            if (!ok) { break; }
            cocos2d::Rect arg1;
            ok &= luaval_to_rect(tolua_S, 3, &arg1, "ccui.Scale9Sprite:createWithSpriteFrame");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::createWithSpriteFrame(arg0, arg1);
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            cocos2d::SpriteFrame* arg0;
            ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0);
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::createWithSpriteFrame(arg0);
            object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccui.Scale9Sprite:createWithSpriteFrame",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_createWithSpriteFrame'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_ui_Scale9Sprite_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::Scale9Sprite* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_Scale9Sprite_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::Scale9Sprite();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.Scale9Sprite");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.Scale9Sprite:Scale9Sprite",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_Scale9Sprite_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_ui_Scale9Sprite_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Scale9Sprite)");
    return 0;
}

int lua_register_cocos2dx_ui_Scale9Sprite(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccui.Scale9Sprite");
    tolua_cclass(tolua_S,"Scale9Sprite","ccui.Scale9Sprite","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"Scale9Sprite");
        tolua_function(tolua_S,"new",lua_cocos2dx_ui_Scale9Sprite_constructor);
        tolua_function(tolua_S,"disableCascadeColor",lua_cocos2dx_ui_Scale9Sprite_disableCascadeColor);
        tolua_function(tolua_S,"updateWithSprite",lua_cocos2dx_ui_Scale9Sprite_updateWithSprite);
        tolua_function(tolua_S,"isFlippedX",lua_cocos2dx_ui_Scale9Sprite_isFlippedX);
        tolua_function(tolua_S,"setScale9Enabled",lua_cocos2dx_ui_Scale9Sprite_setScale9Enabled);
        tolua_function(tolua_S,"setFlippedY",lua_cocos2dx_ui_Scale9Sprite_setFlippedY);
        tolua_function(tolua_S,"setFlippedX",lua_cocos2dx_ui_Scale9Sprite_setFlippedX);
        tolua_function(tolua_S,"resizableSpriteWithCapInsets",lua_cocos2dx_ui_Scale9Sprite_resizableSpriteWithCapInsets);
        tolua_function(tolua_S,"disableCascadeOpacity",lua_cocos2dx_ui_Scale9Sprite_disableCascadeOpacity);
        tolua_function(tolua_S,"setState",lua_cocos2dx_ui_Scale9Sprite_setState);
        tolua_function(tolua_S,"setInsetBottom",lua_cocos2dx_ui_Scale9Sprite_setInsetBottom);
        tolua_function(tolua_S,"initWithSpriteFrameName",lua_cocos2dx_ui_Scale9Sprite_initWithSpriteFrameName);
        tolua_function(tolua_S,"getSprite",lua_cocos2dx_ui_Scale9Sprite_getSprite);
        tolua_function(tolua_S,"setInsetTop",lua_cocos2dx_ui_Scale9Sprite_setInsetTop);
        tolua_function(tolua_S,"init",lua_cocos2dx_ui_Scale9Sprite_init);
        tolua_function(tolua_S,"setPreferredSize",lua_cocos2dx_ui_Scale9Sprite_setPreferredSize);
        tolua_function(tolua_S,"setSpriteFrame",lua_cocos2dx_ui_Scale9Sprite_setSpriteFrame);
        tolua_function(tolua_S,"getBlendFunc",lua_cocos2dx_ui_Scale9Sprite_getBlendFunc);
        tolua_function(tolua_S,"getInsetBottom",lua_cocos2dx_ui_Scale9Sprite_getInsetBottom);
        tolua_function(tolua_S,"getCapInsets",lua_cocos2dx_ui_Scale9Sprite_getCapInsets);
        tolua_function(tolua_S,"isScale9Enabled",lua_cocos2dx_ui_Scale9Sprite_isScale9Enabled);
        tolua_function(tolua_S,"getInsetRight",lua_cocos2dx_ui_Scale9Sprite_getInsetRight);
        tolua_function(tolua_S,"getOriginalSize",lua_cocos2dx_ui_Scale9Sprite_getOriginalSize);
        tolua_function(tolua_S,"initWithFile",lua_cocos2dx_ui_Scale9Sprite_initWithFile);
        tolua_function(tolua_S,"setBlendFunc",lua_cocos2dx_ui_Scale9Sprite_setBlendFunc);
        tolua_function(tolua_S,"getInsetTop",lua_cocos2dx_ui_Scale9Sprite_getInsetTop);
        tolua_function(tolua_S,"setInsetLeft",lua_cocos2dx_ui_Scale9Sprite_setInsetLeft);
        tolua_function(tolua_S,"initWithSpriteFrame",lua_cocos2dx_ui_Scale9Sprite_initWithSpriteFrame);
        tolua_function(tolua_S,"getPreferredSize",lua_cocos2dx_ui_Scale9Sprite_getPreferredSize);
        tolua_function(tolua_S,"setCapInsets",lua_cocos2dx_ui_Scale9Sprite_setCapInsets);
        tolua_function(tolua_S,"isFlippedY",lua_cocos2dx_ui_Scale9Sprite_isFlippedY);
        tolua_function(tolua_S,"getInsetLeft",lua_cocos2dx_ui_Scale9Sprite_getInsetLeft);
        tolua_function(tolua_S,"setInsetRight",lua_cocos2dx_ui_Scale9Sprite_setInsetRight);
        tolua_function(tolua_S,"create", lua_cocos2dx_ui_Scale9Sprite_create);
        tolua_function(tolua_S,"createWithSpriteFrameName", lua_cocos2dx_ui_Scale9Sprite_createWithSpriteFrameName);
        tolua_function(tolua_S,"createWithSpriteFrame", lua_cocos2dx_ui_Scale9Sprite_createWithSpriteFrame);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::ui::Scale9Sprite).name();
    g_luaType[typeName] = "ccui.Scale9Sprite";
    g_typeCast["Scale9Sprite"] = "ccui.Scale9Sprite";
    return 1;
}

int lua_cocos2dx_ui_EditBox_keyboardDidShow(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_keyboardDidShow'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::IMEKeyboardNotificationInfo arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR IMEKeyboardNotificationInfo
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_keyboardDidShow'", nullptr);
            return 0;
        }
        cobj->keyboardDidShow(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:keyboardDidShow",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_keyboardDidShow'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_getScriptEditBoxHandler(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_getScriptEditBoxHandler'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_getScriptEditBoxHandler'", nullptr);
            return 0;
        }
        int ret = cobj->getScriptEditBoxHandler();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getScriptEditBoxHandler",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_getScriptEditBoxHandler'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_getText(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_getText'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_getText'", nullptr);
            return 0;
        }
        const char* ret = cobj->getText();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getText",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_getText'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_keyboardDidHide(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_keyboardDidHide'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::IMEKeyboardNotificationInfo arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR IMEKeyboardNotificationInfo
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_keyboardDidHide'", nullptr);
            return 0;
        }
        cobj->keyboardDidHide(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:keyboardDidHide",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_keyboardDidHide'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_setPlaceholderFontName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_setPlaceholderFontName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccui.EditBox:setPlaceholderFontName"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_setPlaceholderFontName'", nullptr);
            return 0;
        }
        cobj->setPlaceholderFontName(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setPlaceholderFontName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_setPlaceholderFontName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_getPlaceHolder(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_getPlaceHolder'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_getPlaceHolder'", nullptr);
            return 0;
        }
        const char* ret = cobj->getPlaceHolder();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getPlaceHolder",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_getPlaceHolder'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_setFontName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_setFontName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccui.EditBox:setFontName"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_setFontName'", nullptr);
            return 0;
        }
        cobj->setFontName(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setFontName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_setFontName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_registerScriptEditBoxHandler(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_registerScriptEditBoxHandler'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.EditBox:registerScriptEditBoxHandler");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_registerScriptEditBoxHandler'", nullptr);
            return 0;
        }
        cobj->registerScriptEditBoxHandler(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:registerScriptEditBoxHandler",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_registerScriptEditBoxHandler'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_setPlaceholderFontSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_setPlaceholderFontSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.EditBox:setPlaceholderFontSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_setPlaceholderFontSize'", nullptr);
            return 0;
        }
        cobj->setPlaceholderFontSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setPlaceholderFontSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_setPlaceholderFontSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_setInputMode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_setInputMode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ui::EditBox::InputMode arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.EditBox:setInputMode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_setInputMode'", nullptr);
            return 0;
        }
        cobj->setInputMode(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setInputMode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_setInputMode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_unregisterScriptEditBoxHandler(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_unregisterScriptEditBoxHandler'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_unregisterScriptEditBoxHandler'", nullptr);
            return 0;
        }
        cobj->unregisterScriptEditBoxHandler();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:unregisterScriptEditBoxHandler",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_unregisterScriptEditBoxHandler'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_keyboardWillShow(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_keyboardWillShow'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::IMEKeyboardNotificationInfo arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR IMEKeyboardNotificationInfo
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_keyboardWillShow'", nullptr);
            return 0;
        }
        cobj->keyboardWillShow(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:keyboardWillShow",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_keyboardWillShow'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_setPlaceholderFontColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_setPlaceholderFontColor'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.EditBox:setPlaceholderFontColor");

            if (!ok) { break; }
            cobj->setPlaceholderFontColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Color3B arg0;
            ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccui.EditBox:setPlaceholderFontColor");

            if (!ok) { break; }
            cobj->setPlaceholderFontColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.EditBox:setPlaceholderFontColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_setPlaceholderFontColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_setFontColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_setFontColor'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Color4B arg0;
            ok &=luaval_to_color4b(tolua_S, 2, &arg0, "ccui.EditBox:setFontColor");

            if (!ok) { break; }
            cobj->setFontColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Color3B arg0;
            ok &= luaval_to_color3b(tolua_S, 2, &arg0, "ccui.EditBox:setFontColor");

            if (!ok) { break; }
            cobj->setFontColor(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.EditBox:setFontColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_setFontColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_keyboardWillHide(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_keyboardWillHide'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::IMEKeyboardNotificationInfo arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR IMEKeyboardNotificationInfo
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_keyboardWillHide'", nullptr);
            return 0;
        }
        cobj->keyboardWillHide(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:keyboardWillHide",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_keyboardWillHide'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_touchDownAction(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_touchDownAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Ref* arg0;
        cocos2d::ui::Widget::TouchEventType arg1;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccui.EditBox:touchDownAction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_touchDownAction'", nullptr);
            return 0;
        }
        cobj->touchDownAction(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:touchDownAction",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_touchDownAction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_setPlaceholderFont(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_setPlaceholderFont'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        int arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccui.EditBox:setPlaceholderFont"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccui.EditBox:setPlaceholderFont");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_setPlaceholderFont'", nullptr);
            return 0;
        }
        cobj->setPlaceholderFont(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setPlaceholderFont",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_setPlaceholderFont'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_setFontSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_setFontSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.EditBox:setFontSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_setFontSize'", nullptr);
            return 0;
        }
        cobj->setFontSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setFontSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_setFontSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_initWithSizeAndBackgroundSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_initWithSizeAndBackgroundSprite'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg1;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 3, "ccui.Scale9Sprite",&arg1);

            if (!ok) { break; }
            bool ret = cobj->initWithSizeAndBackgroundSprite(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            bool ret = cobj->initWithSizeAndBackgroundSprite(arg0, arg1);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            cocos2d::ui::Widget::TextureResType arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccui.EditBox:initWithSizeAndBackgroundSprite");

            if (!ok) { break; }
            bool ret = cobj->initWithSizeAndBackgroundSprite(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccui.EditBox:initWithSizeAndBackgroundSprite",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_initWithSizeAndBackgroundSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_setPlaceHolder(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_setPlaceHolder'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccui.EditBox:setPlaceHolder"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_setPlaceHolder'", nullptr);
            return 0;
        }
        cobj->setPlaceHolder(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setPlaceHolder",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_setPlaceHolder'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_setReturnType(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_setReturnType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ui::EditBox::KeyboardReturnType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.EditBox:setReturnType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_setReturnType'", nullptr);
            return 0;
        }
        cobj->setReturnType(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setReturnType",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_setReturnType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_setInputFlag(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_setInputFlag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ui::EditBox::InputFlag arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.EditBox:setInputFlag");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_setInputFlag'", nullptr);
            return 0;
        }
        cobj->setInputFlag(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setInputFlag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_setInputFlag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_getMaxLength(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_getMaxLength'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_getMaxLength'", nullptr);
            return 0;
        }
        int ret = cobj->getMaxLength();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:getMaxLength",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_getMaxLength'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_setText(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_setText'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccui.EditBox:setText"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_setText'", nullptr);
            return 0;
        }
        cobj->setText(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setText",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_setText'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_setMaxLength(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_setMaxLength'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccui.EditBox:setMaxLength");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_setMaxLength'", nullptr);
            return 0;
        }
        cobj->setMaxLength(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setMaxLength",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_setMaxLength'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_setFont(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ui::EditBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ui_EditBox_setFont'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        int arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "ccui.EditBox:setFont"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccui.EditBox:setFont");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_setFont'", nullptr);
            return 0;
        }
        cobj->setFont(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:setFont",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_setFont'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_ui_EditBox_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:create");
            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1);
            object_to_luaval<cocos2d::ui::EditBox>(tolua_S, "ccui.EditBox",(cocos2d::ui::EditBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:create");
            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::Widget::TextureResType arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::ui::EditBox>(tolua_S, "ccui.EditBox",(cocos2d::ui::EditBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg1;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 3, "ccui.Scale9Sprite",&arg1);
            if (!ok) { break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1);
            object_to_luaval<cocos2d::ui::EditBox>(tolua_S, "ccui.EditBox",(cocos2d::ui::EditBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg1;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 3, "ccui.Scale9Sprite",&arg1);
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg2;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 4, "ccui.Scale9Sprite",&arg2);
            if (!ok) { break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::ui::EditBox>(tolua_S, "ccui.EditBox",(cocos2d::ui::EditBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "ccui.EditBox:create");
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg1;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 3, "ccui.Scale9Sprite",&arg1);
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg2;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 4, "ccui.Scale9Sprite",&arg2);
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg3;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 5, "ccui.Scale9Sprite",&arg3);
            if (!ok) { break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::ui::EditBox>(tolua_S, "ccui.EditBox",(cocos2d::ui::EditBox*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccui.EditBox:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_ui_EditBox_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ui::EditBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ui_EditBox_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::ui::EditBox();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccui.EditBox");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccui.EditBox:EditBox",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ui_EditBox_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_ui_EditBox_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EditBox)");
    return 0;
}

int lua_register_cocos2dx_ui_EditBox(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccui.EditBox");
    tolua_cclass(tolua_S,"EditBox","ccui.EditBox","ccui.Widget",nullptr);

    tolua_beginmodule(tolua_S,"EditBox");
        tolua_function(tolua_S,"new",lua_cocos2dx_ui_EditBox_constructor);
        tolua_function(tolua_S,"keyboardDidShow",lua_cocos2dx_ui_EditBox_keyboardDidShow);
        tolua_function(tolua_S,"getScriptEditBoxHandler",lua_cocos2dx_ui_EditBox_getScriptEditBoxHandler);
        tolua_function(tolua_S,"getText",lua_cocos2dx_ui_EditBox_getText);
        tolua_function(tolua_S,"keyboardDidHide",lua_cocos2dx_ui_EditBox_keyboardDidHide);
        tolua_function(tolua_S,"setPlaceholderFontName",lua_cocos2dx_ui_EditBox_setPlaceholderFontName);
        tolua_function(tolua_S,"getPlaceHolder",lua_cocos2dx_ui_EditBox_getPlaceHolder);
        tolua_function(tolua_S,"setFontName",lua_cocos2dx_ui_EditBox_setFontName);
        tolua_function(tolua_S,"registerScriptEditBoxHandler",lua_cocos2dx_ui_EditBox_registerScriptEditBoxHandler);
        tolua_function(tolua_S,"setPlaceholderFontSize",lua_cocos2dx_ui_EditBox_setPlaceholderFontSize);
        tolua_function(tolua_S,"setInputMode",lua_cocos2dx_ui_EditBox_setInputMode);
        tolua_function(tolua_S,"unregisterScriptEditBoxHandler",lua_cocos2dx_ui_EditBox_unregisterScriptEditBoxHandler);
        tolua_function(tolua_S,"keyboardWillShow",lua_cocos2dx_ui_EditBox_keyboardWillShow);
        tolua_function(tolua_S,"setPlaceholderFontColor",lua_cocos2dx_ui_EditBox_setPlaceholderFontColor);
        tolua_function(tolua_S,"setFontColor",lua_cocos2dx_ui_EditBox_setFontColor);
        tolua_function(tolua_S,"keyboardWillHide",lua_cocos2dx_ui_EditBox_keyboardWillHide);
        tolua_function(tolua_S,"touchDownAction",lua_cocos2dx_ui_EditBox_touchDownAction);
        tolua_function(tolua_S,"setPlaceholderFont",lua_cocos2dx_ui_EditBox_setPlaceholderFont);
        tolua_function(tolua_S,"setFontSize",lua_cocos2dx_ui_EditBox_setFontSize);
        tolua_function(tolua_S,"initWithSizeAndBackgroundSprite",lua_cocos2dx_ui_EditBox_initWithSizeAndBackgroundSprite);
        tolua_function(tolua_S,"setPlaceHolder",lua_cocos2dx_ui_EditBox_setPlaceHolder);
        tolua_function(tolua_S,"setReturnType",lua_cocos2dx_ui_EditBox_setReturnType);
        tolua_function(tolua_S,"setInputFlag",lua_cocos2dx_ui_EditBox_setInputFlag);
        tolua_function(tolua_S,"getMaxLength",lua_cocos2dx_ui_EditBox_getMaxLength);
        tolua_function(tolua_S,"setText",lua_cocos2dx_ui_EditBox_setText);
        tolua_function(tolua_S,"setMaxLength",lua_cocos2dx_ui_EditBox_setMaxLength);
        tolua_function(tolua_S,"setFont",lua_cocos2dx_ui_EditBox_setFont);
        tolua_function(tolua_S,"create", lua_cocos2dx_ui_EditBox_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::ui::EditBox).name();
    g_luaType[typeName] = "ccui.EditBox";
    g_typeCast["EditBox"] = "ccui.EditBox";
    return 1;
}
TOLUA_API int register_all_cocos2dx_ui(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ccui",0);
	tolua_beginmodule(tolua_S,"ccui");

	lua_register_cocos2dx_ui_RichElement(tolua_S);
	lua_register_cocos2dx_ui_Widget(tolua_S);
	lua_register_cocos2dx_ui_Scale9Sprite(tolua_S);
	lua_register_cocos2dx_ui_EditBox(tolua_S);
	lua_register_cocos2dx_ui_RichElementText(tolua_S);
	lua_register_cocos2dx_ui_RichElementCustomNode(tolua_S);
	lua_register_cocos2dx_ui_RichText(tolua_S);
	lua_register_cocos2dx_ui_RichElementImage(tolua_S);
	lua_register_cocos2dx_ui_TextField(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

