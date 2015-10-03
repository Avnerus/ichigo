#include "CocosAnimation.h"
#include "Utils.h"
#include "CocosSpriteActorView.h"


namespace ichigo
{
    CocosAnimation::CocosAnimation(SpriteActorView *spriteView)
    : Animation(spriteView)
    {
        _firstFrame = NULL;
        _animationAction = NULL;
    }
    
    
    CocosAnimation::~CocosAnimation()
    {
        if (_firstFrame)
        {
            _firstFrame->release();
        }
        
        if (_animationAction)
        {
            _animationAction->release();
        }
    }
    
    
    // Initializes the animation from the parameters provided
    void CocosAnimation::init(std::string frameName, std::string frameExtension, int frameCount, float frameDelay)
    {
        Animation::init(frameName, frameExtension, frameCount, frameDelay);
        
        // If this animation has only one frame, only create the one sprite frame
        if (_frameCount == 1)
        {
            _firstFrame = loadSpriteFrame(_frameName + "." + _frameExtension);
        }
        else
        {
            // The animation has a few frames, load them all
            CCMutableArray<CCSpriteFrame *> *frameArray = new CCMutableArray<CCSpriteFrame *>(_frameCount);
            for (int i = 0; i < _frameCount; i++)
            {
                CCSpriteFrame *frame = loadSpriteFrame(_frameName + Utils::intToZeroPaddedString(i, 2) + "." + _frameExtension);
                frameArray->addObject(frame);
                
                // Save first frame
                if (i == 0)
                {
                    _firstFrame = frame;
                }
            }
            
            // Create a sequence of actions: first run the animation, then wait for duration (so also last frame is displayed the same
            // amount of time) and then call a callback function to handle event and looping
            CCAnimate *animation = CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(frameArray, _frameDelay), false);
            CCCallFunc *callback = CCCallFunc::actionWithTarget(this, callfunc_selector(CocosAnimation::animationEnded));
            _animationAction = CCSequence::actions(animation, callback, NULL);
            _animationAction->retain();
        }
        
        // Make sure we don't lose this texture
        if (_firstFrame)
        {
            _firstFrame->retain();
        }
    }
    
    
    // Returns the first frame of the animation
    CCSpriteFrame *CocosAnimation::getFirstFrame()
    {
        return _firstFrame;
    }
    
    
    // Returns the action which runs the animation
    CCAction *CocosAnimation::getAnimationAction()
    {
        return _animationAction;
    }
    
    
    // Creates and returns a cocos sprite frame from a filename
    CCSpriteFrame *CocosAnimation::loadSpriteFrame(std::string fileName)
    {
        // First attempt to get it from the frame cache, in case it was already loaded from an atlas
        CCSpriteFrame *retVal = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName.c_str());
        
        // If not found, create the frame by loading texture
        if (!retVal)
        {
            CCTexture2D *frameTexture = CCTextureCache::sharedTextureCache()->addImage(fileName.c_str());
            if (frameTexture)
            {
                retVal = CCSpriteFrame::frameWithTexture(frameTexture, 
                                                         CCRect(0, 0, frameTexture->getContentSize().width, frameTexture->getContentSize().height));
                
                // Add to frame cache
                CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(retVal, fileName.c_str());
            }
        }
        
        return retVal;
    }
    
    
    // Gets called when the animation finishes
    void CocosAnimation::animationEnded()
    {
        // Raise an event if needed
        publishEvent();
        
        // If looping needed, loop
        if (_loop)
        {
            _spriteView->restartCurrentAnimation();
        }
    }
}
