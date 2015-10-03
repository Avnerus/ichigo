#ifndef __ICHIGO_COCOSANIMATION_H__
#define __ICHIGO_COCOSANIMATION_H__

#include "Animation.h"

#include "cocos2d.h"
using namespace cocos2d;


namespace ichigo
{
    class CocosAnimation : public Animation, public SelectorProtocol
    {
    public:
        
        CocosAnimation(SpriteActorView *spriteView);
        virtual ~CocosAnimation();
        
        virtual void        init(std::string frameName, std::string frameExtension, int frameCount, float frameDelay);
        
        CCSpriteFrame      *getFirstFrame();
        CCAction           *getAnimationAction();
        
    protected:
        
        CCSpriteFrame      *loadSpriteFrame(std::string fileName);
        void                animationEnded();
        
        CCSpriteFrame      *_firstFrame;
        CCAction           *_animationAction;
    };
}

#endif // __ICHIGO_COCOSANIMATION_H__
