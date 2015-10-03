#include "CocosSpriteActorView.h"
#include "CocosAnimation.h"
#include "Director.h"


namespace ichigo
{
    CocosSpriteActorView::CocosSpriteActorView(Agent *agent)
    : SpriteActorView(agent)
    {
        _ccSprite = NULL;
    }
    
    
    CocosSpriteActorView::~CocosSpriteActorView()
    {
    }
    
    
    // Gets called during actor's initialization
    void CocosSpriteActorView::init()
    {
        SpriteActorView::init();

        // Load sprite with no texture for the time being
        _ccSprite = new CCSprite();
        _ccSprite->init();
        _ccSprite->autorelease();        
    }
    
    
    // Gets called every frame
    void CocosSpriteActorView::update(float dt)
    {
        SpriteActorView::update(dt);
    }
    
    
    // Sets the position of the actor
    void CocosSpriteActorView::setPosition(const ichigo::Point &pos)
    {
        SpriteActorView::setPosition(pos);
        
        if (_ccSprite)
        {
            CCPoint glPos(pos.x, pos.y);
            _ccSprite->setPosition(glPos);
        }
    }
    
    
    // Sets the actor's scale
    void CocosSpriteActorView::setScale(float scale)
    {
        SpriteActorView::setScale(scale);
        
        if (_ccSprite)
        {
            _ccSprite->setScale(scale);
        }
    }
    
    
    // Set the angle (rotation) of the actor
    void CocosSpriteActorView::setAngle(float angle)
    {
        SpriteActorView::setAngle(angle);
        
        if (_ccSprite)
        {
            _ccSprite->setRotation(angle);
        }
    }
    
    
    // Sets the z-order of this sprite
    void CocosSpriteActorView::setZOrder(int zOrder)
    {
        SpriteActorView::setZOrder(zOrder);
        
        // If this sprite was already added to a parent, change the z-order under the parent. If not, the z-order
        // will be used when adding this sprite to a parent
        if (_parent && _ccSprite)
        {
            _ccSprite->getParent()->reorderChild(_ccSprite, zOrder);
        }
    }
    
    
    // Starts playing a given animation (or nothing if this animation is already playing)
    void CocosSpriteActorView::playAnimation(const std::string &name)
    {        
        if (name != _currentAnimation)
        {
            SpriteActorView::playAnimation(name);
        
            if (_currentAnimation != "")
            {
                // Sprite wasn't created yet. Create and set parameters
                if (!_ccSprite)
                {
                    _ccSprite = CCSprite::spriteWithSpriteFrame(((CocosAnimation *)_animations[_currentAnimation].get())->getFirstFrame());    
                    if (_ccSprite)
                    {
                        setPosition(getPosition());
                        setAngle(getAngle());
                        setScale(getScale());
                        setZOrder(getZOrder());
                        setVisible(isVisible());
                        setAlpha(getAlpha());
                    }
                }
                
                // The sprite was created, change texture
                if (_ccSprite)
                {
                    bool isAnimation = _animations[_currentAnimation]->getFrameCount() > 1;
                    
                    CCSpriteFrame *frame = ((CocosAnimation *)_animations[_currentAnimation].get())->getFirstFrame();
                    _ccSprite->setTexture(frame->getTexture());
                    CCRect frameRect = frame->getRectInPixels();
                    if (isAnimation)
                    {
                        frameRect.origin = frame->getOffsetInPixels();
                    }
                    _ccSprite->setTextureRect(frameRect);
                    _ccSprite->setDisplayFrame(frame);
                    
                    // If this animation contains more than one frame, play the animation
                    if (isAnimation)
                    {
                        _ccSprite->runAction(((CocosAnimation *)_animations[_currentAnimation].get())->getAnimationAction());
                    }
                }
                
            }
        }
    }
    
    
    // Restarts the current animation (calling playAnimation() with the current animation name will not interrupt the play)
    // This is called by the animation looping mechanism
    void CocosSpriteActorView::restartCurrentAnimation()
    {
        if (_ccSprite && _animations[_currentAnimation]->getFrameCount() > 1)
        {
            CCAction *animationAction = ((CocosAnimation *)_animations[_currentAnimation].get())->getAnimationAction();
            _ccSprite->stopAction(animationAction);
            _ccSprite->runAction(animationAction);
        }
    }
    
    
    // Creates a new animation of the type needed by this sprite (CocosAnimation)
    Animation *CocosSpriteActorView::createAnimation()
    {
        return new CocosAnimation(this);
    }
    
    
    // Sets the actor's radius using the sprite's width
    void CocosSpriteActorView::setRadiusFromWidth()
    {
        if (_ccSprite)
        {
            _radius = _ccSprite->getContentSize().width / 2.0f;
        }
    }
    
    
    // Sets the actor's radius using the sprite's height
    void CocosSpriteActorView::setRadiusFromHeight()
    {
        if (_ccSprite)
        {
            _radius = _ccSprite->getContentSize().height / 2.0f;
        }
    }
    
    float CocosSpriteActorView::getWidth() {
        if (_ccSprite) {
            return _ccSprite->getContentSize().width;
        }
        else {
            return 0.0f;
        }
    }
    
    float CocosSpriteActorView::getHeight() {
        if (_ccSprite) {
            return _ccSprite->getContentSize().height;
        }
        else {
            return 0.0f;
        }        
    }
    
    
    // Sets opacity of sprite
    void CocosSpriteActorView::setAlpha(float alpha)
    {
        SpriteActorView::setAlpha(alpha);
        
        if (_ccSprite)
        {
            _ccSprite->setOpacity(255 * _alpha);
        }
    }
    
    
    // Sets the pivot point for scales and rotation
    void CocosSpriteActorView::setPivot(const ichigo::Point &pivot)
    {
        if (_ccSprite)
        {
            // Anchor point gets a normalized point
            CCPoint normalizedPivot;
            normalizedPivot.x = (pivot.x / _ccSprite->boundingBox().size.width) / 2.0f + 0.5f;
            normalizedPivot.y = (pivot.y / _ccSprite->boundingBox().size.height) / 2.0f + 0.5f;
            _ccSprite->setAnchorPoint(normalizedPivot);
        }
    }
    
    
    // Shows or hides the scene view
    void CocosSpriteActorView::setVisible(bool isVisible)
    {
        SpriteActorView::setVisible(isVisible);
        
        if (_ccSprite)
        {
            _ccSprite->setIsVisible(isVisible);
        }
    }
    
    
    // Loads all frames from a sprite atlas into cache
    void CocosSpriteActorView::loadFramesFromAtlas(const std::string &atlasFile)
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(atlasFile.c_str());
    }
    
    
    // Returns the screen position of point in actor's local coordinate system
    Point CocosSpriteActorView::convertLocalToScreen(const ichigo::Point &localPos)
    {
        Point retVal;
        
        if (_ccSprite)
        {
            CCPoint worldPos = _ccSprite->getParent()->convertToWorldSpace(ccp(localPos.x, localPos.y));
            
            retVal.x = worldPos.x;
            retVal.y = worldPos.y;
        }
        
        return retVal;        
    }
    
    
    // Converts a point in screen coordinates to local coordinates of this actor
    Point CocosSpriteActorView::convertScreenToLocal(const ichigo::Point &screenPos)
    {
        Point retVal;
        
        if (_ccSprite)
        {
            CCPoint localPos = _ccSprite->getParent()->convertToNodeSpace(ccp(screenPos.x, screenPos.y));

            retVal.x = localPos.x;
            retVal.y = localPos.y;
        }
        
        return retVal;
    }
    
    
    // Adds a child actor to this sprite
    void CocosSpriteActorView::addChild(ichigo::ActorView *child)
    {
        if (_ccSprite)
        {
            _ccSprite->addChild((CCNode *)child->getInternalData(), child->getZOrder());
            child->setParent(this);
        }
    }
    
    
    // Removes a child from this sprite
    void CocosSpriteActorView::removeChild(ichigo::ActorView *child)
    {
        if (_ccSprite)
        {
            _ccSprite->removeChild((CCNode *)child->getInternalData(), false);
            child->setParent(NULL);
        }
    }
    
    
    // Returns a pointer to the CCSprite object
    void *CocosSpriteActorView::getInternalData()
    {
        return _ccSprite;
    }
}
