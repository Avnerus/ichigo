//
//  CocosLuaScriptingEngine.h

#ifndef __ICHIGO_COCOSLUASCRIPTINGENGINE_H__
#define __ICHIGO_COCOSLUASCRIPTINGENGINE_H__


#include <iostream>
#include <tr1/memory>

#include "ichigo.h"
#include "cocos2d.h"
#include "LuaEngine.h"


class CocosLuaScriptingEngine : public ichigo::ScriptingEngine {
public:
    
    CocosLuaScriptingEngine();
	virtual ~CocosLuaScriptingEngine();
    virtual bool executeScriptFile(std::string fileName);
    virtual int executeFunction(std::string funcName);
    virtual void init();
    
protected:
    std::tr1::shared_ptr<LuaEngine> _luaEngine;


};

#endif // __ICHIGO_COCOSLUASCRIPTINGENGINE_H__