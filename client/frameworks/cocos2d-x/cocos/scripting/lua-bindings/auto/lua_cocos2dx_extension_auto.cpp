#include "lua_cocos2dx_extension_auto.hpp"
#include "cocos-ext.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_extension_Control_setEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Control* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Control",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_setEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.Control:setEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_Control_setEnabled'", nullptr);
            return 0;
        }
        cobj->setEnabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Control:setEnabled",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_setEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_Control_getState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Control* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Control",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_getState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_Control_getState'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getState();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Control:getState",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_getState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_Control_sendActionsForControlEvents(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Control* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Control",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_sendActionsForControlEvents'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::Control::EventType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.Control:sendActionsForControlEvents");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_Control_sendActionsForControlEvents'", nullptr);
            return 0;
        }
        cobj->sendActionsForControlEvents(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Control:sendActionsForControlEvents",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_sendActionsForControlEvents'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_Control_setSelected(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Control* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Control",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_setSelected'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.Control:setSelected");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_Control_setSelected'", nullptr);
            return 0;
        }
        cobj->setSelected(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Control:setSelected",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_setSelected'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_Control_isEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Control* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Control",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_isEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_Control_isEnabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Control:isEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_isEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_Control_needsLayout(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Control* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Control",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_needsLayout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_Control_needsLayout'", nullptr);
            return 0;
        }
        cobj->needsLayout();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Control:needsLayout",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_needsLayout'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_Control_hasVisibleParents(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Control* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Control",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_hasVisibleParents'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_Control_hasVisibleParents'", nullptr);
            return 0;
        }
        bool ret = cobj->hasVisibleParents();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Control:hasVisibleParents",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_hasVisibleParents'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_Control_isSelected(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Control* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Control",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_isSelected'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_Control_isSelected'", nullptr);
            return 0;
        }
        bool ret = cobj->isSelected();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Control:isSelected",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_isSelected'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_Control_isTouchInside(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Control* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Control",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_isTouchInside'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Touch* arg0;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_Control_isTouchInside'", nullptr);
            return 0;
        }
        bool ret = cobj->isTouchInside(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Control:isTouchInside",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_isTouchInside'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_Control_setHighlighted(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Control* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Control",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_setHighlighted'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.Control:setHighlighted");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_Control_setHighlighted'", nullptr);
            return 0;
        }
        cobj->setHighlighted(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Control:setHighlighted",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_setHighlighted'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_Control_getTouchLocation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Control* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Control",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_getTouchLocation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Touch* arg0;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_Control_getTouchLocation'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getTouchLocation(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Control:getTouchLocation",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_getTouchLocation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_Control_isHighlighted(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::Control* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Control",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::Control*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_Control_isHighlighted'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_Control_isHighlighted'", nullptr);
            return 0;
        }
        bool ret = cobj->isHighlighted();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Control:isHighlighted",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_isHighlighted'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_Control_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Control",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_Control_create'", nullptr);
            return 0;
        }
        cocos2d::extension::Control* ret = cocos2d::extension::Control::create();
        object_to_luaval<cocos2d::extension::Control>(tolua_S, "cc.Control",(cocos2d::extension::Control*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Control:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_Control_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_extension_Control_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Control)");
    return 0;
}

int lua_register_cocos2dx_extension_Control(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Control");
    tolua_cclass(tolua_S,"Control","cc.Control","cc.Layer",nullptr);

    tolua_beginmodule(tolua_S,"Control");
        tolua_function(tolua_S,"setEnabled",lua_cocos2dx_extension_Control_setEnabled);
        tolua_function(tolua_S,"getState",lua_cocos2dx_extension_Control_getState);
        tolua_function(tolua_S,"sendActionsForControlEvents",lua_cocos2dx_extension_Control_sendActionsForControlEvents);
        tolua_function(tolua_S,"setSelected",lua_cocos2dx_extension_Control_setSelected);
        tolua_function(tolua_S,"isEnabled",lua_cocos2dx_extension_Control_isEnabled);
        tolua_function(tolua_S,"needsLayout",lua_cocos2dx_extension_Control_needsLayout);
        tolua_function(tolua_S,"hasVisibleParents",lua_cocos2dx_extension_Control_hasVisibleParents);
        tolua_function(tolua_S,"isSelected",lua_cocos2dx_extension_Control_isSelected);
        tolua_function(tolua_S,"isTouchInside",lua_cocos2dx_extension_Control_isTouchInside);
        tolua_function(tolua_S,"setHighlighted",lua_cocos2dx_extension_Control_setHighlighted);
        tolua_function(tolua_S,"getTouchLocation",lua_cocos2dx_extension_Control_getTouchLocation);
        tolua_function(tolua_S,"isHighlighted",lua_cocos2dx_extension_Control_isHighlighted);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_Control_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::Control).name();
    g_luaType[typeName] = "cc.Control";
    g_typeCast["Control"] = "cc.Control";
    return 1;
}

int lua_cocos2dx_extension_ControlButton_isPushed(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_isPushed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_isPushed'", nullptr);
            return 0;
        }
        bool ret = cobj->isPushed();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:isPushed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_isPushed'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_setTitleLabelForState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleLabelForState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Node* arg0;
        cocos2d::extension::Control::State arg1;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.ControlButton:setTitleLabelForState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_setTitleLabelForState'", nullptr);
            return 0;
        }
        cobj->setTitleLabelForState(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:setTitleLabelForState",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleLabelForState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_setAdjustBackgroundImage(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setAdjustBackgroundImage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.ControlButton:setAdjustBackgroundImage");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_setAdjustBackgroundImage'", nullptr);
            return 0;
        }
        cobj->setAdjustBackgroundImage(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:setAdjustBackgroundImage",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setAdjustBackgroundImage'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_setTitleForState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleForState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        cocos2d::extension::Control::State arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.ControlButton:setTitleForState");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.ControlButton:setTitleForState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_setTitleForState'", nullptr);
            return 0;
        }
        cobj->setTitleForState(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:setTitleForState",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleForState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_setLabelAnchorPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setLabelAnchorPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ControlButton:setLabelAnchorPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_setLabelAnchorPoint'", nullptr);
            return 0;
        }
        cobj->setLabelAnchorPoint(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:setLabelAnchorPoint",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setLabelAnchorPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getLabelAnchorPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getLabelAnchorPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_getLabelAnchorPoint'", nullptr);
            return 0;
        }
        const cocos2d::Vec2& ret = cobj->getLabelAnchorPoint();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:getLabelAnchorPoint",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getLabelAnchorPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getTitleTTFSizeForState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleTTFSizeForState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::Control::State arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ControlButton:getTitleTTFSizeForState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_getTitleTTFSizeForState'", nullptr);
            return 0;
        }
        double ret = cobj->getTitleTTFSizeForState(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:getTitleTTFSizeForState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleTTFSizeForState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_setTitleTTFForState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleTTFForState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        cocos2d::extension::Control::State arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.ControlButton:setTitleTTFForState");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.ControlButton:setTitleTTFForState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_setTitleTTFForState'", nullptr);
            return 0;
        }
        cobj->setTitleTTFForState(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:setTitleTTFForState",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleTTFForState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_setTitleTTFSizeForState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleTTFSizeForState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        cocos2d::extension::Control::State arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ControlButton:setTitleTTFSizeForState");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.ControlButton:setTitleTTFSizeForState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_setTitleTTFSizeForState'", nullptr);
            return 0;
        }
        cobj->setTitleTTFSizeForState(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:setTitleTTFSizeForState",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleTTFSizeForState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_setTitleLabel(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleLabel'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Node* arg0;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_setTitleLabel'", nullptr);
            return 0;
        }
        cobj->setTitleLabel(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:setTitleLabel",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleLabel'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_setPreferredSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setPreferredSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Size arg0;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.ControlButton:setPreferredSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_setPreferredSize'", nullptr);
            return 0;
        }
        cobj->setPreferredSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:setPreferredSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setPreferredSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getCurrentTitleColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getCurrentTitleColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_getCurrentTitleColor'", nullptr);
            return 0;
        }
        const cocos2d::Color3B& ret = cobj->getCurrentTitleColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:getCurrentTitleColor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getCurrentTitleColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_setZoomOnTouchDown(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setZoomOnTouchDown'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.ControlButton:setZoomOnTouchDown");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_setZoomOnTouchDown'", nullptr);
            return 0;
        }
        cobj->setZoomOnTouchDown(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:setZoomOnTouchDown",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setZoomOnTouchDown'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getBackgroundSpriteForState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSpriteForState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::Control::State arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ControlButton:getBackgroundSpriteForState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSpriteForState'", nullptr);
            return 0;
        }
        cocos2d::ui::Scale9Sprite* ret = cobj->getBackgroundSpriteForState(arg0);
        object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:getBackgroundSpriteForState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSpriteForState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getHorizontalOrigin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getHorizontalOrigin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_getHorizontalOrigin'", nullptr);
            return 0;
        }
        int ret = cobj->getHorizontalOrigin();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:getHorizontalOrigin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getHorizontalOrigin'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_setTitleBMFontForState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleBMFontForState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        cocos2d::extension::Control::State arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.ControlButton:setTitleBMFontForState");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.ControlButton:setTitleBMFontForState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_setTitleBMFontForState'", nullptr);
            return 0;
        }
        cobj->setTitleBMFontForState(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:setTitleBMFontForState",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleBMFontForState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getScaleRatio(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getScaleRatio'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_getScaleRatio'", nullptr);
            return 0;
        }
        double ret = cobj->getScaleRatio();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:getScaleRatio",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getScaleRatio'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getTitleTTFForState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleTTFForState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::Control::State arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ControlButton:getTitleTTFForState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_getTitleTTFForState'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getTitleTTFForState(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:getTitleTTFForState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleTTFForState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getBackgroundSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSprite'", nullptr);
            return 0;
        }
        cocos2d::ui::Scale9Sprite* ret = cobj->getBackgroundSprite();
        object_to_luaval<cocos2d::ui::Scale9Sprite>(tolua_S, "ccui.Scale9Sprite",(cocos2d::ui::Scale9Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:getBackgroundSprite",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getBackgroundSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getTitleColorForState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleColorForState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::Control::State arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ControlButton:getTitleColorForState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_getTitleColorForState'", nullptr);
            return 0;
        }
        cocos2d::Color3B ret = cobj->getTitleColorForState(arg0);
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:getTitleColorForState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleColorForState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_setTitleColorForState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setTitleColorForState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Color3B arg0;
        cocos2d::extension::Control::State arg1;

        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "cc.ControlButton:setTitleColorForState");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.ControlButton:setTitleColorForState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_setTitleColorForState'", nullptr);
            return 0;
        }
        cobj->setTitleColorForState(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:setTitleColorForState",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setTitleColorForState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_doesAdjustBackgroundImage(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_doesAdjustBackgroundImage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_doesAdjustBackgroundImage'", nullptr);
            return 0;
        }
        bool ret = cobj->doesAdjustBackgroundImage();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:doesAdjustBackgroundImage",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_doesAdjustBackgroundImage'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::SpriteFrame* arg0;
        cocos2d::extension::Control::State arg1;

        ok &= luaval_to_object<cocos2d::SpriteFrame>(tolua_S, 2, "cc.SpriteFrame",&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.ControlButton:setBackgroundSpriteFrameForState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState'", nullptr);
            return 0;
        }
        cobj->setBackgroundSpriteFrameForState(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:setBackgroundSpriteFrameForState",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_setBackgroundSpriteForState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteForState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::ui::Scale9Sprite* arg0;
        cocos2d::extension::Control::State arg1;

        ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 2, "ccui.Scale9Sprite",&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.ControlButton:setBackgroundSpriteForState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteForState'", nullptr);
            return 0;
        }
        cobj->setBackgroundSpriteForState(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:setBackgroundSpriteForState",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSpriteForState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_setScaleRatio(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setScaleRatio'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ControlButton:setScaleRatio");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_setScaleRatio'", nullptr);
            return 0;
        }
        cobj->setScaleRatio(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:setScaleRatio",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setScaleRatio'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_setBackgroundSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ui::Scale9Sprite* arg0;

        ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 2, "ccui.Scale9Sprite",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSprite'", nullptr);
            return 0;
        }
        cobj->setBackgroundSprite(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:setBackgroundSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setBackgroundSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getTitleLabel(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleLabel'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_getTitleLabel'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->getTitleLabel();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:getTitleLabel",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleLabel'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getPreferredSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getPreferredSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_getPreferredSize'", nullptr);
            return 0;
        }
        const cocos2d::Size& ret = cobj->getPreferredSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:getPreferredSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getPreferredSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getVerticalMargin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getVerticalMargin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_getVerticalMargin'", nullptr);
            return 0;
        }
        int ret = cobj->getVerticalMargin();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:getVerticalMargin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getVerticalMargin'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getTitleLabelForState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleLabelForState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::Control::State arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ControlButton:getTitleLabelForState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_getTitleLabelForState'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->getTitleLabelForState(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:getTitleLabelForState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleLabelForState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_setMargins(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_setMargins'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ControlButton:setMargins");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.ControlButton:setMargins");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_setMargins'", nullptr);
            return 0;
        }
        cobj->setMargins(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:setMargins",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_setMargins'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getCurrentTitle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getCurrentTitle'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            std::string ret = cobj->getCurrentTitle();
            tolua_pushcppstring(tolua_S,ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            const std::string& ret = cobj->getCurrentTitle();
            tolua_pushcppstring(tolua_S,ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.ControlButton:getCurrentTitle",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getCurrentTitle'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getTitleBMFontForState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleBMFontForState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::Control::State arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ControlButton:getTitleBMFontForState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_getTitleBMFontForState'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getTitleBMFontForState(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:getTitleBMFontForState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleBMFontForState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getZoomOnTouchDown(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getZoomOnTouchDown'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_getZoomOnTouchDown'", nullptr);
            return 0;
        }
        bool ret = cobj->getZoomOnTouchDown();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:getZoomOnTouchDown",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getZoomOnTouchDown'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_getTitleForState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlButton* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlButton*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlButton_getTitleForState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::Control::State arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ControlButton:getTitleForState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlButton_getTitleForState'", nullptr);
            return 0;
        }
        std::string ret = cobj->getTitleForState(arg0);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlButton:getTitleForState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_getTitleForState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlButton_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ControlButton",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            cocos2d::ui::Scale9Sprite* arg0;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 2, "ccui.Scale9Sprite",&arg0);
            if (!ok) { break; }
            cocos2d::extension::ControlButton* ret = cocos2d::extension::ControlButton::create(arg0);
            object_to_luaval<cocos2d::extension::ControlButton>(tolua_S, "cc.ControlButton",(cocos2d::extension::ControlButton*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::ControlButton* ret = cocos2d::extension::ControlButton::create();
            object_to_luaval<cocos2d::extension::ControlButton>(tolua_S, "cc.ControlButton",(cocos2d::extension::ControlButton*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
            if (!ok) { break; }
            cocos2d::ui::Scale9Sprite* arg1;
            ok &= luaval_to_object<cocos2d::ui::Scale9Sprite>(tolua_S, 3, "ccui.Scale9Sprite",&arg1);
            if (!ok) { break; }
            cocos2d::extension::ControlButton* ret = cocos2d::extension::ControlButton::create(arg0, arg1);
            object_to_luaval<cocos2d::extension::ControlButton>(tolua_S, "cc.ControlButton",(cocos2d::extension::ControlButton*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.ControlButton:create");
            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.ControlButton:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.ControlButton:create");
            if (!ok) { break; }
            cocos2d::extension::ControlButton* ret = cocos2d::extension::ControlButton::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::extension::ControlButton>(tolua_S, "cc.ControlButton",(cocos2d::extension::ControlButton*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.ControlButton:create",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlButton_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_extension_ControlButton_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ControlButton)");
    return 0;
}

int lua_register_cocos2dx_extension_ControlButton(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.ControlButton");
    tolua_cclass(tolua_S,"ControlButton","cc.ControlButton","cc.Control",nullptr);

    tolua_beginmodule(tolua_S,"ControlButton");
        tolua_function(tolua_S,"isPushed",lua_cocos2dx_extension_ControlButton_isPushed);
        tolua_function(tolua_S,"setTitleLabelForState",lua_cocos2dx_extension_ControlButton_setTitleLabelForState);
        tolua_function(tolua_S,"setAdjustBackgroundImage",lua_cocos2dx_extension_ControlButton_setAdjustBackgroundImage);
        tolua_function(tolua_S,"setTitleForState",lua_cocos2dx_extension_ControlButton_setTitleForState);
        tolua_function(tolua_S,"setLabelAnchorPoint",lua_cocos2dx_extension_ControlButton_setLabelAnchorPoint);
        tolua_function(tolua_S,"getLabelAnchorPoint",lua_cocos2dx_extension_ControlButton_getLabelAnchorPoint);
        tolua_function(tolua_S,"getTitleTTFSizeForState",lua_cocos2dx_extension_ControlButton_getTitleTTFSizeForState);
        tolua_function(tolua_S,"setTitleTTFForState",lua_cocos2dx_extension_ControlButton_setTitleTTFForState);
        tolua_function(tolua_S,"setTitleTTFSizeForState",lua_cocos2dx_extension_ControlButton_setTitleTTFSizeForState);
        tolua_function(tolua_S,"setTitleLabel",lua_cocos2dx_extension_ControlButton_setTitleLabel);
        tolua_function(tolua_S,"setPreferredSize",lua_cocos2dx_extension_ControlButton_setPreferredSize);
        tolua_function(tolua_S,"getCurrentTitleColor",lua_cocos2dx_extension_ControlButton_getCurrentTitleColor);
        tolua_function(tolua_S,"setZoomOnTouchDown",lua_cocos2dx_extension_ControlButton_setZoomOnTouchDown);
        tolua_function(tolua_S,"getBackgroundSpriteForState",lua_cocos2dx_extension_ControlButton_getBackgroundSpriteForState);
        tolua_function(tolua_S,"getHorizontalOrigin",lua_cocos2dx_extension_ControlButton_getHorizontalOrigin);
        tolua_function(tolua_S,"setTitleBMFontForState",lua_cocos2dx_extension_ControlButton_setTitleBMFontForState);
        tolua_function(tolua_S,"getScaleRatio",lua_cocos2dx_extension_ControlButton_getScaleRatio);
        tolua_function(tolua_S,"getTitleTTFForState",lua_cocos2dx_extension_ControlButton_getTitleTTFForState);
        tolua_function(tolua_S,"getBackgroundSprite",lua_cocos2dx_extension_ControlButton_getBackgroundSprite);
        tolua_function(tolua_S,"getTitleColorForState",lua_cocos2dx_extension_ControlButton_getTitleColorForState);
        tolua_function(tolua_S,"setTitleColorForState",lua_cocos2dx_extension_ControlButton_setTitleColorForState);
        tolua_function(tolua_S,"doesAdjustBackgroundImage",lua_cocos2dx_extension_ControlButton_doesAdjustBackgroundImage);
        tolua_function(tolua_S,"setBackgroundSpriteFrameForState",lua_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState);
        tolua_function(tolua_S,"setBackgroundSpriteForState",lua_cocos2dx_extension_ControlButton_setBackgroundSpriteForState);
        tolua_function(tolua_S,"setScaleRatio",lua_cocos2dx_extension_ControlButton_setScaleRatio);
        tolua_function(tolua_S,"setBackgroundSprite",lua_cocos2dx_extension_ControlButton_setBackgroundSprite);
        tolua_function(tolua_S,"getTitleLabel",lua_cocos2dx_extension_ControlButton_getTitleLabel);
        tolua_function(tolua_S,"getPreferredSize",lua_cocos2dx_extension_ControlButton_getPreferredSize);
        tolua_function(tolua_S,"getVerticalMargin",lua_cocos2dx_extension_ControlButton_getVerticalMargin);
        tolua_function(tolua_S,"getTitleLabelForState",lua_cocos2dx_extension_ControlButton_getTitleLabelForState);
        tolua_function(tolua_S,"setMargins",lua_cocos2dx_extension_ControlButton_setMargins);
        tolua_function(tolua_S,"getCurrentTitle",lua_cocos2dx_extension_ControlButton_getCurrentTitle);
        tolua_function(tolua_S,"getTitleBMFontForState",lua_cocos2dx_extension_ControlButton_getTitleBMFontForState);
        tolua_function(tolua_S,"getZoomOnTouchDown",lua_cocos2dx_extension_ControlButton_getZoomOnTouchDown);
        tolua_function(tolua_S,"getTitleForState",lua_cocos2dx_extension_ControlButton_getTitleForState);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_ControlButton_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::ControlButton).name();
    g_luaType[typeName] = "cc.ControlButton";
    g_typeCast["ControlButton"] = "cc.ControlButton";
    return 1;
}

int lua_cocos2dx_extension_ControlSlider_setBackgroundSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_setBackgroundSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Sprite* arg0;

        ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_setBackgroundSprite'", nullptr);
            return 0;
        }
        cobj->setBackgroundSprite(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:setBackgroundSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_setBackgroundSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_getMaximumAllowedValue(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_getMaximumAllowedValue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_getMaximumAllowedValue'", nullptr);
            return 0;
        }
        double ret = cobj->getMaximumAllowedValue();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:getMaximumAllowedValue",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_getMaximumAllowedValue'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_initWithSprites(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_initWithSprites'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 4) {
            cocos2d::Sprite* arg0;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0);

            if (!ok) { break; }
            cocos2d::Sprite* arg1;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 3, "cc.Sprite",&arg1);

            if (!ok) { break; }
            cocos2d::Sprite* arg2;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 4, "cc.Sprite",&arg2);

            if (!ok) { break; }
            cocos2d::Sprite* arg3;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 5, "cc.Sprite",&arg3);

            if (!ok) { break; }
            bool ret = cobj->initWithSprites(arg0, arg1, arg2, arg3);
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
            cocos2d::Sprite* arg1;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 3, "cc.Sprite",&arg1);

            if (!ok) { break; }
            cocos2d::Sprite* arg2;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 4, "cc.Sprite",&arg2);

            if (!ok) { break; }
            bool ret = cobj->initWithSprites(arg0, arg1, arg2);
            tolua_pushboolean(tolua_S,(bool)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.ControlSlider:initWithSprites",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_initWithSprites'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_getMinimumAllowedValue(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_getMinimumAllowedValue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_getMinimumAllowedValue'", nullptr);
            return 0;
        }
        double ret = cobj->getMinimumAllowedValue();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:getMinimumAllowedValue",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_getMinimumAllowedValue'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_getMaximumValue(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_getMaximumValue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_getMaximumValue'", nullptr);
            return 0;
        }
        double ret = cobj->getMaximumValue();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:getMaximumValue",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_getMaximumValue'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_getSelectedThumbSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_getSelectedThumbSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_getSelectedThumbSprite'", nullptr);
            return 0;
        }
        cocos2d::Sprite* ret = cobj->getSelectedThumbSprite();
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:getSelectedThumbSprite",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_getSelectedThumbSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_setProgressSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_setProgressSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Sprite* arg0;

        ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_setProgressSprite'", nullptr);
            return 0;
        }
        cobj->setProgressSprite(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:setProgressSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_setProgressSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_setMaximumValue(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_setMaximumValue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ControlSlider:setMaximumValue");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_setMaximumValue'", nullptr);
            return 0;
        }
        cobj->setMaximumValue(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:setMaximumValue",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_setMaximumValue'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_getMinimumValue(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_getMinimumValue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_getMinimumValue'", nullptr);
            return 0;
        }
        double ret = cobj->getMinimumValue();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:getMinimumValue",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_getMinimumValue'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_setThumbSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_setThumbSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Sprite* arg0;

        ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_setThumbSprite'", nullptr);
            return 0;
        }
        cobj->setThumbSprite(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:setThumbSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_setThumbSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_getValue(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_getValue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_getValue'", nullptr);
            return 0;
        }
        double ret = cobj->getValue();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:getValue",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_getValue'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_getBackgroundSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_getBackgroundSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_getBackgroundSprite'", nullptr);
            return 0;
        }
        cocos2d::Sprite* ret = cobj->getBackgroundSprite();
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:getBackgroundSprite",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_getBackgroundSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_getThumbSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_getThumbSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_getThumbSprite'", nullptr);
            return 0;
        }
        cocos2d::Sprite* ret = cobj->getThumbSprite();
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:getThumbSprite",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_getThumbSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_setValue(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_setValue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ControlSlider:setValue");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_setValue'", nullptr);
            return 0;
        }
        cobj->setValue(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:setValue",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_setValue'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_locationFromTouch(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_locationFromTouch'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Touch* arg0;

        ok &= luaval_to_object<cocos2d::Touch>(tolua_S, 2, "cc.Touch",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_locationFromTouch'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->locationFromTouch(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:locationFromTouch",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_locationFromTouch'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_setMinimumValue(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_setMinimumValue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ControlSlider:setMinimumValue");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_setMinimumValue'", nullptr);
            return 0;
        }
        cobj->setMinimumValue(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:setMinimumValue",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_setMinimumValue'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_setMinimumAllowedValue(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_setMinimumAllowedValue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ControlSlider:setMinimumAllowedValue");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_setMinimumAllowedValue'", nullptr);
            return 0;
        }
        cobj->setMinimumAllowedValue(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:setMinimumAllowedValue",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_setMinimumAllowedValue'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_getProgressSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_getProgressSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_getProgressSprite'", nullptr);
            return 0;
        }
        cocos2d::Sprite* ret = cobj->getProgressSprite();
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:getProgressSprite",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_getProgressSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_setSelectedThumbSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_setSelectedThumbSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Sprite* arg0;

        ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_setSelectedThumbSprite'", nullptr);
            return 0;
        }
        cobj->setSelectedThumbSprite(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:setSelectedThumbSprite",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_setSelectedThumbSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_setMaximumAllowedValue(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ControlSlider*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ControlSlider_setMaximumAllowedValue'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ControlSlider:setMaximumAllowedValue");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_setMaximumAllowedValue'", nullptr);
            return 0;
        }
        cobj->setMaximumAllowedValue(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:setMaximumAllowedValue",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_setMaximumAllowedValue'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ControlSlider_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ControlSlider",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 3)
        {
            cocos2d::Sprite* arg0;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0);
            if (!ok) { break; }
            cocos2d::Sprite* arg1;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 3, "cc.Sprite",&arg1);
            if (!ok) { break; }
            cocos2d::Sprite* arg2;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 4, "cc.Sprite",&arg2);
            if (!ok) { break; }
            cocos2d::extension::ControlSlider* ret = cocos2d::extension::ControlSlider::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::extension::ControlSlider>(tolua_S, "cc.ControlSlider",(cocos2d::extension::ControlSlider*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.ControlSlider:create"); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            const char* arg1;
            std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "cc.ControlSlider:create"); arg1 = arg1_tmp.c_str();
            if (!ok) { break; }
            const char* arg2;
            std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "cc.ControlSlider:create"); arg2 = arg2_tmp.c_str();
            if (!ok) { break; }
            cocos2d::extension::ControlSlider* ret = cocos2d::extension::ControlSlider::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::extension::ControlSlider>(tolua_S, "cc.ControlSlider",(cocos2d::extension::ControlSlider*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.ControlSlider:create"); arg0 = arg0_tmp.c_str();
            if (!ok) { break; }
            const char* arg1;
            std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "cc.ControlSlider:create"); arg1 = arg1_tmp.c_str();
            if (!ok) { break; }
            const char* arg2;
            std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "cc.ControlSlider:create"); arg2 = arg2_tmp.c_str();
            if (!ok) { break; }
            const char* arg3;
            std::string arg3_tmp; ok &= luaval_to_std_string(tolua_S, 5, &arg3_tmp, "cc.ControlSlider:create"); arg3 = arg3_tmp.c_str();
            if (!ok) { break; }
            cocos2d::extension::ControlSlider* ret = cocos2d::extension::ControlSlider::create(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::extension::ControlSlider>(tolua_S, "cc.ControlSlider",(cocos2d::extension::ControlSlider*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            cocos2d::Sprite* arg0;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0);
            if (!ok) { break; }
            cocos2d::Sprite* arg1;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 3, "cc.Sprite",&arg1);
            if (!ok) { break; }
            cocos2d::Sprite* arg2;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 4, "cc.Sprite",&arg2);
            if (!ok) { break; }
            cocos2d::Sprite* arg3;
            ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 5, "cc.Sprite",&arg3);
            if (!ok) { break; }
            cocos2d::extension::ControlSlider* ret = cocos2d::extension::ControlSlider::create(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::extension::ControlSlider>(tolua_S, "cc.ControlSlider",(cocos2d::extension::ControlSlider*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.ControlSlider:create",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_ControlSlider_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ControlSlider* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ControlSlider_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::ControlSlider();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ControlSlider");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ControlSlider:ControlSlider",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ControlSlider_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_ControlSlider_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ControlSlider)");
    return 0;
}

int lua_register_cocos2dx_extension_ControlSlider(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.ControlSlider");
    tolua_cclass(tolua_S,"ControlSlider","cc.ControlSlider","cc.Control",nullptr);

    tolua_beginmodule(tolua_S,"ControlSlider");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_ControlSlider_constructor);
        tolua_function(tolua_S,"setBackgroundSprite",lua_cocos2dx_extension_ControlSlider_setBackgroundSprite);
        tolua_function(tolua_S,"getMaximumAllowedValue",lua_cocos2dx_extension_ControlSlider_getMaximumAllowedValue);
        tolua_function(tolua_S,"initWithSprites",lua_cocos2dx_extension_ControlSlider_initWithSprites);
        tolua_function(tolua_S,"getMinimumAllowedValue",lua_cocos2dx_extension_ControlSlider_getMinimumAllowedValue);
        tolua_function(tolua_S,"getMaximumValue",lua_cocos2dx_extension_ControlSlider_getMaximumValue);
        tolua_function(tolua_S,"getSelectedThumbSprite",lua_cocos2dx_extension_ControlSlider_getSelectedThumbSprite);
        tolua_function(tolua_S,"setProgressSprite",lua_cocos2dx_extension_ControlSlider_setProgressSprite);
        tolua_function(tolua_S,"setMaximumValue",lua_cocos2dx_extension_ControlSlider_setMaximumValue);
        tolua_function(tolua_S,"getMinimumValue",lua_cocos2dx_extension_ControlSlider_getMinimumValue);
        tolua_function(tolua_S,"setThumbSprite",lua_cocos2dx_extension_ControlSlider_setThumbSprite);
        tolua_function(tolua_S,"getValue",lua_cocos2dx_extension_ControlSlider_getValue);
        tolua_function(tolua_S,"getBackgroundSprite",lua_cocos2dx_extension_ControlSlider_getBackgroundSprite);
        tolua_function(tolua_S,"getThumbSprite",lua_cocos2dx_extension_ControlSlider_getThumbSprite);
        tolua_function(tolua_S,"setValue",lua_cocos2dx_extension_ControlSlider_setValue);
        tolua_function(tolua_S,"locationFromTouch",lua_cocos2dx_extension_ControlSlider_locationFromTouch);
        tolua_function(tolua_S,"setMinimumValue",lua_cocos2dx_extension_ControlSlider_setMinimumValue);
        tolua_function(tolua_S,"setMinimumAllowedValue",lua_cocos2dx_extension_ControlSlider_setMinimumAllowedValue);
        tolua_function(tolua_S,"getProgressSprite",lua_cocos2dx_extension_ControlSlider_getProgressSprite);
        tolua_function(tolua_S,"setSelectedThumbSprite",lua_cocos2dx_extension_ControlSlider_setSelectedThumbSprite);
        tolua_function(tolua_S,"setMaximumAllowedValue",lua_cocos2dx_extension_ControlSlider_setMaximumAllowedValue);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_ControlSlider_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::ControlSlider).name();
    g_luaType[typeName] = "cc.ControlSlider";
    g_typeCast["ControlSlider"] = "cc.ControlSlider";
    return 1;
}

int lua_cocos2dx_extension_ScrollView_isClippingToBounds(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_isClippingToBounds'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_isClippingToBounds'", nullptr);
            return 0;
        }
        bool ret = cobj->isClippingToBounds();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:isClippingToBounds",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_isClippingToBounds'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_setContainer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setContainer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Node* arg0;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_setContainer'", nullptr);
            return 0;
        }
        cobj->setContainer(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:setContainer",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setContainer'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_setContentOffsetInDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setContentOffsetInDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Vec2 arg0;
        double arg1;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ScrollView:setContentOffsetInDuration");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ScrollView:setContentOffsetInDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_setContentOffsetInDuration'", nullptr);
            return 0;
        }
        cobj->setContentOffsetInDuration(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:setContentOffsetInDuration",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setContentOffsetInDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_setZoomScaleInDuration(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setZoomScaleInDuration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        double arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ScrollView:setZoomScaleInDuration");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.ScrollView:setZoomScaleInDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_setZoomScaleInDuration'", nullptr);
            return 0;
        }
        cobj->setZoomScaleInDuration(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:setZoomScaleInDuration",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setZoomScaleInDuration'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_updateTweenAction(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_updateTweenAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        std::string arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ScrollView:updateTweenAction");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.ScrollView:updateTweenAction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_updateTweenAction'", nullptr);
            return 0;
        }
        cobj->updateTweenAction(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:updateTweenAction",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_updateTweenAction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_setMaxScale(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setMaxScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ScrollView:setMaxScale");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_setMaxScale'", nullptr);
            return 0;
        }
        cobj->setMaxScale(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:setMaxScale",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setMaxScale'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_hasVisibleParents(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_hasVisibleParents'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_hasVisibleParents'", nullptr);
            return 0;
        }
        bool ret = cobj->hasVisibleParents();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:hasVisibleParents",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_hasVisibleParents'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_getDirection(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getDirection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_getDirection'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getDirection();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:getDirection",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getDirection'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_getContainer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getContainer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_getContainer'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->getContainer();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:getContainer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getContainer'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_setMinScale(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setMinScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ScrollView:setMinScale");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_setMinScale'", nullptr);
            return 0;
        }
        cobj->setMinScale(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:setMinScale",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setMinScale'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_getZoomScale(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getZoomScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_getZoomScale'", nullptr);
            return 0;
        }
        double ret = cobj->getZoomScale();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:getZoomScale",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getZoomScale'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_updateInset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_updateInset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_updateInset'", nullptr);
            return 0;
        }
        cobj->updateInset();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:updateInset",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_updateInset'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_initWithViewSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_initWithViewSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Size arg0;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.ScrollView:initWithViewSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_initWithViewSize'", nullptr);
            return 0;
        }
        bool ret = cobj->initWithViewSize(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::Size arg0;
        cocos2d::Node* arg1;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.ScrollView:initWithViewSize");

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_initWithViewSize'", nullptr);
            return 0;
        }
        bool ret = cobj->initWithViewSize(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:initWithViewSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_initWithViewSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_pause(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_pause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_pause'", nullptr);
            return 0;
        }
        cobj->pause(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:pause",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_pause'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_setDirection(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setDirection'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::ScrollView::Direction arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ScrollView:setDirection");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_setDirection'", nullptr);
            return 0;
        }
        cobj->setDirection(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:setDirection",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setDirection'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_setContentOffset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setContentOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ScrollView:setContentOffset");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_setContentOffset'", nullptr);
            return 0;
        }
        cobj->setContentOffset(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::Vec2 arg0;
        bool arg1;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.ScrollView:setContentOffset");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.ScrollView:setContentOffset");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_setContentOffset'", nullptr);
            return 0;
        }
        cobj->setContentOffset(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:setContentOffset",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setContentOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_isDragging(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_isDragging'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_isDragging'", nullptr);
            return 0;
        }
        bool ret = cobj->isDragging();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:isDragging",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_isDragging'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_isTouchEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_isTouchEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_isTouchEnabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isTouchEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:isTouchEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_isTouchEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_isBounceable(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_isBounceable'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_isBounceable'", nullptr);
            return 0;
        }
        bool ret = cobj->isBounceable();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:isBounceable",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_isBounceable'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_setTouchEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setTouchEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.ScrollView:setTouchEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_setTouchEnabled'", nullptr);
            return 0;
        }
        cobj->setTouchEnabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:setTouchEnabled",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setTouchEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_getContentOffset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getContentOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_getContentOffset'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getContentOffset();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:getContentOffset",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getContentOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_resume(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_resume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_resume'", nullptr);
            return 0;
        }
        cobj->resume(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:resume",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_resume'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_setClippingToBounds(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setClippingToBounds'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.ScrollView:setClippingToBounds");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_setClippingToBounds'", nullptr);
            return 0;
        }
        cobj->setClippingToBounds(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:setClippingToBounds",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setClippingToBounds'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_setViewSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setViewSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Size arg0;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.ScrollView:setViewSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_setViewSize'", nullptr);
            return 0;
        }
        cobj->setViewSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:setViewSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setViewSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_getViewSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_getViewSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_getViewSize'", nullptr);
            return 0;
        }
        cocos2d::Size ret = cobj->getViewSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:getViewSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_getViewSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_maxContainerOffset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_maxContainerOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_maxContainerOffset'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->maxContainerOffset();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:maxContainerOffset",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_maxContainerOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_setBounceable(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setBounceable'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.ScrollView:setBounceable");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_setBounceable'", nullptr);
            return 0;
        }
        cobj->setBounceable(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:setBounceable",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setBounceable'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_isTouchMoved(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_isTouchMoved'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_isTouchMoved'", nullptr);
            return 0;
        }
        bool ret = cobj->isTouchMoved();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:isTouchMoved",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_isTouchMoved'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_isNodeVisible(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_isNodeVisible'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Node* arg0;

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_isNodeVisible'", nullptr);
            return 0;
        }
        bool ret = cobj->isNodeVisible(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:isNodeVisible",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_isNodeVisible'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_minContainerOffset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_minContainerOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_minContainerOffset'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->minContainerOffset();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:minContainerOffset",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_minContainerOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_setZoomScale(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::extension::ScrollView*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ScrollView_setZoomScale'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ScrollView:setZoomScale");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.ScrollView:setZoomScale");

            if (!ok) { break; }
            cobj->setZoomScale(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ScrollView:setZoomScale");

            if (!ok) { break; }
            cobj->setZoomScale(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.ScrollView:setZoomScale",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_setZoomScale'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_ScrollView_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 0)
        {
            cocos2d::extension::ScrollView* ret = cocos2d::extension::ScrollView::create();
            object_to_luaval<cocos2d::extension::ScrollView>(tolua_S, "cc.ScrollView",(cocos2d::extension::ScrollView*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.ScrollView:create");
            if (!ok) { break; }
            cocos2d::extension::ScrollView* ret = cocos2d::extension::ScrollView::create(arg0);
            object_to_luaval<cocos2d::extension::ScrollView>(tolua_S, "cc.ScrollView",(cocos2d::extension::ScrollView*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            cocos2d::Size arg0;
            ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.ScrollView:create");
            if (!ok) { break; }
            cocos2d::Node* arg1;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);
            if (!ok) { break; }
            cocos2d::extension::ScrollView* ret = cocos2d::extension::ScrollView::create(arg0, arg1);
            object_to_luaval<cocos2d::extension::ScrollView>(tolua_S, "cc.ScrollView",(cocos2d::extension::ScrollView*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.ScrollView:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_ScrollView_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::ScrollView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ScrollView_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::ScrollView();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.ScrollView");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ScrollView:ScrollView",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ScrollView_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_ScrollView_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ScrollView)");
    return 0;
}

int lua_register_cocos2dx_extension_ScrollView(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.ScrollView");
    tolua_cclass(tolua_S,"ScrollView","cc.ScrollView","cc.Layer",nullptr);

    tolua_beginmodule(tolua_S,"ScrollView");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_ScrollView_constructor);
        tolua_function(tolua_S,"isClippingToBounds",lua_cocos2dx_extension_ScrollView_isClippingToBounds);
        tolua_function(tolua_S,"setContainer",lua_cocos2dx_extension_ScrollView_setContainer);
        tolua_function(tolua_S,"setContentOffsetInDuration",lua_cocos2dx_extension_ScrollView_setContentOffsetInDuration);
        tolua_function(tolua_S,"setZoomScaleInDuration",lua_cocos2dx_extension_ScrollView_setZoomScaleInDuration);
        tolua_function(tolua_S,"updateTweenAction",lua_cocos2dx_extension_ScrollView_updateTweenAction);
        tolua_function(tolua_S,"setMaxScale",lua_cocos2dx_extension_ScrollView_setMaxScale);
        tolua_function(tolua_S,"hasVisibleParents",lua_cocos2dx_extension_ScrollView_hasVisibleParents);
        tolua_function(tolua_S,"getDirection",lua_cocos2dx_extension_ScrollView_getDirection);
        tolua_function(tolua_S,"getContainer",lua_cocos2dx_extension_ScrollView_getContainer);
        tolua_function(tolua_S,"setMinScale",lua_cocos2dx_extension_ScrollView_setMinScale);
        tolua_function(tolua_S,"getZoomScale",lua_cocos2dx_extension_ScrollView_getZoomScale);
        tolua_function(tolua_S,"updateInset",lua_cocos2dx_extension_ScrollView_updateInset);
        tolua_function(tolua_S,"initWithViewSize",lua_cocos2dx_extension_ScrollView_initWithViewSize);
        tolua_function(tolua_S,"pause",lua_cocos2dx_extension_ScrollView_pause);
        tolua_function(tolua_S,"setDirection",lua_cocos2dx_extension_ScrollView_setDirection);
        tolua_function(tolua_S,"init",lua_cocos2dx_extension_ScrollView_init);
        tolua_function(tolua_S,"setContentOffset",lua_cocos2dx_extension_ScrollView_setContentOffset);
        tolua_function(tolua_S,"isDragging",lua_cocos2dx_extension_ScrollView_isDragging);
        tolua_function(tolua_S,"isTouchEnabled",lua_cocos2dx_extension_ScrollView_isTouchEnabled);
        tolua_function(tolua_S,"isBounceable",lua_cocos2dx_extension_ScrollView_isBounceable);
        tolua_function(tolua_S,"setTouchEnabled",lua_cocos2dx_extension_ScrollView_setTouchEnabled);
        tolua_function(tolua_S,"getContentOffset",lua_cocos2dx_extension_ScrollView_getContentOffset);
        tolua_function(tolua_S,"resume",lua_cocos2dx_extension_ScrollView_resume);
        tolua_function(tolua_S,"setClippingToBounds",lua_cocos2dx_extension_ScrollView_setClippingToBounds);
        tolua_function(tolua_S,"setViewSize",lua_cocos2dx_extension_ScrollView_setViewSize);
        tolua_function(tolua_S,"getViewSize",lua_cocos2dx_extension_ScrollView_getViewSize);
        tolua_function(tolua_S,"maxContainerOffset",lua_cocos2dx_extension_ScrollView_maxContainerOffset);
        tolua_function(tolua_S,"setBounceable",lua_cocos2dx_extension_ScrollView_setBounceable);
        tolua_function(tolua_S,"isTouchMoved",lua_cocos2dx_extension_ScrollView_isTouchMoved);
        tolua_function(tolua_S,"isNodeVisible",lua_cocos2dx_extension_ScrollView_isNodeVisible);
        tolua_function(tolua_S,"minContainerOffset",lua_cocos2dx_extension_ScrollView_minContainerOffset);
        tolua_function(tolua_S,"setZoomScale",lua_cocos2dx_extension_ScrollView_setZoomScale);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_ScrollView_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::ScrollView).name();
    g_luaType[typeName] = "cc.ScrollView";
    g_typeCast["ScrollView"] = "cc.ScrollView";
    return 1;
}

int lua_cocos2dx_extension_TableViewCell_reset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableViewCell* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TableViewCell",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TableViewCell*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableViewCell_reset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableViewCell_reset'", nullptr);
            return 0;
        }
        cobj->reset();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableViewCell:reset",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_reset'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_TableViewCell_getIdx(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableViewCell* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TableViewCell",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TableViewCell*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableViewCell_getIdx'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableViewCell_getIdx'", nullptr);
            return 0;
        }
        ssize_t ret = cobj->getIdx();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableViewCell:getIdx",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_getIdx'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_TableViewCell_setIdx(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableViewCell* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TableViewCell",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TableViewCell*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableViewCell_setIdx'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ssize_t arg0;

        ok &= luaval_to_ssize(tolua_S, 2, &arg0, "cc.TableViewCell:setIdx");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableViewCell_setIdx'", nullptr);
            return 0;
        }
        cobj->setIdx(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableViewCell:setIdx",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_setIdx'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_TableViewCell_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.TableViewCell",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableViewCell_create'", nullptr);
            return 0;
        }
        cocos2d::extension::TableViewCell* ret = cocos2d::extension::TableViewCell::create();
        object_to_luaval<cocos2d::extension::TableViewCell>(tolua_S, "cc.TableViewCell",(cocos2d::extension::TableViewCell*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.TableViewCell:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_TableViewCell_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableViewCell* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableViewCell_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::TableViewCell();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TableViewCell");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableViewCell:TableViewCell",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableViewCell_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_TableViewCell_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (TableViewCell)");
    return 0;
}

int lua_register_cocos2dx_extension_TableViewCell(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.TableViewCell");
    tolua_cclass(tolua_S,"TableViewCell","cc.TableViewCell","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"TableViewCell");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_TableViewCell_constructor);
        tolua_function(tolua_S,"reset",lua_cocos2dx_extension_TableViewCell_reset);
        tolua_function(tolua_S,"getIdx",lua_cocos2dx_extension_TableViewCell_getIdx);
        tolua_function(tolua_S,"setIdx",lua_cocos2dx_extension_TableViewCell_setIdx);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_TableViewCell_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::TableViewCell).name();
    g_luaType[typeName] = "cc.TableViewCell";
    g_typeCast["TableViewCell"] = "cc.TableViewCell";
    return 1;
}

int lua_cocos2dx_extension_TableView_updateCellAtIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_updateCellAtIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ssize_t arg0;

        ok &= luaval_to_ssize(tolua_S, 2, &arg0, "cc.TableView:updateCellAtIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableView_updateCellAtIndex'", nullptr);
            return 0;
        }
        cobj->updateCellAtIndex(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableView:updateCellAtIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_updateCellAtIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_TableView_setVerticalFillOrder(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_setVerticalFillOrder'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::TableView::VerticalFillOrder arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.TableView:setVerticalFillOrder");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableView_setVerticalFillOrder'", nullptr);
            return 0;
        }
        cobj->setVerticalFillOrder(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableView:setVerticalFillOrder",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_setVerticalFillOrder'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_TableView_scrollViewDidZoom(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_scrollViewDidZoom'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::ScrollView* arg0;

        ok &= luaval_to_object<cocos2d::extension::ScrollView>(tolua_S, 2, "cc.ScrollView",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableView_scrollViewDidZoom'", nullptr);
            return 0;
        }
        cobj->scrollViewDidZoom(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableView:scrollViewDidZoom",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_scrollViewDidZoom'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_TableView__updateContentSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView__updateContentSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableView__updateContentSize'", nullptr);
            return 0;
        }
        cobj->_updateContentSize();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableView:_updateContentSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView__updateContentSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_TableView_getVerticalFillOrder(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_getVerticalFillOrder'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableView_getVerticalFillOrder'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getVerticalFillOrder();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableView:getVerticalFillOrder",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_getVerticalFillOrder'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_TableView_removeCellAtIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_removeCellAtIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ssize_t arg0;

        ok &= luaval_to_ssize(tolua_S, 2, &arg0, "cc.TableView:removeCellAtIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableView_removeCellAtIndex'", nullptr);
            return 0;
        }
        cobj->removeCellAtIndex(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableView:removeCellAtIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_removeCellAtIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_TableView_initWithViewSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_initWithViewSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Size arg0;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.TableView:initWithViewSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableView_initWithViewSize'", nullptr);
            return 0;
        }
        bool ret = cobj->initWithViewSize(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::Size arg0;
        cocos2d::Node* arg1;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.TableView:initWithViewSize");

        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 3, "cc.Node",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableView_initWithViewSize'", nullptr);
            return 0;
        }
        bool ret = cobj->initWithViewSize(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableView:initWithViewSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_initWithViewSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_TableView_scrollViewDidScroll(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_scrollViewDidScroll'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::extension::ScrollView* arg0;

        ok &= luaval_to_object<cocos2d::extension::ScrollView>(tolua_S, 2, "cc.ScrollView",&arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableView_scrollViewDidScroll'", nullptr);
            return 0;
        }
        cobj->scrollViewDidScroll(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableView:scrollViewDidScroll",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_scrollViewDidScroll'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_TableView_reloadData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_reloadData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableView_reloadData'", nullptr);
            return 0;
        }
        cobj->reloadData();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableView:reloadData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_reloadData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_TableView_insertCellAtIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_insertCellAtIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ssize_t arg0;

        ok &= luaval_to_ssize(tolua_S, 2, &arg0, "cc.TableView:insertCellAtIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableView_insertCellAtIndex'", nullptr);
            return 0;
        }
        cobj->insertCellAtIndex(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableView:insertCellAtIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_insertCellAtIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_TableView_cellAtIndex(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_cellAtIndex'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ssize_t arg0;

        ok &= luaval_to_ssize(tolua_S, 2, &arg0, "cc.TableView:cellAtIndex");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableView_cellAtIndex'", nullptr);
            return 0;
        }
        cocos2d::extension::TableViewCell* ret = cobj->cellAtIndex(arg0);
        object_to_luaval<cocos2d::extension::TableViewCell>(tolua_S, "cc.TableViewCell",(cocos2d::extension::TableViewCell*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableView:cellAtIndex",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_cellAtIndex'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_TableView_dequeueCell(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::TableView*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_TableView_dequeueCell'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableView_dequeueCell'", nullptr);
            return 0;
        }
        cocos2d::extension::TableViewCell* ret = cobj->dequeueCell();
        object_to_luaval<cocos2d::extension::TableViewCell>(tolua_S, "cc.TableViewCell",(cocos2d::extension::TableViewCell*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableView:dequeueCell",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_dequeueCell'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_TableView_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::TableView* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_TableView_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::TableView();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.TableView");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.TableView:TableView",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_TableView_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_TableView_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (TableView)");
    return 0;
}

int lua_register_cocos2dx_extension_TableView(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.TableView");
    tolua_cclass(tolua_S,"TableView","cc.TableView","cc.ScrollView",nullptr);

    tolua_beginmodule(tolua_S,"TableView");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_TableView_constructor);
        tolua_function(tolua_S,"updateCellAtIndex",lua_cocos2dx_extension_TableView_updateCellAtIndex);
        tolua_function(tolua_S,"setVerticalFillOrder",lua_cocos2dx_extension_TableView_setVerticalFillOrder);
        tolua_function(tolua_S,"scrollViewDidZoom",lua_cocos2dx_extension_TableView_scrollViewDidZoom);
        tolua_function(tolua_S,"_updateContentSize",lua_cocos2dx_extension_TableView__updateContentSize);
        tolua_function(tolua_S,"getVerticalFillOrder",lua_cocos2dx_extension_TableView_getVerticalFillOrder);
        tolua_function(tolua_S,"removeCellAtIndex",lua_cocos2dx_extension_TableView_removeCellAtIndex);
        tolua_function(tolua_S,"initWithViewSize",lua_cocos2dx_extension_TableView_initWithViewSize);
        tolua_function(tolua_S,"scrollViewDidScroll",lua_cocos2dx_extension_TableView_scrollViewDidScroll);
        tolua_function(tolua_S,"reloadData",lua_cocos2dx_extension_TableView_reloadData);
        tolua_function(tolua_S,"insertCellAtIndex",lua_cocos2dx_extension_TableView_insertCellAtIndex);
        tolua_function(tolua_S,"cellAtIndex",lua_cocos2dx_extension_TableView_cellAtIndex);
        tolua_function(tolua_S,"dequeueCell",lua_cocos2dx_extension_TableView_dequeueCell);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::TableView).name();
    g_luaType[typeName] = "cc.TableView";
    g_typeCast["TableView"] = "cc.TableView";
    return 1;
}

int lua_cocos2dx_extension_AssetsManager_setStoragePath(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManager_setStoragePath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:setStoragePath"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_setStoragePath'", nullptr);
            return 0;
        }
        cobj->setStoragePath(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:setStoragePath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManager_setStoragePath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManager_setNeedRemovePath(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManager_setNeedRemovePath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:setNeedRemovePath"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_setNeedRemovePath'", nullptr);
            return 0;
        }
        cobj->setNeedRemovePath(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:setNeedRemovePath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManager_setNeedRemovePath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManager_setPackageUrl(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManager_setPackageUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:setPackageUrl"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_setPackageUrl'", nullptr);
            return 0;
        }
        cobj->setPackageUrl(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:setPackageUrl",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManager_setPackageUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManager_checkUpdate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManager_checkUpdate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_checkUpdate'", nullptr);
            return 0;
        }
        bool ret = cobj->checkUpdate();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:checkUpdate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManager_checkUpdate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManager_getStoragePath(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManager_getStoragePath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_getStoragePath'", nullptr);
            return 0;
        }
        const char* ret = cobj->getStoragePath();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:getStoragePath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManager_getStoragePath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManager_update(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManager_update'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_update'", nullptr);
            return 0;
        }
        cobj->update();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:update",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManager_update'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManager_setConnectionTimeout(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManager_setConnectionTimeout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "cc.AssetsManager:setConnectionTimeout");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_setConnectionTimeout'", nullptr);
            return 0;
        }
        cobj->setConnectionTimeout(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:setConnectionTimeout",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManager_setConnectionTimeout'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManager_setVersionFileUrl(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManager_setVersionFileUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:setVersionFileUrl"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_setVersionFileUrl'", nullptr);
            return 0;
        }
        cobj->setVersionFileUrl(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:setVersionFileUrl",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManager_setVersionFileUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManager_getPackageUrl(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManager_getPackageUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_getPackageUrl'", nullptr);
            return 0;
        }
        const char* ret = cobj->getPackageUrl();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:getPackageUrl",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManager_getPackageUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManager_getConnectionTimeout(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManager_getConnectionTimeout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_getConnectionTimeout'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getConnectionTimeout();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:getConnectionTimeout",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManager_getConnectionTimeout'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManager_getVersion(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManager_getVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_getVersion'", nullptr);
            return 0;
        }
        std::string ret = cobj->getVersion();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:getVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManager_getVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManager_getVersionFileUrl(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManager_getVersionFileUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_getVersionFileUrl'", nullptr);
            return 0;
        }
        const char* ret = cobj->getVersionFileUrl();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:getVersionFileUrl",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManager_getVersionFileUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManager_deleteVersion(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManager_deleteVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_deleteVersion'", nullptr);
            return 0;
        }
        cobj->deleteVersion();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:deleteVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManager_deleteVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManager_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 6)
    {
        const char* arg0;
        const char* arg1;
        const char* arg2;
        std::function<void (int)> arg3;
        std::function<void (int)> arg4;
        std::function<void ()> arg5;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:create"); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "cc.AssetsManager:create"); arg1 = arg1_tmp.c_str();
        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "cc.AssetsManager:create"); arg2 = arg2_tmp.c_str();
        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_create'", nullptr);
            return 0;
        }
        cocos2d::extension::AssetsManager* ret = cocos2d::extension::AssetsManager::create(arg0, arg1, arg2, arg3, arg4, arg5);
        object_to_luaval<cocos2d::extension::AssetsManager>(tolua_S, "cc.AssetsManager",(cocos2d::extension::AssetsManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.AssetsManager:create",argc, 6);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManager_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extension_AssetsManager_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::AssetsManager();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AssetsManager");
        return 1;
    }
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:AssetsManager"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::AssetsManager(arg0);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AssetsManager");
        return 1;
    }
    if (argc == 2) 
    {
        const char* arg0;
        const char* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:AssetsManager"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "cc.AssetsManager:AssetsManager"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::AssetsManager(arg0, arg1);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AssetsManager");
        return 1;
    }
    if (argc == 3) 
    {
        const char* arg0;
        const char* arg1;
        const char* arg2;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.AssetsManager:AssetsManager"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "cc.AssetsManager:AssetsManager"); arg1 = arg1_tmp.c_str();

        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "cc.AssetsManager:AssetsManager"); arg2 = arg2_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManager_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::extension::AssetsManager(arg0, arg1, arg2);
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.AssetsManager");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManager:AssetsManager",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManager_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_extension_AssetsManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AssetsManager)");
    return 0;
}

int lua_register_cocos2dx_extension_AssetsManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.AssetsManager");
    tolua_cclass(tolua_S,"AssetsManager","cc.AssetsManager","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"AssetsManager");
        tolua_function(tolua_S,"new",lua_cocos2dx_extension_AssetsManager_constructor);
        tolua_function(tolua_S,"setStoragePath",lua_cocos2dx_extension_AssetsManager_setStoragePath);
        tolua_function(tolua_S,"setNeedRemovePath",lua_cocos2dx_extension_AssetsManager_setNeedRemovePath);
        tolua_function(tolua_S,"setPackageUrl",lua_cocos2dx_extension_AssetsManager_setPackageUrl);
        tolua_function(tolua_S,"checkUpdate",lua_cocos2dx_extension_AssetsManager_checkUpdate);
        tolua_function(tolua_S,"getStoragePath",lua_cocos2dx_extension_AssetsManager_getStoragePath);
        tolua_function(tolua_S,"update",lua_cocos2dx_extension_AssetsManager_update);
        tolua_function(tolua_S,"setConnectionTimeout",lua_cocos2dx_extension_AssetsManager_setConnectionTimeout);
        tolua_function(tolua_S,"setVersionFileUrl",lua_cocos2dx_extension_AssetsManager_setVersionFileUrl);
        tolua_function(tolua_S,"getPackageUrl",lua_cocos2dx_extension_AssetsManager_getPackageUrl);
        tolua_function(tolua_S,"getConnectionTimeout",lua_cocos2dx_extension_AssetsManager_getConnectionTimeout);
        tolua_function(tolua_S,"getVersion",lua_cocos2dx_extension_AssetsManager_getVersion);
        tolua_function(tolua_S,"getVersionFileUrl",lua_cocos2dx_extension_AssetsManager_getVersionFileUrl);
        tolua_function(tolua_S,"deleteVersion",lua_cocos2dx_extension_AssetsManager_deleteVersion);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_AssetsManager_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::AssetsManager).name();
    g_luaType[typeName] = "cc.AssetsManager";
    g_typeCast["AssetsManager"] = "cc.AssetsManager";
    return 1;
}

int lua_cocos2dx_extension_AssetsManagerEx_getState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManagerEx_getState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManagerEx_getState'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getState();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:getState",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManagerEx_getState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManagerEx_checkUpdate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManagerEx_checkUpdate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManagerEx_checkUpdate'", nullptr);
            return 0;
        }
        cobj->checkUpdate();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:checkUpdate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManagerEx_checkUpdate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManagerEx_getStoragePath(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManagerEx_getStoragePath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManagerEx_getStoragePath'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getStoragePath();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:getStoragePath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManagerEx_getStoragePath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManagerEx_update(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManagerEx_update'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManagerEx_update'", nullptr);
            return 0;
        }
        cobj->update();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:update",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManagerEx_update'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManagerEx_getLocalManifest(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManagerEx_getLocalManifest'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManagerEx_getLocalManifest'", nullptr);
            return 0;
        }
        const cocos2d::extension::Manifest* ret = cobj->getLocalManifest();
        object_to_luaval<cocos2d::extension::Manifest>(tolua_S, "cc.Manifest",(cocos2d::extension::Manifest*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:getLocalManifest",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManagerEx_getLocalManifest'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManagerEx_getRemoteManifest(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManagerEx_getRemoteManifest'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManagerEx_getRemoteManifest'", nullptr);
            return 0;
        }
        const cocos2d::extension::Manifest* ret = cobj->getRemoteManifest();
        object_to_luaval<cocos2d::extension::Manifest>(tolua_S, "cc.Manifest",(cocos2d::extension::Manifest*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:getRemoteManifest",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManagerEx_getRemoteManifest'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManagerEx_downloadFailedAssets(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::AssetsManagerEx* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extension::AssetsManagerEx*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_AssetsManagerEx_downloadFailedAssets'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManagerEx_downloadFailedAssets'", nullptr);
            return 0;
        }
        cobj->downloadFailedAssets();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AssetsManagerEx:downloadFailedAssets",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManagerEx_downloadFailedAssets'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extension_AssetsManagerEx_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.AssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.AssetsManagerEx:create");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.AssetsManagerEx:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_AssetsManagerEx_create'", nullptr);
            return 0;
        }
        cocos2d::extension::AssetsManagerEx* ret = cocos2d::extension::AssetsManagerEx::create(arg0, arg1);
        object_to_luaval<cocos2d::extension::AssetsManagerEx>(tolua_S, "cc.AssetsManagerEx",(cocos2d::extension::AssetsManagerEx*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.AssetsManagerEx:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_AssetsManagerEx_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_extension_AssetsManagerEx_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AssetsManagerEx)");
    return 0;
}

int lua_register_cocos2dx_extension_AssetsManagerEx(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.AssetsManagerEx");
    tolua_cclass(tolua_S,"AssetsManagerEx","cc.AssetsManagerEx","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"AssetsManagerEx");
        tolua_function(tolua_S,"getState",lua_cocos2dx_extension_AssetsManagerEx_getState);
        tolua_function(tolua_S,"checkUpdate",lua_cocos2dx_extension_AssetsManagerEx_checkUpdate);
        tolua_function(tolua_S,"getStoragePath",lua_cocos2dx_extension_AssetsManagerEx_getStoragePath);
        tolua_function(tolua_S,"update",lua_cocos2dx_extension_AssetsManagerEx_update);
        tolua_function(tolua_S,"getLocalManifest",lua_cocos2dx_extension_AssetsManagerEx_getLocalManifest);
        tolua_function(tolua_S,"getRemoteManifest",lua_cocos2dx_extension_AssetsManagerEx_getRemoteManifest);
        tolua_function(tolua_S,"downloadFailedAssets",lua_cocos2dx_extension_AssetsManagerEx_downloadFailedAssets);
        tolua_function(tolua_S,"create", lua_cocos2dx_extension_AssetsManagerEx_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extension::AssetsManagerEx).name();
    g_luaType[typeName] = "cc.AssetsManagerEx";
    g_typeCast["AssetsManagerEx"] = "cc.AssetsManagerEx";
    return 1;
}
TOLUA_API int register_all_cocos2dx_extension(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_extension_Control(tolua_S);
	lua_register_cocos2dx_extension_AssetsManager(tolua_S);
	lua_register_cocos2dx_extension_ScrollView(tolua_S);
	lua_register_cocos2dx_extension_TableView(tolua_S);
	lua_register_cocos2dx_extension_ControlSlider(tolua_S);
	lua_register_cocos2dx_extension_AssetsManagerEx(tolua_S);
	lua_register_cocos2dx_extension_TableViewCell(tolua_S);
	lua_register_cocos2dx_extension_ControlButton(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

