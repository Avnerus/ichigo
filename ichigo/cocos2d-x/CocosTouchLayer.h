#ifndef __ICHIGO_COCOSTOUCHLAYER_H__
#define __ICHIGO_COCOSTOUCHLAYER_H__

#include "cocos2d.h"

using namespace cocos2d;


namespace ichigo
{
    class CocosTouchLayer : public CCLayer
    {
    public:
        
        virtual bool init();
        
        virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
        virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
        virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
        virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);     
        
        LAYER_NODE_FUNC(CocosTouchLayer);
    };
}


#endif  // __ICHIGO_COCOSTOUCHLAYER_H__
