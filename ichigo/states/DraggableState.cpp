#include "DraggableState.h"
#include "DraggingState.h"
#include "ichigo.h"
#include <iostream>

namespace ichigo {    
        
    DraggableState::DraggableState() {
        // My event table
        _eventCallbacks["OnTouchStarted"] = std::tr1::bind(&DraggableState::onTouchBegan, this, _1);
        
        _name = "Draggable";
    }
    
    
    DraggableState::~DraggableState() {
        std::cout << "DraggableState destroyed" << std::endl;
    }
    
    
    // Callback for when a touch has started
    void DraggableState::onTouchBegan(Agent* director) {
        
        View *view = _agent->getView();
        
        // Go over all current touches
        TouchList &touches = ((Director *)director)->getTouchList();
        for (TouchList::iterator it = touches.begin(); it != touches.end(); it++)
        {
            // Check that this touch wasn't handled already by an agent higher in the z-order, and that the touch is within bounds
            if (!it->second->wasHandled() && view->isTouched(it->second->getPos()))
            {
                // Drag detected, go to dragging state and give it the touchID to follow. It also needs to know the name of
                // this state, to return to it once the dragging has ended
                DraggingState *nextState = (DraggingState *)_agent->getFSM()->transitionTo("Dragging");
                nextState->setDraggingTouchID(it->first);
                nextState->setIdleStateName(getName());
                
                // Set the touch offset, so the point where the agent was touched will remain under the user's finger
                Point touchOffset = view->getPositionOnScreen() - it->second->getPos();
                nextState->setTouchOffset(touchOffset);
                
                // Mark this touch as handled, so other agents under this one don't use it too
                it->second->markAsHandled();
            }      
        }
    }
}