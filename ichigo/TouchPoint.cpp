#include "TouchPoint.h"


namespace ichigo
{
    TouchPoint::TouchPoint(int touchID /* = 0 */, float x /* = 0 */, float y /* = 0 */)
    : _touchID(touchID), _pos(Point(x, y)), _handled(false), _hasEnded(false)
    {
    }
    
    
    TouchPoint::~TouchPoint()
    {
    }
    
    
    int TouchPoint::getID()
    {
        return _touchID;
    }
    
    
    void TouchPoint::setPos(const Point &pos)
    {
        _prevPos = _pos;
        _pos = pos;
    }
    
    
    void TouchPoint::setPos(float x, float y)
    {
        _prevPos = _pos;
        _pos.x = x;
        _pos.y = y;
    }
    
    
    const Point &TouchPoint::getPos()
    {
        return _pos;
    }
    
    
    const Point &TouchPoint::getPrevPos()
    {
        return _prevPos;
    }
    
    
    // A state can mark a touch as handled after dealing with the event to signal to other states there is no need to further process it.
    void TouchPoint::markAsHandled(bool handled /* = true */)
    {
        _handled = handled;
    }
    
    
    // Returns true if this touch has been marked as handled by another state
    bool TouchPoint::wasHandled()
    {
        return _handled;
    }
    
    
    // When a touch has ended, it is passed to the events, so we need to mark it as an ended touch.
    // It will only be removed from the list of active touches once the event has been handled
    void TouchPoint::markAsEnded()
    {
        _hasEnded = true;
    }
    
    
    bool TouchPoint::hasEnded()
    {
        return _hasEnded;
    }
}
