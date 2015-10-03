//
//  CocosLuaScriptingEngine.cpp
#include "CocosLuaScriptingEngine.h"
#include "LuaEngineImpl.h"
#include            "LuaIchigo.h"

#include <iostream>

CocosLuaScriptingEngine::CocosLuaScriptingEngine() {
    
}

CocosLuaScriptingEngine::~CocosLuaScriptingEngine() {
    
}

void CocosLuaScriptingEngine::init() {
    std::cout << "Cocos-Lua scripting engine initializing" << std::endl;
    _luaEngine = std::tr1::shared_ptr<LuaEngine>(new LuaEngine);
    
    // Add a touch of ICHIGO
    tolua_ichigo_open(CCLuaScriptModule::sharedLuaScriptModule()->getLuaState());
    
    
}

bool CocosLuaScriptingEngine::executeScriptFile(std::string fileName) {
    std::string path = cocos2d::CCFileUtils::fullPathFromRelativePath(fileName.c_str());
	_luaEngine->addSearchPath(path.substr(0, path.find_last_of("/")).c_str());
	bool result = _luaEngine->executeScriptFile(path.c_str());	
	if (result) {
        std::cout << "Loaded script " << fileName << std::endl;
    }
    else {
        std::cout << "Failed to load script! " << fileName << std::endl;
    }
    return result;
}

int CocosLuaScriptingEngine::executeFunction(std::string funcName) {
    return _luaEngine->executeFuction(funcName.c_str());
}