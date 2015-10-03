#include "View.h"
#include "Agent.h"
#include "DataManager.h"


namespace ichigo
{
    View::View(Agent *agent)
    : _position()
    {
        _agent = agent;
        _type = "View";
        _zOrder = 0;
        _scale = 1.0f;
        _angle = 0.0f;
        _isVisible = true;
        _isMoving = false;
    }
    
    
    View::~View()
    {
    }
    
    
    // Gets called during view initialization
    void View::init()
    {
    }
    
    
    // Load view parameters from Json structure
    void View::deserialize(Json::Value &configData)
    {
        setPosition (DataManager::getPoint  (configData, "position",    getPosition()));
        setScale    (DataManager::getFloat  (configData, "scale",       getScale()));
        setAngle    (DataManager::getFloat  (configData, "angle",       getAngle()));
        setVisible  (DataManager::getBool   (configData, "isVisible",   isVisible()));
    }
    
    
    // Gets called every frame. dt is the time passed from previous frame
    void View::update(float dt)
    {
        if (_isMoving)
        {
            if (dt >= _moveDuration)
            {
                // Reached target
                setPosition(_moveTarget);
                _isMoving = false;
            }
            else
            {
                // Calculate how much we are closer to the target
                float currFrameDelta = dt / _moveDuration;
                
                // Find how much to move this frame
                Point currPosition = getPosition();
                Point vecToTarget = _moveTarget - currPosition;
                Point moveThisFrame = vecToTarget * currFrameDelta;
                setPosition(currPosition + moveThisFrame);
                
                _moveDuration -= dt;
            }
        }
    }
    
    
    // Is the agent currently on the move?
    bool View::isMoving()
    {
        return _isMoving;
    }
    
    
    // Move the agent to given position in "duration" seconds
    void View::moveTo(const ichigo::Point &target, float duration)
    {
        _isMoving = true;
        _moveTarget = target;
        _moveDuration = duration;
    }
    
    
    // Move the agent from its current position by "delta" in "duration" seconds
    void View::moveBy(const ichigo::Point &delta, float duration)
    {
        // Calculate target
        Point target = getPosition() + delta;
        
        // Move to target
        moveTo(target, duration);
    }
    
    
    // Stop the agent moving
    void View::stopMoving()
    {
        _isMoving = false;
    }
    
    
    // Sets the position of the view
    void View::setPosition(const ichigo::Point &position)
    {
        _position = position;
    }
    
    
    // Returns the position of the vuew
    const Point &View::getPosition()
    {
        return _position;
    }
    
    
    // Sets the scale of the view
    void View::setScale(float scale)
    {
        _scale = scale;
    }
    
    
    // Returns the scale of the viewr
    float View::getScale()
    {
        return _scale;
    }
    
    
    // Sets the angle (rotation) of the view
    void View::setAngle(float angle)
    {
        _angle = angle;
    }
    
    
    // Returns the angle (rotation) of the view
    float View::getAngle()
    {
        return _angle;
    }
    
    
    // Sets the z-order of this layer
    void View::setZOrder(int zOrder)
    {
        _zOrder = zOrder;
    }
    
    
    // Returns the z-order of this layer
    int View::getZOrder()
    {
        return _zOrder;
    }
    
    
    // Returns a queue containing the an entry of every object's z-order, from the director to the current agent
    void View::getZOrderPath(std::queue<int> &path)
    {
        // Recursivly get the path of all parents to this agent
        Agent *parent = _agent->getParent();
        if (parent && parent->getView())
        {
            parent->getView()->getZOrderPath(path);
        }
        
        // Add self to queue
        path.push(_zOrder);
    }
    
    
    // Sets the visibility of the view
    void View::setVisible(bool isVisible)
    {
        _isVisible = isVisible;
    }
    
    
    // Returns whether or not the view is visible
    bool View::isVisible()
    {
        return _isVisible;
    }
    
    
    // Gets a position on screen where a touch has been occored and returns true if the touch falls within the bound
    // of this view or its children. The bound checking itself is irtual and should be implemented according to view type
    bool View::isTouched(const ichigo::Point &touchPos)
    {
        // Check self
        bool retVal = isScreenPointInside(touchPos);
        
        // If not inside this actor, check children recursively
        if (!retVal)
        {
            AgentList &children = _agent->getChildren();
            for (AgentList::iterator it = children.begin(); it != children.end() && !retVal; it++)
            {
                View *childView = it->second->getView();
                retVal = childView->isTouched(touchPos);
            }
        }
        
        return retVal;
    }
    
    
    // Returns the position of the actor in pixels on the screen
    Point View::getPositionOnScreen()
    {
        return convertLocalToScreen(_position);
    }
    
    
    // Returns true if a point in screen coordinates is within the bounds of the view
    bool View::isScreenPointInside(const ichigo::Point &screenPoint)
    {
        return true;
    }
    
    
    // Returns view's real scale (after taking into account all of the ancestors)
    float View::getWorldScale()
    {
        float worldScale = 1;
        
        // Find screen position of actor's center
        Point screenPos = getPositionOnScreen();
            
        // Find screen position of a point at distance 1 from the center
        Point edgePoint = convertLocalToScreen(Point(_position.x + 1, _position.y));
            
        // Real world scale is the ratio between the on-screen radius and _radius
        worldScale = screenPos.distanceTo(edgePoint);
            
        // Now we have the world scale of the parent. Multiply by local scale
        worldScale *= _scale;
        
        return worldScale;
    }
    
    
    Rect View::getBoundingBox() {
        return (Rect(0.0f,0.0f,0.0f,0.0f));
    }
    
    // Returns the agent of this view
    Agent *View::getAgent()
    {
        return _agent;
    }
    
    
    // Returns the view's type
    std::string View::getType()
    {
        return _type;
    }
}
