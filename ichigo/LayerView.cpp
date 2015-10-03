#include "LayerView.h"
#include "DataManager.h"
#include "Agent.h"


namespace ichigo
{
    LayerView::LayerView(Agent *agent)
    : View(agent), _viewportPosMultiplier(1.0f, 1.0f), _clipToBounds(false), _clippingOrigin(0, 0), _clippingSize(0, 0)
    {
        _type = "LayerView";
        _parent = NULL;
    }
    
    
    LayerView::~LayerView()
    {
    }
    
    
    // Called during view initialization
    void LayerView::init()
    {
        View::init();
    }
    
    
    // Configs the view's data from a JSON structure
    void LayerView::deserialize(Json::Value &configData)
    {
        View::deserialize(configData);
        
        setZOrder               (DataManager::getInt  (configData, "zOrder",                   getZOrder()));
        setViewportPosMultiplier(DataManager::getPoint(configData, "viewportPosMultiplier",    getViewportPosMultiplier()));       
        clipToBounds            (DataManager::getBool (configData, "clipToBounds",             isClippingToBounds()));
        
        Point clippingPos =      DataManager::getPoint(configData, "clippingPos",              Point(0, 0));
        Point clippingSize =     DataManager::getPoint(configData, "clippingSize",             Point(0, 0));
        setClippingBounds(clippingPos.x, clippingPos.y, clippingSize.x, clippingSize.y);
    }
    
    
    // Called every frame
    void LayerView::update(float dt)
    {
        View::update(dt);
    }
    
    
    // Sets the layer's position multiplier. When the Scene's viewport position is updated, all the layers move accordingly.
    // The "speed" in which the layer moves will be the opposite direction to the movement of the viewport, multiplied by
    // "viewportPosMultiplier". Giving each layer different values in the multiplier can create an illusion of depth while 
    // the viewport is moved (if deeper layers move slower).
    void LayerView::setViewportPosMultiplier(const ichigo::Point &multiplier)
    {
        _viewportPosMultiplier = multiplier;
    }
    
    
    // Returns the viewport position multiplier (see comment of setViewportPosMultiplier() for explanation).
    const Point &LayerView::getViewportPosMultiplier()
    {
        return _viewportPosMultiplier;
    }
    
    
    // Sets the layer's clipping on or off. If true, objects in the layer outside the bounds provided by setClippingBounds() will not
    // be drawn.
    void LayerView::clipToBounds(bool clip)
    {
        _clipToBounds = clip;
    }
    
    
    // Returns true if the layer's clipping is on
    bool LayerView::isClippingToBounds()
    {
        return _clipToBounds;
    }
    
    
    // Sets the bounds (in layer coordinates, [x,y] being the bottom left corent of the rect) outside of which nothing should be
    // drawn when clipping is set to true
    void LayerView::setClippingBounds(float x, float y, float w, float h)
    {
        _clippingOrigin.x = x;
        _clippingOrigin.y = y;
        _clippingSize.x = w;
        _clippingSize.y = h;
        
        // std::cout << _agent->getName() << " Setting clipping bounds to " << x << "," << y << "," << w << "," << h << " Clipping? " << _clipToBounds << std::endl;
    }
    
    
    // Set the view's parent
    void LayerView::setParent(ichigo::SceneView *sceneView)
    {
        _parent = sceneView;
    }
    
    Rect LayerView::getBoundingBox() {
        return Rect(0.0f, 0.0f, 0.0f, 0.0f);
    }    
}
