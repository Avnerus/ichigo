#include "DraggingState.h"
#include "ichigo.h"

#include <iostream>


namespace ichigo {
        
    DraggingState::DraggingState() 
    : _boundsMin(-2000, -2000), _boundsMax(2000, 2000)
    {
         _eventCallbacks["OnTouchMoved"] = std::tr1::bind(&DraggingState::onTouchMoved, this, _1);        
         _eventCallbacks["OnTouchEnded"] = std::tr1::bind(&DraggingState::onTouchEnded, this, _1);  
        
        _name = "Dragging";
        _draggingTouchID = 0;
    }
    
    
    DraggingState::~DraggingState() {
        std::cout << "Dragging State destroyed" << std::endl;
    }
    
    
    void DraggingState::setIdleStateName(std::string name) {
        _idleStateName = name;
    }
    
    
    void DraggingState::setDraggingTouchID(int id)
    {
        _draggingTouchID = id;
    }
    
    
    // Touch offset is the point where the touch occurred. We need to keep this point under the user's finger
    void DraggingState::setTouchOffset(const ichigo::Point &touchOffset)
    {
        _touchOffset = touchOffset;
    }
    
    
    // Sets the dargging bounds the agent won't move outside of
    void DraggingState::setPositionBounds(float minX, float maxX, float minY, float maxY)
    {
        _boundsMin.x = minX;
        _boundsMin.y = minY;

        _boundsMax.x = maxX;
        _boundsMax.y = maxY;
    }

    
    // Callback for when touch has moved
    void DraggingState::onTouchMoved(Agent* director) {
        
        // Get the current position of the touch
        TouchPoint *touchPoint = ((Director *)director)->getTouchPoint(_draggingTouchID);
        
        if (touchPoint)
        {
            moveActorToTouchPosition(touchPoint);
        }
        else
        {
            // Can't find touch, end the dragging
            endDrag();
        }
    }
    
    
    // Callback for when touch has ended
    void DraggingState::onTouchEnded(Agent* director) {
        
        // Check if the ending touch is the one dragging this agent
        TouchPoint *touchPoint = ((Director *)director)->getTouchPoint(_draggingTouchID);
        
        if (!touchPoint || touchPoint->hasEnded())
        {
            // Move to final position and end the drag
            moveActorToTouchPosition(((Director *)director)->getTouchPoint(_draggingTouchID));
            endDrag();
        }
    }
    
    
    // Does the actual moving
    void DraggingState::moveActorToTouchPosition(TouchPoint *touchPoint)
    {
        if (touchPoint)
        {
            View *view = _agent->getView();
            Point newLocalPos = view->convertScreenToLocal(touchPoint->getPos() + _touchOffset);
            
            // Check bounds
            if (newLocalPos.x < _boundsMin.x)
            {
                newLocalPos.x = _boundsMin.x;
            }
            if (newLocalPos.y < _boundsMin.y)
            {
                newLocalPos.y = _boundsMin.y;
            }
            if (newLocalPos.x > _boundsMax.x)
            {
                newLocalPos.x = _boundsMax.x;
            }
            if (newLocalPos.y > _boundsMax.y)
            {
                newLocalPos.y = _boundsMax.y;
            }
            
            view->setPosition(newLocalPos);
        }
    }
    
    
    // End the dragging
    void DraggingState::endDrag()
    {
        _draggingTouchID = 0;
        _agent->getFSM()->transitionTo(_idleStateName);
    }
}