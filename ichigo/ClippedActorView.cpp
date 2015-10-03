#include "ClippedActorView.h"
#include "DataManager.h"


namespace ichigo
{
    ClippedActorView::ClippedActorView(Agent *agent)
    : ActorView(agent),_clipToBounds(false), _clippingOrigin(0, 0), _clippingSize(0, 0) {
        
        _parent = NULL;
    }
    
    
    ClippedActorView::~ClippedActorView() {
    }
    
    
    // Configs the view's data from a JSON structure
    void ClippedActorView::deserialize(Json::Value &configData)
    {
        ActorView::deserialize(configData);
        clipToBounds            (DataManager::getBool (configData, "clipToBounds",             isClippingToBounds()));
        
        Point clippingPos =      DataManager::getPoint(configData, "clippingPos",              Point(0, 0));
        Point clippingSize =     DataManager::getPoint(configData, "clippingSize",             Point(0, 0));
        setClippingBounds(clippingPos.x, clippingPos.y, clippingSize.x, clippingSize.y);
    }
    
    Point   ClippedActorView::getClippingSize() {
        return _clippingSize;
    }
    void    ClippedActorView::setClippingSize(Point size) {
        setClippingBounds(_clippingOrigin.x, _clippingOrigin.y, size.x, size.y);        
    }
      
    
    // Sets the layer's clipping on or off. If true, objects in the layer outside the bounds provided by setClippingBounds() will not
    // be drawn.
    void ClippedActorView::clipToBounds(bool clip)
    {
        _clipToBounds = clip;
    }
    
    
    // Returns true if the layer's clipping is on
    bool ClippedActorView::isClippingToBounds()
    {
        return _clipToBounds;
    }
    
    
    // Sets the bounds (in layer coordinates, [x,y] being the bottom left corent of the rect) outside of which nothing should be
    // drawn when clipping is set to true
    void ClippedActorView::setClippingBounds(float x, float y, float w, float h)
    {
        _clippingOrigin.x = x;
        _clippingOrigin.y = y;
        _clippingSize.x = w;
        _clippingSize.y = h;
    }
}
