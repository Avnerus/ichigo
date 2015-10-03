#include "CharacterState.h"
#include "Director.h"
#include "TouchPoint.h"
#include "EventManager.h"
#include "SpriteActorView.h"


namespace ichigo  {
    
    CharacterState::CharacterState()  {
        // My event table
        _eventCallbacks["OnTouchStarted"] = std::tr1::bind(&CharacterState::onTouchStarted, this, _1);
        _touchID = 0;
        _name = "Character";
    }
    
    
    CharacterState::~CharacterState() {

    }
    
    
    void CharacterState::init() {
        _character = (Character *)_agent;
        _characterView = (SpriteActorView *)_agent->getView();
    }
   
    
    // Callback function for touch starting.
    void CharacterState::onTouchStarted(Agent *director)
    {
        
        // std::cout << "CharacterState - On touch started" << std::endl;
        
        // Go over all current touches
        TouchList &touches = ((Director *)director)->getTouchList();
        for (TouchList::iterator it = touches.begin(); it != touches.end(); it++)
        {
            // Check that this touch wasn't handled already by an agent higher in the z-order, and that the touch is within bounds
            if (!it->second->wasHandled() && _characterView->isTouched(it->second->getPos()))
            {
                // Touch!
                _character->touch();
                
                
                // Mark this touch as handled, so other agents under this one don't use it too
                it->second->markAsHandled();
                _touchID = it->first;
            } 
        }
    }
}