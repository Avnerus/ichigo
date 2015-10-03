#include "CocosClippedActorView.h"


namespace ichigo
{
    CocosClippedActorView::CocosClippedActorView(Agent *agent)
    : ClippedActorView(agent) {
        _clippingNode = NULL;
    }
    
    
    CocosClippedActorView::~CocosClippedActorView() {
    }
    
    
    // Called during view initialization
    void CocosClippedActorView::init() {
        
        ClippedActorView::init();
        
        // Initialize clippping node
        _clippingNode = CocosClippingNode::clippingNode();
    }
    
    
    // Called every frame
    void CocosClippedActorView::update(float dt) {
        
        ClippedActorView::update(dt);
    }
    
    
    // Sets the position of the actor
    void CocosClippedActorView::setPosition(const ichigo::Point &pos)
    {
        ClippedActorView::setPosition(pos);
        
        if (_clippingNode)
        {
            _clippingNode->setPosition(ccp(pos.x, pos.y));
        }
    }
    
    
    // Sets the scale of the actor
    void CocosClippedActorView::setScale(float scale)
    {
        ClippedActorView::setScale(scale);
        
        if (_clippingNode)
        {
            _clippingNode->setScale(scale);
        }
    }
    
    
    // Sets the angle (rotation) of the actor
    void CocosClippedActorView::setAngle(float angle)
    {
        ClippedActorView::setAngle(angle);
        
        if (_clippingNode)
        {
            _clippingNode->setRotation(angle);
        }
    }
    
    
    // Set the z-order of this object under it's parent
    void CocosClippedActorView::setZOrder(int zOrder)
    {
        ClippedActorView::setZOrder(zOrder);
        
        // If the node is already attached to a parent, set its z-order under that parent.
        // If it is not attached to a parent yet, it will get the z-order when attached.
        if (_parent && _clippingNode)
        {
            _clippingNode->getParent()->reorderChild(_clippingNode, zOrder);
        }
    }
    
    
    // Sets the pivot point for scales and rotation
    void CocosClippedActorView::setPivot(const ichigo::Point &pivot)
    {
        if (_clippingNode && _radius)
        {
            // Anchor point gets a normalized point
            CCPoint normalizedPivot;
            normalizedPivot.x = (pivot.x / _radius) / 2.0f + 0.5f;
            normalizedPivot.y = (pivot.y / _radius) / 2.0f + 0.5f;
            _clippingNode->setAnchorPoint(normalizedPivot);
        }
    }
    
    
    // Shows or hides the actor view
    void CocosClippedActorView::setVisible(bool isVisible)
    {
        ClippedActorView::setVisible(isVisible);
        
        if (_clippingNode)
        {
            _clippingNode->setIsVisible(isVisible);
        }
    }
    
    
    // Returns the screen position of point in actor's local coordinate system
    Point CocosClippedActorView::convertLocalToScreen(const ichigo::Point &localPos)
    {
        Point retVal;
        
        if (_clippingNode)
        {
            CCPoint worldPos = _clippingNode->getParent()->convertToWorldSpace(ccp(localPos.x, localPos.y));
            
            retVal.x = worldPos.x;
            retVal.y = worldPos.y;
        }
        
        return retVal;        
    }
    
    
    // Converts a point in screen coordinates to local coordinates of this actor
    Point CocosClippedActorView::convertScreenToLocal(const ichigo::Point &screenPos)
    {
        Point retVal;
        
        if (_clippingNode)
        {
            CCPoint localPos = _clippingNode->getParent()->convertToNodeSpace(ccp(screenPos.x, screenPos.y));
            
            retVal.x = localPos.x;
            retVal.y = localPos.y;
        }
        
        return retVal;
    }
    
    
    // Add a child under this actor
    void CocosClippedActorView::addChild(ichigo::ActorView *child)
    {
        if (_clippingNode)
        {
            _clippingNode->addChild((CCNode *)child->getInternalData(), child->getZOrder());
            child->setParent(this);
        }
    }
    
    
    // Remove a child from this actor
    void CocosClippedActorView::removeChild(ichigo::ActorView *child)
    {
        if (_clippingNode)
        {
            _clippingNode->removeChild((CCNode *)child->getInternalData(), false);
            child->setParent(NULL);
        }
    }
    
    
    // Returns the Cocos2d node
    void *CocosClippedActorView::getInternalData()
    {
        return _clippingNode;
    }
    
    // Sets clipping to enabled or disabled. Clipping is done with the CocosClippingNode between this layer and its children
    void CocosClippedActorView::clipToBounds(bool clipToBounds)
    {
        ClippedActorView::clipToBounds(clipToBounds);
        
        if (_clippingNode)
        {
            _clippingNode->shouldClip(clipToBounds);
        }
    }
    
    
    // Sets the clipping bounds for the node (they only take effect if clipping has been enabled with clipToBounds)
    void CocosClippedActorView::setClippingBounds(float x, float y, float w, float h)
    {
        ClippedActorView::setClippingBounds(x, y, w, h);
        
        if (_clippingNode)
        {
            CCRect boundsRect = CCRectMake(x, y, w, h);
            _clippingNode->setClipRect(boundsRect);
        }
    }
}
