#include "Agent.h"
#include "CharacterJumpingState.h"
#include "SpriteActorView.h"
#include "DataManager.h"
#include "Utils.h"

#include <cmath>


namespace it
{
    CharacterJumpingState::CharacterJumpingState()
    {
        _name = "Jump";
    }
    
    
    // Called when the state is entered. Change character animation to jump
    void CharacterJumpingState::onEnter()
    {
        ichigo::FSMState::onEnter();
        
        ((ichigo::SpriteActorView *)_agent->getView())->playAnimation("jump");
        
        _initialPos = ((ichigo::SpriteActorView *)_agent->getView())->getPosition();
        _jumpPhase = 0;
    }
    
    
    // Called each frame
    void CharacterJumpingState::onUpdate(float dt)
    {
        ichigo::FSMState::onUpdate(dt);
        
        // We want the jump to last half a second
        _jumpPhase += 180.0f * dt * CONST_FLOAT("JUMP_SPEED");
        float jumpHeight = sinf(ichigo::Utils::deg2rad(_jumpPhase)) * CONST_FLOAT("JUMP_HEIGHT");
        
        // The jump ends when the character has got back to the floor
        if (jumpHeight <= 0)
        {
            jumpHeight = 0;
            _agent->getFSM()->transitionTo("Stand");
        }
        
        // Set character at jump height
        ((ichigo::SpriteActorView *)_agent->getView())->setPosition(_initialPos + ichigo::Point(0, jumpHeight));
    }
}
