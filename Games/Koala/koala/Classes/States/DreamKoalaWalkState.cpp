#include "DreamKoalaWalkState.h"
#include "DreamKoala.h"
#include "DataManager.h"
#include "SpriteActorView.h"

namespace koala
{
    DreamKoalaWalkState::DreamKoalaWalkState()
    {
        _name = "Walk";
        
        _koala = NULL;

        _eventCallbacks["ANIM_OVER_left"] = std::tr1::bind(&DreamKoalaWalkState::onLeftWalkEnded, this, _1);
        _eventCallbacks["ANIM_OVER_right"] = std::tr1::bind(&DreamKoalaWalkState::onRightWalkEnded, this, _1);
    }
    
    
    DreamKoalaWalkState::~DreamKoalaWalkState()
    {
        
    }
    
    
    // Called when starting the walk state
    void DreamKoalaWalkState::onEnter()
    {
        FSMState::onEnter();
        
        // Initialize data
        if (!_koala)
        {
            _koala = (DreamKoala *)_agent;
        }
    }
    
    
    // Called every time left animation walk loops
    void DreamKoalaWalkState::onLeftWalkEnded(ichigo::Agent *agnet)
    {
        // Have we reached out target or new target moved to our right?
        if (_koala->getPosX() <= _koala->getTargetX())
        {
            // If so, stand in place
            ((ichigo::SpriteActorView *)_koala->getView())->playAnimation("standLeft");
            _koala->getFSM()->transitionTo("stand");
            _koala->stopWalking();
        }
        else
        {
            // Walk to target (we call this again because target might have moved to new position which is still to the left)
            _koala->walkToTargetX();
        }
    }
    
    
    // Called every time right animation walk loops
    void DreamKoalaWalkState::onRightWalkEnded(ichigo::Agent *agent)
    {
        // Have we reached out target or new target moved to our left?
        if (_koala->getPosX() >= _koala->getTargetX())
        {
            // If so, stand in place
            ((ichigo::SpriteActorView *)_koala->getView())->playAnimation("standRight");
            _koala->getFSM()->transitionTo("stand");
            _koala->stopWalking();
        }
        else
        {
            // Walk to target (we call this again because target might have moved to new position which is still to the right)
            _koala->walkToTargetX();
        }        
    }
}
