#include "StretchableState.h"
#include "StretchingState.h"
#include "TouchPoint.h"
#include "Director.h"
#include "View.h"


namespace ichigo
{
    StretchableState::StretchableState() 
    {
        _eventCallbacks["OnTouchStarted"] = std::tr1::bind(&StretchableState::onTouchBegan, this, _1);
        
        _name = "Stretchable";
        _stretchingStateName = "Stretching";
    }    
    
    
    StretchableState::~StretchableState() {
    }
    
    
    // Callback for when a touch has started
    void StretchableState::onTouchBegan(ichigo::Agent *director)
    {
        View *view = _agent->getView();
        
        // Go over all current touches
        TouchList &touches = ((Director *)director)->getTouchList();
        // std::cout << "Stretchable for " << _agent->getType() << " touches: " << touches.size() << std::endl;
        for (TouchList::iterator it = touches.begin(); it != touches.end(); it++)
        {
            // Check that this touch isn't handled by some other agent, and that it is within this agent's bounds
            if (!it->second->wasHandled() && !it->second->hasEnded() && view->isTouched(it->second->getPos()))
            {
                // Go to active state and feed it with the data of this touch
                StretchingState *nextState = (StretchingState *)_agent->getFSM()->transitionTo(_stretchingStateName);
                nextState->setIdleStateName(getName());
                nextState->addTouchPoint(it->second.get());
            }
        }
    }
}