#include "CocosColorLayerView.h"
#include "CocosSceneView.h"
#include "CocosActorView.h"
#include "Director.h"


namespace ichigo
{
    CocosColorLayerView::CocosColorLayerView(Agent *agent)
    : ColorLayerView(agent)
    {
        _ccLayer = NULL;
    }
    
    
    CocosColorLayerView::~CocosColorLayerView()
    {
    }
    
    
    // Gets called during initialization
    void CocosColorLayerView::init()
    {
        ColorLayerView::init();
        
        cout << "CocosColorLayerView::init() bgColor: " << _bgColor << " Width " << _width << " Height " << _height << std::endl;
                
        // Initialize the cocos layer itself
        _ccLayer = CCLayerColor::layerWithColorWidthHeight(ccc4(_bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a), 
                                                                _width, _height);

        
        // Initialize a clipping node, and add it between the layer and its children
        _clippingNode = CocosClippingNode::clippingNode();
        _ccLayer->addChild(_clippingNode);
    }
    
    
    // Gets called every frame
    void CocosColorLayerView::update(float dt)
    {
        ColorLayerView::update(dt);
    }
    
    
    // Sets the layer's position
    void CocosColorLayerView::setPosition(const ichigo::Point &pos)
    {
        ColorLayerView::setPosition(pos);
        
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
    void CocosColorLayerView::setScale(float scale)
    {
        ColorLayerView::setScale(scale);
        
        if (_ccLayer)
        {
            _ccLayer->setScale(scale);
        }
    }
    
    
    // Set the layer's angle (rotation)
    void CocosColorLayerView::setAngle(float angle)
    {
        ColorLayerView::setAngle(angle);
        
        if (_ccLayer)
        {
            _ccLayer->setRotation(angle);
        }
    }
    
    
    // Sets the z-order of the layer
    void CocosColorLayerView::setZOrder(int zOrder)
    {
        ColorLayerView::setZOrder(zOrder);
                
        // If this layer was already added to a CCScene, tell the CCScene our new z-order
        if (_parent && _ccLayer)
        {        
            ((CCScene *)_parent->getInternalData())->reorderChild(_ccLayer, zOrder);
        }
    }
    
    
    // Sets the pivot point for scales and rotation
    void CocosColorLayerView::setPivot(const ichigo::Point &pivot)
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
    void CocosColorLayerView::setVisible(bool isVisible)
    {
        ColorLayerView::setVisible(isVisible);
        
        if (_ccLayer)
        {
            _ccLayer->setIsVisible(isVisible);
        }
    }
    
    void CocosColorLayerView::setBGColor(const Color &bgColor) {
        ColorLayerView::setBGColor(bgColor);
        if (_ccLayer) {
            _ccLayer->setColor(ccc3(_bgColor.r, _bgColor.g, _bgColor.b));
            _ccLayer->setOpacity(_bgColor.a);
        }
    }
    
    void CocosColorLayerView::setHeight(float height) {
        ColorLayerView::setHeight(height);
        if (_ccLayer) {
            _ccLayer->changeHeight(height);
        }
    }
    
    void CocosColorLayerView::setWidth(float width) {
        ColorLayerView::setWidth(width);
        if (_ccLayer) {
            _ccLayer->changeWidth(width);
        }
    }
    
    
    // Sets clipping to enabled or disabled. Clipping is done with the CocosClippingNode between this layer and its children
    void CocosColorLayerView::clipToBounds(bool clipToBounds)
    {
        ColorLayerView::clipToBounds(clipToBounds);
        
        if (_clippingNode)
        {
            _clippingNode->shouldClip(clipToBounds);
        }
    }
    
    
    // Sets the clipping bounds for the node (they only take effect if clipping has been enabled with clipToBounds)
    void CocosColorLayerView::setClippingBounds(float x, float y, float w, float h)
    {
        ColorLayerView::setClippingBounds(x, y, w, h);
        
        if (_clippingNode)
        {
            CCRect boundsRect = CCRectMake(x, y, w, h);
            _clippingNode->setClipRect(boundsRect);
        }
    }
    
    
    // Returns the screen position of point in layer's local coordinate system
    Point CocosColorLayerView::convertLocalToScreen(const ichigo::Point &localPos)
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
    Point CocosColorLayerView::convertScreenToLocal(const ichigo::Point &screenPos)
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
    void CocosColorLayerView::addActor(ichigo::ActorView *actor)
    {
        if (_ccLayer && _clippingNode)
        {
            _clippingNode->addChild((CCNode *)actor->getInternalData(), actor->getZOrder());
            actor->setParent(this);
        }
    }
    
    
    // Removes an actor from the layer
    void CocosColorLayerView::removeActor(ichigo::ActorView *actor)
    {
        if (_ccLayer && _clippingNode)
        {
            _clippingNode->removeChild((CCNode *)actor->getInternalData(), false);
            actor->setParent(NULL);
        }
    } 
    
    
    // Returns the actual cocos layer
    void *CocosColorLayerView::getInternalData()
    {
        return _ccLayer;
    }
}
