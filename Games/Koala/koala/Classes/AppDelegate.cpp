//
//  avnerdropAppDelegate.cpp
//  avnerdrop
//
//  Created by Avner Peled on 9/22/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "ichigo.h"
#include <tr1/memory>

#include "Loader.h"


USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::initInstance()
{
    bool bRet = false;
    do 
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

        // Initialize OpenGLView instance, that release by CCDirector when application terminate.
        // The HelloWorld is designed as HVGA.
        CCEGLView * pMainWnd = new CCEGLView();
        CC_BREAK_IF(! pMainWnd
            || ! pMainWnd->Create(TEXT("Avner Drop"), 320, 480));

#endif  // CC_PLATFORM_WIN32
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        // OpenGLView initialized in testsAppDelegate.mm on ios platform, nothing need to do here.
#endif  // CC_PLATFORM_IOS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		// android does not do anything
#endif
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)

        // Initialize OpenGLView instance, that release by CCDirector when application terminate.
        // The HelloWorld is designed as HVGA.
        CCEGLView* pMainWnd = new CCEGLView(this);
        CC_BREAK_IF(! pMainWnd || ! pMainWnd->Create(320,480));

#ifndef _TRANZDA_VM_  
        // on wophone emulator, we copy resources files to Work7/TG3/APP/ folder instead of zip file
        cocos2d::CCFileUtils::setResource("Game.zip");
#endif

#endif  // CC_PLATFORM_WOPHONE

        bRet = true;
    } while (0);
    return bRet;
}

bool AppDelegate::applicationDidFinishLaunching()
{
    
    // START ICHIGO
    std::tr1::shared_ptr<koala::Loader> koalaLoader (new koala::Loader());
    koalaLoader->init();
    

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
	
	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
