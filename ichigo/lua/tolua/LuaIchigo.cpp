/*
** Lua binding: ichigo
** Generated automatically by tolua++-1.0.92 on Tue Jan 31 20:44:16 2012.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_ichigo_open (lua_State* tolua_S);

#include "LuaIchigo.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_ichigo__Director (lua_State* tolua_S)
{
 ichigo::Director* self = (ichigo::Director*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_ichigo__Character (lua_State* tolua_S)
{
 ichigo::Character* self = (ichigo::Character*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"ichigo::Character");
 tolua_usertype(tolua_S,"ichigo::Agent");
 tolua_usertype(tolua_S,"ichigo::Actor");
 tolua_usertype(tolua_S,"ichigo::Director");
}

/* method: delete of class  ichigo::Director */
#ifndef TOLUA_DISABLE_tolua_ichigo_ichigo_Director_delete00
static int tolua_ichigo_ichigo_Director_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ichigo::Director",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ichigo::Director* self = (ichigo::Director*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  ichigo::Director */
#ifndef TOLUA_DISABLE_tolua_ichigo_ichigo_Director_getInstance00
static int tolua_ichigo_ichigo_Director_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ichigo::Director",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ichigo::Director* tolua_ret = (ichigo::Director*)  ichigo::Director::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ichigo::Director");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ichigo::Character */
#ifndef TOLUA_DISABLE_tolua_ichigo_ichigo_Character_new00
static int tolua_ichigo_ichigo_Character_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ichigo::Character",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ichigo::Character* tolua_ret = (ichigo::Character*)  Mtolua_new((ichigo::Character)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ichigo::Character");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ichigo::Character */
#ifndef TOLUA_DISABLE_tolua_ichigo_ichigo_Character_new00_local
static int tolua_ichigo_ichigo_Character_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ichigo::Character",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ichigo::Character* tolua_ret = (ichigo::Character*)  Mtolua_new((ichigo::Character)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ichigo::Character");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ichigo::Character */
#ifndef TOLUA_DISABLE_tolua_ichigo_ichigo_Character_delete00
static int tolua_ichigo_ichigo_Character_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ichigo::Character",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ichigo::Character* self = (ichigo::Character*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: say of class  ichigo::Character */
#ifndef TOLUA_DISABLE_tolua_ichigo_ichigo_Character_say00
static int tolua_ichigo_ichigo_Character_say00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ichigo::Character",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ichigo::Character* self = (ichigo::Character*)  tolua_tousertype(tolua_S,1,0);
  std::string text = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'say'", NULL);
#endif
  {
   self->say(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'say'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: findByName of class  ichigo::Agent */
#ifndef TOLUA_DISABLE_tolua_ichigo_ichigo_Agent_findByName00
static int tolua_ichigo_ichigo_Agent_findByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ichigo::Agent",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ichigo::Agent* self = (ichigo::Agent*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'findByName'", NULL);
#endif
  {
   ichigo::Agent* tolua_ret = (ichigo::Agent*)  self->findByName(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ichigo::Agent");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'findByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  ichigo::Agent */
#ifndef TOLUA_DISABLE_tolua_ichigo_ichigo_Agent_getName00
static int tolua_ichigo_ichigo_Agent_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ichigo::Agent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ichigo::Agent* self = (ichigo::Agent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_ichigo_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"ichigo",0);
  tolua_beginmodule(tolua_S,"ichigo");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Director","ichigo::Director","ichigo::Agent",tolua_collect_ichigo__Director);
   #else
   tolua_cclass(tolua_S,"Director","ichigo::Director","ichigo::Agent",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Director");
    tolua_function(tolua_S,"delete",tolua_ichigo_ichigo_Director_delete00);
    tolua_function(tolua_S,"getInstance",tolua_ichigo_ichigo_Director_getInstance00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"ichigo",0);
  tolua_beginmodule(tolua_S,"ichigo");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Character","ichigo::Character","ichigo::Actor",tolua_collect_ichigo__Character);
   #else
   tolua_cclass(tolua_S,"Character","ichigo::Character","ichigo::Actor",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Character");
    tolua_function(tolua_S,"new",tolua_ichigo_ichigo_Character_new00);
    tolua_function(tolua_S,"new_local",tolua_ichigo_ichigo_Character_new00_local);
    tolua_function(tolua_S,".call",tolua_ichigo_ichigo_Character_new00_local);
    tolua_function(tolua_S,"delete",tolua_ichigo_ichigo_Character_delete00);
    tolua_function(tolua_S,"say",tolua_ichigo_ichigo_Character_say00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"ichigo",0);
  tolua_beginmodule(tolua_S,"ichigo");
   tolua_cclass(tolua_S,"Agent","ichigo::Agent","",NULL);
   tolua_beginmodule(tolua_S,"Agent");
    tolua_function(tolua_S,"findByName",tolua_ichigo_ichigo_Agent_findByName00);
    tolua_function(tolua_S,"getName",tolua_ichigo_ichigo_Agent_getName00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_ichigo (lua_State* tolua_S) {
 return tolua_ichigo_open(tolua_S);
};
#endif

