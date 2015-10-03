#include "CocosSceneView.h"
#include "CocosLayerView.h"
#include "Scene.h"


namespace ichigo
{
    CocosSceneView::CocosSceneView(Agent *agent)
    : SceneView(agent)
    {
        _ccScene = NULL;
        _bgColorLayer = NULL;
    }
    
    
    CocosSceneView::~CocosSceneView()
    {
        if (_ccScene)
        {
            _ccScene->release();
            _ccScene = NULL;
        }
    }
    
    
    // Initialize vire object
    void CocosSceneView::init()
    {
        SceneView::init();
        
        // Initialize the cocos scene itself
        _ccScene = CocosUpdatingScene::node();
        _ccScene->retain();
        
        // The touch layer is the layer which handles touch input and passes the data to the Director
        _touchLayer = CocosTouchLayer::node();
        _ccScene->addChild(_touchLayer);
    }
    
    
    // Gets called each frame
    void CocosSceneView::update(float dt)
    {
        SceneView::update(dt);
    }
    
    
    // Set's the viewport's position (top left corner)
    void CocosSceneView::setPosition(const ichigo::Point &pos)
    {
        SceneView::setPosition(pos);
        
        if (_ccScene)
        {
            // We don't actually move the whole scene, but instead each layer is moved seperately. This is to allow
            // layers to move in different speedsm using their viewport-position-multiplier.
            AgentList &layerList = _agent->getChildren();
            
            // Now that the viewport is moved, refresh the positions of all child layers
            for (AgentList::iterator it = layerList.begin(); it != layerList.end(); it++)
            {
                LayerView *layerView = (LayerView *)it->second->getView();
                layerView->setPosition(layerView->getPosition());
            }
        }
    }
    
    
    // Set the scene's scale (zoom)
    void CocosSceneView::setScale(float scale)
    {
        // Save the amount of change, it will might be used later for static layers
        float scaleChange = scale / _scale;
        
        SceneView::setScale(scale);
        
        if (_ccScene)
        {
            _ccScene->setScale(scale);
        }
        
        // Go over all layers in the scene. If the layer is "static" (viewport pos multiplier is 0), scale it down to cancel
        // the scene scale, making it appear static
        AgentList &layerList = _agent->getChildren();
        for (AgentList::iterator it = layerList.begin(); it != layerList.end(); it++)
        {
            LayerView *layerView = (LayerView *)it->second->getView();
            if (layerView->getViewportPosMultiplier() == Point(0, 0))
            {
                layerView->setScale(layerView->getScale() / scaleChange);
            }
        }
    }
    
    
    // Set the scene's angle (rotation)
    void CocosSceneView::setAngle(float angle)
    {
        // Save the amount of change, it might be used later for static layers
        float deltaAngle = angle - _angle;
        
        SceneView::setAngle(angle);
        
        if (_ccScene)
        {
            _ccScene->setRotation(angle);
        }
        
        // Go over all layers in the scene. If the layer is "static" (viewport pos multiplier is 0), rotate the opposite direction
        // to cancel the scene rotation, making it appear static
        AgentList &layerList = _agent->getChildren();
        for (AgentList::iterator it = layerList.begin(); it != layerList.end(); it++)
        {
            LayerView *layerView = (LayerView *)it->second->getView();
            if (layerView->getViewportPosMultiplier() == Point(0, 0))
            {
                layerView->setAngle(layerView->getAngle() - deltaAngle);
            }
        }
    }
    
    
    // Sets the background color of the scene
    void CocosSceneView::setBGColor(const ichigo::Color &bgColor)
    {
        SceneView::setBGColor(bgColor);
        
        // Remove existing color background
        if (_bgColorLayer)
        {
            _bgColorLayer->getParent()->removeChild(_bgColorLayer, true);
        }
        
        // Create new color layer and add to the back of the scene
        _bgColorLayer = CCLayerColor::layerWithColorWidthHeight(ccc4(bgColor.r, bgColor.g, bgColor.b, bgColor.a), 
                                                                BGCOLOR_LAYER_WIDTH, BGCOLOR_LAYER_HEIGHT);
        if (_ccScene) 
        {
            _ccScene->addChild(_bgColorLayer, BGCOLOR_LAYER_ZORDER);
            _bgColorLayer->setPosition(ccp(-(BGCOLOR_LAYER_WIDTH / 2), -(BGCOLOR_LAYER_HEIGHT / 2)));
        }
    }
    
    
    // Sets the pivot point for scales and rotation
    void CocosSceneView::setPivot(const ichigo::Point &pivot)
    {
        if (_ccScene)
        {
            // Anchor point gets a normalized point
            CCPoint normalizedPivot;
            normalizedPivot.x = (pivot.x / _ccScene->boundingBox().size.width) / 2.0f + 0.5f;
            normalizedPivot.y = (pivot.y / _ccScene->boundingBox().size.height) / 2.0f + 0.5f;
            _ccScene->setAnchorPoint(normalizedPivot);
        }
    }
    
    
    // Returns the screen position of point in scene's local coordinate system
    Point CocosSceneView::convertLocalToScreen(const ichigo::Point &localPos)
    {
        Point retVal;
        
        if (_ccScene)
        {
            CCPoint worldPos = _ccScene->convertToWorldSpace(ccp(localPos.x, localPos.y));
            
            retVal.x = worldPos.x;
            retVal.y = worldPos.y;
        }
        
        return retVal;        
    }
    
    
    // Converts a point in screen coordinates to local coordinates of this scene
    Point CocosSceneView::convertScreenToLocal(const ichigo::Point &screenPos)
    {
        Point retVal;
        
        if (_ccScene)
        {
            CCPoint localPos = _ccScene->convertToNodeSpace(ccp(screenPos.x, screenPos.y));
            
            retVal.x = localPos.x;
            retVal.y = localPos.y;
        }
        
        return retVal;
    }
    
    
    // Adds a layer to this scene
    void CocosSceneView::addLayer(LayerView *layerView)
    {
        if (_ccScene)
        {
            _ccScene->addChild((CCNode *)layerView->getInternalData(), layerView->getZOrder());
            layerView->setParent(this);
        }
    }
    
    
    // Removes a layer from this scene
    void CocosSceneView::removeLayer(LayerView *layerView)
    {
        if (_ccScene)
        {
            _ccScene->removeChild((CCNode *)layerView->getInternalData(), false);
            layerView->setParent(NULL);
        }
    }
    
    
    // Notifies this scene that it is now the active scene under the director
    void CocosSceneView::setAsCurrent(bool isCurrent)
    {
        // std::cout << "CocosSceneView::setAsCurrent" << std::endl;
        
        if (_ccScene)
        {
            if (isCurrent)
            {
                // std::cout << "isCurrent!!" << std::endl;
                // This is the current scene, schedule it to start updating the whole game
                _ccScene->scheduleUpdate();
            }
            else
            {
                // Stopped being the current scene, unschedule this scene
                _ccScene->unscheduleUpdate();
            }
        }
    }
    
    
    // Returns a pointer to the CCScene
    void *CocosSceneView::getInternalData()
    {
        return _ccScene;
    }
}
