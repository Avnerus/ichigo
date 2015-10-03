#include "CocosLayerView.h"
#include "CocosSceneView.h"
#include "CocosActorView.h"
#include "Director.h"


namespace ichigo
{
    CocosLayerView::CocosLayerView(Agent *agent)
    : LayerView(agent)
    {
        _ccLayer = NULL;
    }
    
    
    CocosLayerView::~CocosLayerView()
    {
    }
    
    
    // Gets called during initialization
    void CocosLayerView::init()
    {
        LayerView::init();
                
        // Initialize the cocos layer itself
        _ccLayer = CCLayer::node();         
        
        // Initialize a clipping node, and add it between the layer and its children
        _clippingNode = CocosClippingNode::clippingNode();
        _ccLayer->addChild(_clippingNode);
    }
    
    
    // Gets called every frame
    void CocosLayerView::update(float dt)
    {
        LayerView::update(dt);
    }
    
    
    // Sets the layer's position
    void CocosLayerView::setPosition(const ichigo::Point &pos)
    {
        LayerView::setPosition(pos);
        
        if (_ccLayer)
        {
            // Get the scene's viewport's position
            Point vpPos(0, 0);
            if (_parent)
            {
                vpPos = _parent->getPosition();
            }
            
            // Set new position , take into account viewport position
            CCPoint newPos;
            newPos.x = pos.x + (vpPos.x * _viewportPosMultiplier.x);
            newPos.y = pos.y + (vpPos.y * _viewportPosMultiplier.y);
            
            // Set the position
            _ccLayer->setPosition(newPos);
        }
    }
    
    
    // Set the layer's scale
    void CocosLayerView::setScale(float scale)
    {
        LayerView::setScale(scale);
        
        if (_ccLayer)
        {
            _ccLayer->setScale(scale);
        }
    }
    
    
    // Set the layer's angle (rotation)
    void CocosLayerView::setAngle(float angle)
    {
        LayerView::setAngle(angle);
        
        if (_ccLayer)
        {
            _ccLayer->setRotation(angle);
        }
    }
    
    
    // Sets the z-order of the layer
    void CocosLayerView::setZOrder(int zOrder)
    {
        LayerView::setZOrder(zOrder);
        
        // If this layer was already added to a CCScene, tell the CCScene our new z-order
        if (_parent && _ccLayer)
        {
            ((CCScene *)_parent->getInternalData())->reorderChild(_ccLayer, zOrder);
        }
    }
    
    
    // Sets the pivot point for scales and rotation
    void CocosLayerView::setPivot(const ichigo::Point &pivot)
    {
        if (_ccLayer)
        {
            // Anchor point gets a normalized point
            CCPoint normalizedPivot;
            normalizedPivot.x = (pivot.x / _ccLayer->boundingBox().size.width) / 2.0f + 0.5f;
            normalizedPivot.y = (pivot.y / _ccLayer->boundingBox().size.height) / 2.0f + 0.5f;
            _ccLayer->setAnchorPoint(normalizedPivot);
        }
    }
    
    
    // Shows or hides the layer view
    void CocosLayerView::setVisible(bool isVisible)
    {
        LayerView::setVisible(isVisible);
        
        if (_ccLayer)
        {
            _ccLayer->setIsVisible(isVisible);
        }
    }
        
    
    // Sets clipping to enabled or disabled. Clipping is done with the CocosClippingNode between this layer and its children
    void CocosLayerView::clipToBounds(bool clipToBounds)
    {
        LayerView::clipToBounds(clipToBounds);
        
        if (_clippingNode)
        {
            _clippingNode->shouldClip(clipToBounds);
        }
    }
    
    
    // Sets the clipping bounds for the node (they only take effect if clipping has been enabled with clipToBounds)
    void CocosLayerView::setClippingBounds(float x, float y, float w, float h)
    {
        LayerView::setClippingBounds(x, y, w, h);
        
        if (_clippingNode)
        {
            CCRect boundsRect = CCRectMake(x, y, w, h);
            _clippingNode->setClipRect(boundsRect);
        }
    }
    
    
    // Returns the screen position of point in layer's local coordinate system
    Point CocosLayerView::convertLocalToScreen(const ichigo::Point &localPos)
    {
        Point retVal;
        
        if (_ccLayer)
        {
            CCPoint worldPos = _ccLayer->getParent()->convertToWorldSpace(ccp(localPos.x, localPos.y));
            
            retVal.x = worldPos.x;
            retVal.y = worldPos.y;
        }
        
        return retVal;        
    }
    
    
    // Converts a point in screen coordinates to local coordinates of this layer
    Point CocosLayerView::convertScreenToLocal(const ichigo::Point &screenPos)
    {
        Point retVal;
        
        if (_ccLayer)
        {
            CCPoint localPos = _ccLayer->getParent()->convertToNodeSpace(ccp(screenPos.x, screenPos.y));
            
            retVal.x = localPos.x;
            retVal.y = localPos.y;
        }
        
        return retVal;
    }
    
    
    // Adds an actor as the child of this layer
    void CocosLayerView::addActor(ichigo::ActorView *actor)
    {
        if (_ccLayer && _clippingNode)
        {
            _clippingNode->addChild((CCNode *)actor->getInternalData(), actor->getZOrder());
            actor->setParent(this);
        }
    }
    
    
    // Removes an actor from the layer
    void CocosLayerView::removeActor(ichigo::ActorView *actor)
    {
        if (_ccLayer && _clippingNode)
        {
            _clippingNode->removeChild((CCNode *)actor->getInternalData(), false);
            actor->setParent(NULL);
        }
    }
    
    
    
    
    // Returns the actual cocos layer
    void *CocosLayerView::getInternalData()
    {
        return _ccLayer;
    }
}
