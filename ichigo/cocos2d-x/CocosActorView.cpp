#include "CocosActorView.h"
#include "CocosLayerView.h"


namespace ichigo
{
    CocosActorView::CocosActorView(Agent *agent)
    : ActorView(agent)
    {
        _ccNode = NULL;
    }
    
    
    CocosActorView::~CocosActorView()
    {
    }
    
    
    // Called during view initialization
    void CocosActorView::init()
    {
        ActorView::init();
        
        // Initialize actual node
        _ccNode = CCNode::node();
    }
    
    
    // Called every frame
    void CocosActorView::update(float dt)
    {
        ActorView::update(dt);
    }
    
    
    // Sets the position of the actor
    void CocosActorView::setPosition(const ichigo::Point &pos)
    {
        ActorView::setPosition(pos);
        
        if (_ccNode)
        {
            _ccNode->setPosition(ccp(pos.x, pos.y));
        }
    }
    
    
    // Sets the scale of the actor
    void CocosActorView::setScale(float scale)
    {
        ActorView::setScale(scale);
        
        if (_ccNode)
        {
            _ccNode->setScale(scale);
        }
    }
    
    
    // Sets the angle (rotation) of the actor
    void CocosActorView::setAngle(float angle)
    {
        ActorView::setAngle(angle);
        
        if (_ccNode)
        {
            _ccNode->setRotation(angle);
        }
    }
    
    
    // Set the z-order of this object under it's parent
    void CocosActorView::setZOrder(int zOrder)
    {
        ActorView::setZOrder(zOrder);
        
        // If the node is already attached to a parent, set its z-order under that parent.
        // If it is not attached to a parent yet, it will get the z-order when attached.
        if (_parent && _ccNode)
        {
            _ccNode->getParent()->reorderChild(_ccNode, zOrder);
        }
    }
    
    
    // Sets the pivot point for scales and rotation
    void CocosActorView::setPivot(const ichigo::Point &pivot)
    {
        if (_ccNode && _radius)
        {
            // Anchor point gets a normalized point
            CCPoint normalizedPivot;
            normalizedPivot.x = (pivot.x / _radius) / 2.0f + 0.5f;
            normalizedPivot.y = (pivot.y / _radius) / 2.0f + 0.5f;
            _ccNode->setAnchorPoint(normalizedPivot);
        }
    }
    
    
    // Shows or hides the actor view
    void CocosActorView::setVisible(bool isVisible)
    {
        ActorView::setVisible(isVisible);
        
        if (_ccNode)
        {
            _ccNode->setIsVisible(isVisible);
        }
    }
    
    
    // Returns the screen position of point in actor's local coordinate system
    Point CocosActorView::convertLocalToScreen(const ichigo::Point &localPos)
    {
        Point retVal;
        
        if (_ccNode)
        {
            CCPoint worldPos = _ccNode->getParent()->convertToWorldSpace(ccp(localPos.x, localPos.y));
            
            retVal.x = worldPos.x;
            retVal.y = worldPos.y;
        }
        
        return retVal;        
    }
    
    
    // Converts a point in screen coordinates to local coordinates of this actor
    Point CocosActorView::convertScreenToLocal(const ichigo::Point &screenPos)
    {
        Point retVal;
        
        if (_ccNode)
        {
            CCPoint localPos = _ccNode->getParent()->convertToNodeSpace(ccp(screenPos.x, screenPos.y));
            
            retVal.x = localPos.x;
            retVal.y = localPos.y;
        }
        
        return retVal;
    }
    
    
    // Add a child under this actor
    void CocosActorView::addChild(ichigo::ActorView *child)
    {
        if (_ccNode)
        {
            _ccNode->addChild((CCNode *)child->getInternalData(), child->getZOrder());
            child->setParent(this);
        }
    }
    
    
    // Remove a child from this actor
    void CocosActorView::removeChild(ichigo::ActorView *child)
    {
        if (_ccNode)
        {
            _ccNode->removeChild((CCNode *)child->getInternalData(), false);
            child->setParent(NULL);
        }
    }
    
    
    // Returns the Cocos2d node
    void *CocosActorView::getInternalData()
    {
        return _ccNode;
    }
}
