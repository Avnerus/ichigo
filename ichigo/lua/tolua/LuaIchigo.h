#ifndef LUAICHIGO_H
#define LUAICHIGO_H

#include "ichigo.h"
#include "tolua++.h"

#if  defined(_WIN32) && defined(_DEBUG)
#pragma warning (disable:4800)
#endif
int  tolua_ichigo_open(lua_State* tolua_S);


#endif//LUAICHIGO_H