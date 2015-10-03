#include "CharacterStandingState.h"
#include "SpriteActorView.h"
#include "TouchPoint.h"
#include "Director.h"


namespace it
{
    CharacterStandingState::CharacterStandingState()
    {
        _name = "Stand";
        
        _eventCallbacks["OnTouchStarted"] = std::tr1::bind(&CharacterStandingState::onTouchStarted, this, _1);
    }
    
    
    // Called when state is entered
    void CharacterStandingState::onEnter()
    {
        ichigo::FSMState::onEnter();
        
        ((ichigo::SpriteActorView *)_agent->getView())->playAnimation("stand");
    }
    
    
    // Called when a touch was detected
    void CharacterStandingState::onTouchStarted(ichigo::Agent *director)
    {
        // Go over all touches
        ichigo::TouchList &touches = ((ichigo::Director *)director)->getTouchList();
        for (ichigo::TouchList::iterator it = touches.begin(); it != touches.end(); it++)
        {
            ichigo::TouchPoint *touch = it->second.get();
            if (!touch->wasHandled() && _agent->getView()->isTouched(touch->getPos()))
            {
                touch->markAsHandled();
                _agent->getFSM()->transitionTo("Jump");
            }
        }
    }
}
