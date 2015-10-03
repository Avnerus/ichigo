#include "DreamKoalaStandState.h"
#include "DreamKoala.h"
#include "SpriteActorView.h"
#include "DataManager.h"
#include "Director.h"
#include "Office.h"


namespace koala
{
    DreamKoalaStandState::DreamKoalaStandState()
    {
        _name = "stand";
        
        _koala = NULL;
        _isTurning = false;
        _twoPhaseTurn = false;

        _eventCallbacks["ANIM_OVER_l2r"] = std::tr1::bind(&DreamKoalaStandState::onTurnRightComplete, this, _1);
        _eventCallbacks["ANIM_OVER_i2r"] = std::tr1::bind(&DreamKoalaStandState::onTurnRightComplete, this, _1);
        _eventCallbacks["ANIM_OVER_o2r"] = std::tr1::bind(&DreamKoalaStandState::onTurnRightComplete, this, _1);
        _eventCallbacks["ANIM_OVER_r2l"] = std::tr1::bind(&DreamKoalaStandState::onTurnLeftComplete, this, _1);
        _eventCallbacks["ANIM_OVER_i2l"] = std::tr1::bind(&DreamKoalaStandState::onTurnLeftComplete, this, _1);
        _eventCallbacks["ANIM_OVER_o2l"] = std::tr1::bind(&DreamKoalaStandState::onTurnLeftComplete, this, _1);
        _eventCallbacks["ANIM_OVER_r2i"] = std::tr1::bind(&DreamKoalaStandState::onTurnInComplete, this, _1);
        _eventCallbacks["ANIM_OVER_l2i"] = std::tr1::bind(&DreamKoalaStandState::onTurnInComplete, this, _1);
        _eventCallbacks["ANIM_OVER_l2o"] = std::tr1::bind(&DreamKoalaStandState::onTurnOutComplete, this, _1);
        _eventCallbacks["ANIM_OVER_r2o"] = std::tr1::bind(&DreamKoalaStandState::onTurnOutComplete, this, _1);
    }
    
    
    DreamKoalaStandState::~DreamKoalaStandState()
    {
        
    }
    
    
    // First initialization
    void DreamKoalaStandState::onEnter()
    {
        ichigo::CharacterState::onEnter();
        
        if (!_koala)
        {
            _koala = (DreamKoala *)_agent;
            
            // Tell koala its original position
            float koalaCurrX = _koala->getView()->getPosition().x;
            Office *office = (Office *)ichigo::Director::getInstance()->findByName("office");
            int koalaCurrFloor = office->getFloorForTilePos(_koala->getView()->getPosition().y);
            
            _koala->setPosX(koalaCurrX);
            _koala->setTargetX(koalaCurrX);
            _koala->setDir(DKD_RIGHT);
            _koala->setFloor(koalaCurrFloor);
            _koala->setTargetFloor(koalaCurrFloor);
        }
    }
    
    
    // Called on each frame
    void DreamKoalaStandState::onUpdate(float dt)
    {
        ichigo::CharacterState::onUpdate(dt);
        
        if (!_isTurning)
        {
            // Check if there is a difference between current position and target position
            float distToTarget = _koala->getPosX() - _koala->getTargetX();
        
            if (distToTarget < -CONST_FLOAT("DKOALA_MOVE_THRESHOLD"))
            {
                // Target is at right of koala. Turn towards it and walk there.
                if (_koala->getDir() != DKD_RIGHT)
                {
                    turnRight();
                }
                else
                {
                    walk();
                }
            }
            else if (distToTarget > CONST_FLOAT("DKOALA_MOVE_THRESHOLD"))
            {
                // Target is at left of koala. Turn towards is and walk there.
                if (_koala->getDir() == DKD_LEFT)
                {
                    walk();
                }
                else 
                {
                    turnLeft();
                }
            }
            else if (_koala->getFloor() != _koala->getTargetFloor())
            {
                // Koala needs to go to a different floor. Turn towards lift and switch to lift state
                if (_koala->getDir() != DKD_IN)
                {
                    turnIn();
                }
                else
                {
                    startLiftSequence();
                }
            }
            else if (_koala->isEnteringDoor())
            {
                // Koala needs to enter the door it is currently in front of
                if (_koala->getDir() != DKD_IN)
                {
                    turnIn();
                }
                else
                {
                    goIntoDoor();
                }
            }
            else if (_koala->shouldInteractWithObject())
            {
                // Check if koala needs to turn before the interaction
                DreamKoalaDirection dirForInteraction = _koala->getInteractionDirection();
                if (_koala->getDir() == dirForInteraction)
                {
                    useObject();
                }
                else if (dirForInteraction == DKD_IN)
                {
                    turnIn();
                }
                else if (dirForInteraction == DKD_OUT)
                {
                    turnOut();
                }
            }
        }
    }
    
    
    // Starts turning animation to left
    void DreamKoalaStandState::turnLeft()
    {
        _twoPhaseTurn = false;
        
        switch (_koala->getDir())
        {
            case DKD_RIGHT:
                ((ichigo::SpriteActorView *)_koala->getView())->playAnimation("r2l");
                break;
                
            case DKD_IN:
                ((ichigo::SpriteActorView *)_koala->getView())->playAnimation("i2l");
                
                // Make sure no lift action withstanding
                _koala->setTargetFloor(_koala->getFloor());
                break;
                
            case DKD_OUT:
                ((ichigo::SpriteActorView *)_koala->getView())->playAnimation("o2l");
                break;
                
            default:
                break;
        }
        
        _koala->setDir(DKD_LEFT);
        _isTurning = true;
    }
    
    
    // Starts turning animation to right
    void DreamKoalaStandState::turnRight()
    {
        _twoPhaseTurn = false;
        
        switch (_koala->getDir())
        {
            case DKD_LEFT:
                ((ichigo::SpriteActorView *)_koala->getView())->playAnimation("l2r");
                break;
                
            case DKD_IN:
                ((ichigo::SpriteActorView *)_koala->getView())->playAnimation("i2r");
                
                // Make sure no lift action withstanding
                _koala->setTargetFloor(_koala->getFloor());
                break;
                
            case DKD_OUT:
                ((ichigo::SpriteActorView *)_koala->getView())->playAnimation("o2r");
                break;
                
            default:
                break;
        }
        
        _koala->setDir(DKD_RIGHT);
        _isTurning = true;
    }
    
    
    // Starts turning animation to face wall
    void DreamKoalaStandState::turnIn()
    {
        _twoPhaseTurn = false;
        
        switch (_koala->getDir())
        {
            case DKD_LEFT:
                ((ichigo::SpriteActorView *)_koala->getView())->playAnimation("l2i");
                break;
                
            case DKD_RIGHT:
                ((ichigo::SpriteActorView *)_koala->getView())->playAnimation("r2i");
                break;
                
            case DKD_OUT:
                ((ichigo::SpriteActorView *)_koala->getView())->playAnimation("o2r");
                _twoPhaseTurn = true;
                break;
                
            default:
                break;
        }
        
        _koala->setDir(DKD_IN);
        _isTurning = true;
    }
    
    
    // Start turning animation to face camera
    void DreamKoalaStandState::turnOut()
    {
        _twoPhaseTurn = false;
        
        switch (_koala->getDir())
        {
            case DKD_LEFT:
                ((ichigo::SpriteActorView *)_koala->getView())->playAnimation("l2o");
                break;
                
            case DKD_RIGHT:
                ((ichigo::SpriteActorView *)_koala->getView())->playAnimation("r2o");
                break;
                
            case DKD_IN:
                ((ichigo::SpriteActorView *)_koala->getView())->playAnimation("i2r");
                _twoPhaseTurn = true;
                break;
                
            default:
                break;
        }
        
        _koala->setDir(DKD_OUT);
        _isTurning = true;
    }
    
    
    // Starts walking left
    void DreamKoalaStandState::walk()
    {
        _koala->walkToTargetX();
        _agent->getFSM()->transitionTo("walk");
    }
    
    
    // Start lift animation and state
    void DreamKoalaStandState::startLiftSequence()
    {
        ((ichigo::SpriteActorView *)_koala->getView())->playAnimation("standIn");
        _agent->getFSM()->transitionTo("lift");
    }
    
    
    // Start door animation and state
    void DreamKoalaStandState::goIntoDoor()
    {
        ((ichigo::SpriteActorView *)_koala->getView())->playAnimation("standIn");
        _agent->getFSM()->transitionTo("door");
    }
    
    
    // Interact with an object
    void DreamKoalaStandState::useObject()
    {
        _koala->say("Yo dawg, this is a " + _koala->getInteractionType());
        _koala->endObjectInteraction();
    }
    
    
    // Called when animation of turning to the right ends
    void DreamKoalaStandState::onTurnRightComplete(ichigo::Agent *agnet)
    {
        if (!_twoPhaseTurn)
        {
            // Mark turning has stopped so onUpdate can take control again
            _isTurning = false;
        }
        else
        {
            // Turning from out to in (or opposite), continue second part of turn
            DreamKoalaDirection destDirection = _koala->getDir();
            _koala->setDir(DKD_RIGHT);
            if (destDirection == DKD_OUT)
            {
                turnOut();
            }
            else if (destDirection == DKD_IN)
            {
                turnIn();
            }
        }
    }
    
    
    // Called when animation of turning to the left ends
    void DreamKoalaStandState::onTurnLeftComplete(ichigo::Agent *agent)
    {
        // Marking turning has stopped so onUpdate can take control again
        _isTurning = false;
    }
    
    
    // Called when animation of turning towards the wall ended
    void DreamKoalaStandState::onTurnInComplete(ichigo::Agent *agent)
    {
        // Marking turning has stopped so onUpdate can take control again
        _isTurning = false;
    }
    
    
    // Called when animation of turning towards the camera ended
    void DreamKoalaStandState::onTurnOutComplete(ichigo::Agent *agent)
    {
        // Marking turning has stopped so onUpdate can take control again
        _isTurning = false;
    }
}
