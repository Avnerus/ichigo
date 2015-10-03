#include "AssetManager.h"
#include <iostream>

namespace ichigo {
        
    static ichigo::AssetManager s_assetManager;
    static bool s_bFirstRun = true;
    
    AssetManager* AssetManager::getInstance()
    {
    	if (s_bFirstRun)
    	{
    		s_assetManager.init();
            s_bFirstRun = false;
    	}

    	return &s_assetManager;
    }
    
    
    AssetManager::AssetManager() {
    }
    
    AssetManager::~AssetManager() {
    }
    
    bool AssetManager::init() {
        std::cout << "AssetManager Initializing" << std::endl;        
		
		return true;
    }
    
    cocos2d::CCTexture2D* AssetManager::getTexture(std::string name) {
        return cocos2d::CCTextureCache::sharedTextureCache()->addImage(name.c_str());
    }
    void AssetManager::addTexture(std::string name) {
        cocos2d::CCTextureCache::sharedTextureCache()->addImage(name.c_str());
    }
    

}