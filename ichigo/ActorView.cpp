#include "ActorView.h"
#include "Actor.h"
#include "DataManager.h"


namespace ichigo
{
    ActorView::ActorView(Agent *agent)
    : View(agent)
    {
        _type = "ActorView";
        
        _parent = NULL;
        _scale = 1.0f;
        _radius = 0;
    }
    
    
    ActorView::~ActorView()
    {
    }
    
    
    // Gets called during initialization
    void ActorView::init()
    {
        View::init();
    }
    
    
    // Config the view using Json data
    void ActorView::deserialize(Json::Value &configData)
    {
        View::deserialize(configData);
        
        setRadius   (DataManager::getFloat  (configData, "radius",      getRadius()));
        setZOrder   (DataManager::getInt    (configData, "zOrder",      getZOrder()));
    }
    
    
    // Gets called every frame
    void ActorView::update(float dt)
    {
        View::update(dt);
    }
    
    
    // Sets the radius of the actor
    void ActorView::setRadius(float radius)
    {
        _radius = radius;
    }
    
    
    // Returns the radius od the actor
    float ActorView::getRadius()
    {
        return _radius;
    }
    
    
    // Returns true if the given point (in screen coordinates) is within the actor's radius
    bool ActorView::isScreenPointInside(const ichigo::Point &screenPos)
    {
        bool retVal = false;
        
        if (_radius != 0)
        {
            // Find the actor's position on screen
            Point actorScreenPos = getPositionOnScreen();
            
            // Find distance from actor's position to given point on screen
            float distanceToPoint = actorScreenPos.distanceTo(screenPos);
            
            // Get actor's on-screen scale
            float worldScale = getWorldScale();
            
            // The point is within the actor only if the distance to it is shorter than the screen-scaled radius
            if (distanceToPoint <= _radius * worldScale)
            {
                retVal = true;
            }
        }
        
        return retVal;
    }
    
    
    // Points to the Actor's parent. Should be a LayerView or AcrorView.
    void ActorView::setParent(ichigo::View *parentView)
    {
        _parent = parentView;
    }
    Rect ActorView::getBoundingBox() {
        return Rect(0.0f, 0.0f, 0.0f, 0.0f);
    }
}
