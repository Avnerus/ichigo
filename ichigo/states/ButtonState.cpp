#include "ButtonState.h"
#include "Director.h"
#include "TouchPoint.h"
#include "EventManager.h"
#include "SpriteActorView.h"


namespace ichigo 
{    
    ButtonState::ButtonState() 
    {
        // My event table
        _eventCallbacks["OnTouchStarted"] = std::tr1::bind(&ButtonState::onTouchBegan, this, _1);
        _eventCallbacks["OnTouchMoved"] = std::tr1::bind(&ButtonState::onTouchMoved, this, _1);
        _eventCallbacks["OnTouchEnded"] = std::tr1::bind(&ButtonState::onTouchEnded, this, _1);
        
        _name = "Button";
        _isPressed = false;
        _touchID = 0;
    }
    
    
    ButtonState::~ButtonState() 
    {

    }
    
    
    // True when the button is being pressed down 
    bool ButtonState::isPressed()
    {
        return _isPressed;
    }
    
    
    // Sets the name of the animation for when the button is unpressed
    void ButtonState::setUpAnimation(const std::string &animationName)
    {
        _upAnimation = animationName;
    }
    
    
    // Sets the name of the animation for when the button is pressed
    void ButtonState::setDownAnimation(const std::string &animationName)
    {
        _downAnimation = animationName;
    }
    
    
    // Callback function for touch starting.
    void ButtonState::onTouchBegan(Agent *director)
    {
        View *view = _agent->getView();
        
        // Go over all current touches
        TouchList &touches = ((Director *)director)->getTouchList();
        for (TouchList::iterator it = touches.begin(); it != touches.end(); it++)
        {
            // Check that this touch wasn't handled already by an agent higher in the z-order, and that the touch is within bounds
            if (!it->second->wasHandled() && view->isTouched(it->second->getPos()))
            {
                // Press started!
                setPressed(true);
                
                // Mark this touch as handled, so other agents under this one don't use it too
                it->second->markAsHandled();
                _touchID = it->first;
            }      
        }
    }
    
    
    // Callback function for touch moving
    void ButtonState::onTouchMoved(ichigo::Agent *director)
    {
        TouchPoint *tp = ((Director *)director)->getTouchPoint(_touchID);
        
        // If we got no touch point, touch has ended, we need to forget it
        if (!tp)
        {
            setPressed(false);
            _touchID = 0;
        }
        else
        {
            if (_agent->getView()->isTouched(tp->getPos()))
            {
                if (tp->hasEnded())
                {
                    // Pressing has ended within button bounds, this is a successful click. We fire an event containing the name of the
                    // agent
                    EventManager::getInstance()->publish("BUTTON_CLICK_" + _agent->getName(), _agent);
                    setPressed(false);
                    _touchID = 0;
                }
                else
                {
                    // Button still pressed down
                    setPressed(true);
                }
            }
            else
            {
                if (tp->hasEnded())
                {
                    // Press has been released, and outside the button's bounds. Press canceled.
                    setPressed(false);
                    _touchID = 0;
                }
                else
                {
                    // User is still touching the screen, but out of bounds. Mark this button as unpressed until the user returns
                    // to button bounds
                   setPressed(false);
                }
            }
        }
    }
    
    
    // Callback function for touch ending
    void ButtonState::onTouchEnded(ichigo::Agent *director)
    {
        onTouchMoved(director);
    }
    
    
    // Sets the button to the pressed or unpressed state. Notice, this agent needs to be a spite
    void ButtonState::setPressed(bool pressed)
    {
        _isPressed = pressed;
        
        ((SpriteActorView *)_agent->getView())->playAnimation(_isPressed ? _downAnimation : _upAnimation);
    }
}