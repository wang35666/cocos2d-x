#include "scripting/lua-bindings/auto/lua_cocos2dx_l3d_auto.hpp"
#include "cocos2d.h"
#include "3d/CCBundle3D.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

int lua_cocos2dx_l3d_LSprite3D_setTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LSprite3D* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LSprite3D",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::LSprite3D*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_l3d_LSprite3D_setTexture'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            cocos2d::Texture2D* arg0;
            ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.LSprite3D:setTexture");

            if (!ok) { break; }
            cobj->setTexture(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LSprite3D:setTexture");

            if (!ok) { break; }
            cobj->setTexture(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.LSprite3D:setTexture",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_l3d_LSprite3D_setTexture'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_l3d_LSprite3D_initWithFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LSprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LSprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LSprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_l3d_LSprite3D_initWithFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LSprite3D:initWithFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_l3d_LSprite3D_initWithFile'", nullptr);
            return 0;
        }
        bool ret = cobj->initWithFile(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LSprite3D:initWithFile",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_l3d_LSprite3D_initWithFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_l3d_LSprite3D_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LSprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LSprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LSprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_l3d_LSprite3D_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.LSprite3D:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_l3d_LSprite3D_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LSprite3D:setBlendFunc",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_l3d_LSprite3D_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_l3d_LSprite3D_onDraw(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LSprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LSprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LSprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_l3d_LSprite3D_onDraw'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Mat4 arg0;
        unsigned int arg1;

        ok &= luaval_to_mat4(tolua_S, 2, &arg0, "cc.LSprite3D:onDraw");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "cc.LSprite3D:onDraw");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_l3d_LSprite3D_onDraw'", nullptr);
            return 0;
        }
        cobj->onDraw(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LSprite3D:onDraw",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_l3d_LSprite3D_onDraw'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_l3d_LSprite3D_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LSprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LSprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::LSprite3D*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_l3d_LSprite3D_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_l3d_LSprite3D_getBlendFunc'", nullptr);
            return 0;
        }
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LSprite3D:getBlendFunc",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_l3d_LSprite3D_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_l3d_LSprite3D_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.LSprite3D",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LSprite3D:create");
            if (!ok) { break; }
            cocos2d::LSprite3D* ret = cocos2d::LSprite3D::create(arg0);
            object_to_luaval<cocos2d::LSprite3D>(tolua_S, "cc.LSprite3D",(cocos2d::LSprite3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::LSprite3D* ret = cocos2d::LSprite3D::create();
            object_to_luaval<cocos2d::LSprite3D>(tolua_S, "cc.LSprite3D",(cocos2d::LSprite3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LSprite3D:create");
            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.LSprite3D:create");
            if (!ok) { break; }
            cocos2d::LSprite3D* ret = cocos2d::LSprite3D::create(arg0, arg1);
            object_to_luaval<cocos2d::LSprite3D>(tolua_S, "cc.LSprite3D",(cocos2d::LSprite3D*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.LSprite3D:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_l3d_LSprite3D_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_l3d_LSprite3D_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LSprite3D* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_l3d_LSprite3D_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::LSprite3D();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.LSprite3D");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LSprite3D:LSprite3D",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_l3d_LSprite3D_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_l3d_LSprite3D_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (LSprite3D)");
    return 0;
}

int lua_register_cocos2dx_l3d_LSprite3D(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.LSprite3D");
    tolua_cclass(tolua_S,"LSprite3D","cc.LSprite3D","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"LSprite3D");
        tolua_function(tolua_S,"new",lua_cocos2dx_l3d_LSprite3D_constructor);
        tolua_function(tolua_S,"setTexture",lua_cocos2dx_l3d_LSprite3D_setTexture);
        tolua_function(tolua_S,"initWithFile",lua_cocos2dx_l3d_LSprite3D_initWithFile);
        tolua_function(tolua_S,"setBlendFunc",lua_cocos2dx_l3d_LSprite3D_setBlendFunc);
        tolua_function(tolua_S,"onDraw",lua_cocos2dx_l3d_LSprite3D_onDraw);
        tolua_function(tolua_S,"getBlendFunc",lua_cocos2dx_l3d_LSprite3D_getBlendFunc);
        tolua_function(tolua_S,"create", lua_cocos2dx_l3d_LSprite3D_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::LSprite3D).name();
    g_luaType[typeName] = "cc.LSprite3D";
    g_typeCast["LSprite3D"] = "cc.LSprite3D";
    return 1;
}
TOLUA_API int register_all_cocos2dx_l3d(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_l3d_LSprite3D(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

