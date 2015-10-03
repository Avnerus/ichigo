#include "ichigo.h"

#include "Loader.h"

#include <iostream>

USING_NS_CC;


namespace it 
{
    Loader::Loader() 
	{
        std::cout << "IchigoTest Loader Started" << std::endl;
    }
    
	
	Loader::~Loader() 
	{
		std::cout << "IchigoTest Loader Ended" << std::endl;
    }
	
	
	// Initialize objects
    void Loader::init() 
	{
        std::cout << "Loader init" << std::endl;  
				
        initDevice();
        loadTextures();                  
        
        ichigo::Director *director = (ichigo::Director *)ichigo::AgentFactory::createAgent("Director");
        director->setScenesFileName(CONST_STRING("SCENES_FILENAME"));
        director->start();
    }
    
   
	// Initialize device specific input/output
    void Loader::initDevice() 
	{  
        // Load constants
        ichigo::DataManager::getInstance()->loadConstFile("Config.json");
        
		// Get the Cocos2d director
        cocos2d::CCDirector *ccDirector = cocos2d::CCDirector::sharedDirector();
        
		// For now, standart initialization
        ccDirector->setOpenGLView(&cocos2d::CCEGLView::sharedOpenGLView());
        ccDirector->setDeviceOrientation(cocos2d::kCCDeviceOrientationLandscapeLeft);
    	ccDirector->setDisplayFPS(true);
    	ccDirector->setAnimationInterval(1.0f / 60.0f);        
    } 
	
    
	// Preload textures
    void Loader::loadTextures() 
	{
        std::cout << "Loading Textures" << std::endl;  
		
		// Load textures from file before game start
        ichigo::AssetManager::getInstance()->addTexture("avner.png");
    }
}