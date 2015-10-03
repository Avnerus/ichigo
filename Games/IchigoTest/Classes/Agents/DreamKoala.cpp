#include "DreamKoala.h"
#include "DreamKoalaStandState.h"
#include "DreamKoalaWalkState.h"
#include "DreamKoalaLiftState.h"

#include "SpriteActorView.h"
#include "DataManager.h"
#include <cmath>

namespace it
{
    DreamKoala::DreamKoala()
    {
        _targetX = 0;
        _floor = 0;
        _dir = DKD_RIGHT;
        
        _fsm.addState(new DreamKoalaStandState(), true);
        _fsm.addState(new DreamKoalaWalkState(), false);
        _fsm.addState(new DreamKoalaLiftState(), false);
    }
    
    
    DreamKoala::~DreamKoala()
    {
        
    }
    
    
    // Starts walking to position X on the current floor
    void DreamKoala::setTargetX(float x)
    {
        // Only move if the new point isn't too close
        if (fabs(x - _targetX) >= CONST_FLOAT("DKOALA_MOVE_THRESHOLD"))
        {
            _targetX = x;
        }
    }
    
    
    // Returns the taget X coordinate the koala is walking to
    float DreamKoala::getTargetX()
    {
        return _targetX;
    }
    
    
    // Sets the position of the koala at current floor, X position (immediate)
    void DreamKoala::setPosX(float xPos)
    {
        _view->setPosition(ichigo::Point(xPos, _view->getPosition().y));
    }
    
    
    // Returns the current X position of the koala
    float DreamKoala::getPosX()
    {
        return _view->getPosition().x;
    }
    
    
    // Sets the floor the koala is standing on. This does not affect the animation, but is called by the animation
    void DreamKoala::setFloor(int floor)
    {
        _floor = floor;
    }
    
    
    // Returns the floor number the koala is currently on
    int DreamKoala::getFloor()
    {
        return _floor;
    }
    
    
    // Sets the floor the koala is moving to
    void DreamKoala::setTargetFloor(int floor)
    {
        _targetFloor = floor;
    }
    
    
    // Returns the koala's target floor
    int DreamKoala::getTargetFloor()
    {
        return _targetFloor;
    }
    
    
    // Sets the direction the koala is facing. This will not affect the animation, it is actually called by the animation
    void DreamKoala::setDir(it::DreamKoalaDirection dir)
    {
        _dir = dir;
    }
    
    
    // Returns true if the koala is facing the lft direction, false if facing right
    DreamKoalaDirection DreamKoala::getDir()
    {
        return _dir;
    }
    
    
    // Starts moving and animating the koala towards targetX
    void DreamKoala::walkToTargetX()
    {
        // Stop previous movement
        ichigo::SpriteActorView *koalaView = (ichigo::SpriteActorView *)getView();
        koalaView->stopMoving();
        
        // Only move if it is worth it
        if (fabs(_targetX - getPosX()) > CONST_FLOAT("DKOALA_MOVE_THRESHOLD"))
        {
            ichigo::Point target(_targetX, _view->getPosition().y);
            
            // Assuming the koala has already turned to the correct direction
            if (_dir == DKD_LEFT)
            {
                koalaView->playAndMoveTo("left", target, CONST_FLOAT("DKOALA_WALK_SPEED"));
            }
            else
            {
                koalaView->playAndMoveTo("right", target, CONST_FLOAT("DKOALA_WALK_SPEED"));
            }
        }
        else
        {
            // To close to move, just set this as target
            setTargetX(getPosX());
            koalaView->playAnimation(_dir == DKD_LEFT ? "standLeft" : "standRight");
            _fsm.transitionTo("stand");
        }
    }
    
    
    // Stop walking
    void DreamKoala::stopWalking()
    {
        ((ichigo::SpriteActorView *)getView())->stopMoving();
    }
    
    
    // Returns true if the koala is currently not walking (standing = staying at one position, even if turning at the same time)
    bool DreamKoala::isStanding()
    {
        return _fsm.getCurrentState()->getName() == "stand";
    }
}
