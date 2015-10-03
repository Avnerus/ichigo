#include "CocosTouchLayer.h"
#include "EventManager.h"
#include "TouchPoint.h"
#include "Director.h"


namespace ichigo
{
    // Called during initialization
    bool CocosTouchLayer::init()
    {
        bool retVal = CCLayer::init();
        
        if (retVal)
        {
            // This class will handle touch event
            m_bIsTouchEnabled = true;
        }
        
        return retVal;
    }
    
    
    // Called by Cocos when touches have been started.
    void CocosTouchLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
    {
        // Go over all the touches in the set
        for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); it++)
        {
            // Translate touch position to GL coordinates
            CCTouch *ccTouch = (CCTouch *)(*it);
            CCPoint pos = CCDirector::sharedDirector()->convertToUI(ccTouch->locationInView(ccTouch->view()));
            
            // Create a new ichigo touch object at the new position. The ccTouch object is supposed to be consistent
            // throughout the whole touch, so its address will make a good touchID.
            TouchPoint *tp = new TouchPoint((int)ccTouch, pos.x, pos.y);
            
            // Let the event manager handle this new touch
            EventManager::getInstance()->onTouchStarted(tp);
        }
    }
    
    
    // Called by Cocos when touches have moved
    void CocosTouchLayer::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
    {
        // Go over all the touchs in the set
        for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); it++)
        {
            // Translate touch position to GL coordinates
            CCTouch *ccTouch = (CCTouch *)(*it);
            CCPoint pos = CCDirector::sharedDirector()->convertToUI(ccTouch->locationInView(ccTouch->view()));
            
            // Create a new ichigo touch object with the new position
            TouchPoint tp((int)ccTouch, pos.x, pos.y);
            
            // Let the event manager handle this touch
            EventManager::getInstance()->onTouchMoved(&tp);
        }
    }
    
    
    // Called by Cocos when touches have ended
    void CocosTouchLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
    {
        // Go over all the touchs in the set
        for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); it++)
        {
            // Translate touch position to GL coordinates
            CCTouch *ccTouch = (CCTouch *)(*it);
            CCPoint pos = CCDirector::sharedDirector()->convertToUI(ccTouch->locationInView(ccTouch->view()));
            
            // Create a new ichigo touch object with the new position
            TouchPoint tp((int)ccTouch, pos.x, pos.y);
            
            // Let the event manager handle this touch
            EventManager::getInstance()->onTouchEnded(&tp);
        }        
    }
    
    
    // Called by Cocos when touches were cancelled
    void CocosTouchLayer::ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
    {
        ccTouchesEnded(pTouches, pEvent);
    }
}
