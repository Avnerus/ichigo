#include "SafeActiveState.h"
#include "Director.h"
#include "Scene.h"
#include "Actor.h"
#include "SpriteActorView.h"
#include "DataManager.h"
#include "Utils.h"

#include <sstream>


namespace it
{
    SafeActiveState::SafeActiveState()
    {
        _eventCallbacks["CollisionReenable"] = std::tr1::bind(&SafeActiveState::enableCollisionDetection, this, _1);
        
        _name = "Active";
        _tzahiAgent = NULL;
        _hitCounter = NULL;
        _ouchAgent = NULL;
        _hits = 0;
        _canDetectCollisions = true;
        _initialSafeX = 0;
    }
    
    
    // State initialization
    void SafeActiveState::onEnter()
    {
        // The first time we want to save pointers to some agents, for quick access later
        if (!_tzahiAgent)
        {
            _tzahiAgent = ichigo::Director::getInstance()->getCurrentScene()->findByName("tzahi");
            
            if (!_ouchAgent)
            {
                _ouchAgent = _tzahiAgent->findByName("ouch");
            }
        }
        if (!_hitCounter)
        {
            _hitCounter = ichigo::Director::getInstance()->getCurrentScene()->findByName("hits");
        }
        
        // Reset hits and remember initial position of safe
        _hits = 0;
        _initialSafeX = _agent->getView()->getPosition().x;
        _canDetectCollisions = true;
    }
    
    
    // Gets called every frame. Run the safe across the screen and check for collisions
    void SafeActiveState::onUpdate(float dt)
    {
        // Update to new position. If safe arrives to end of world, restart it
        ichigo::Point safePos = _agent->getView()->getPosition();
        safePos.x += CONST_FLOAT("SAFE_SPEED") * dt;
        if (safePos.x <= CONST_FLOAT("SAFE_END_X"))
        {
            safePos.x = _initialSafeX;
        }
        _agent->getView()->setPosition(safePos);
        
        // Check for collision
        if (_canDetectCollisions && ichigo::Utils::areActorsColliding((ichigo::Actor *)_agent, (ichigo::Actor *)_tzahiAgent))
        {
            handleCollision();
        }
    }
    
    
    // A collision has been detected, handle it!
    void SafeActiveState::handleCollision()
    {
        // Tzahi goes ouch for a small while. For that while, make sure we don't detect more collisions so we don't lose
        // hits in all the next frames.
        _canDetectCollisions = false;
        _ouchAgent->getView()->setVisible(true);
        ichigo::Director::getInstance()->addTimer(_agent, "CollisionReenable", CONST_FLOAT("COLLISION_IGNORE_TIME"));
        
        // Count hits and update HUD accordingly
        _hits++;
        std::stringstream animName;
        animName << "hit" << _hits;
        ((ichigo::SpriteActorView *)_hitCounter->getView())->playAnimation(animName.str());
        
        // Game over? If so, display OSF and return to idle state
        if (_hits == CONST_INT("MAX_HITS"))
        {
            ichigo::Point safePos = _agent->getView()->getPosition();
            safePos.x = _initialSafeX;
            _agent->getView()->setPosition(safePos);
            
            ichigo::Director::getInstance()->getCurrentScene()->findByName("tryAgain")->getView()->setVisible(true);
            ichigo::Director::getInstance()->addTimer(_agent, "CanRestart", CONST_FLOAT("TRY_AGAIN_TIME"));
            
            _agent->getFSM()->transitionTo("Idle");
        }
    }
    
    
    // A while after a collision is detected, a timer calls this function to re-enable collision checking, and removed the "ouch"
    void SafeActiveState::enableCollisionDetection(ichigo::Agent *director)
    {
        _canDetectCollisions = true;
        _ouchAgent->getView()->setVisible(false);
    }
}
