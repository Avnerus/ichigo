#include "SafeIdleState.h"
#include "SpriteActorView.h"
#include "Director.h"
#include "Scene.h"


namespace it
{
    SafeIdleState::SafeIdleState()
    {
        _eventCallbacks["BUTTON_CLICK_start"] = std::tr1::bind(&SafeIdleState::onStartButtonPressed, this, _1);
        _eventCallbacks["CanRestart"] = std::tr1::bind(&SafeIdleState::onCanRestart, this, _1);
        
        _name = "Idle";
        _startButton = NULL;
        _hitCounter = NULL;
        _tryAgain = NULL;
    }
    
    
    // Gets called by a timer event after the "try again" OSF was displayed for a few seconds
    void SafeIdleState::onCanRestart(ichigo::Agent *director)
    {
        // Hide the Try Again OSF
        if (_tryAgain)
        {
            _tryAgain->getView()->setVisible(false);
        }
        
        // Make sure the start button is showing
        if (_startButton)
        {
            _startButton->getView()->setVisible(true);
        }
        
        // Hide the "ouch" thingy
        ichigo::Director::getInstance()->getCurrentScene()->findByName("ouch")->getView()->setVisible(false);
    }
    
    
    // Gets called when the start button is clicked
    void SafeIdleState::onStartButtonPressed(ichigo::Agent *button)
    {
        // Only react if this button is visible
        if (button->getView()->isVisible())
        {
            // If we don't have it yet, save a pointer to the start button
            if (!_startButton)
            {
                _startButton = button;
            }
        
            // First time we will want to save a pointer to the hit counter
            if (!_hitCounter)
            {
                _hitCounter = ichigo::Director::getInstance()->getCurrentScene()->findByName("hits");
            }
        
            // First time we will want to save a pointer to the Try Again OSF
            if (!_tryAgain)
            {
                _tryAgain = ichigo::Director::getInstance()->getCurrentScene()->findByName("tryAgain");
            }
       
            // Game should start, update HUD
            _startButton->getView()->setVisible(false);
            ((ichigo::SpriteActorView *)_hitCounter->getView())->playAnimation("hit0");
        
            // Start playing
            _agent->getFSM()->transitionTo("Active");
        }
    }
}