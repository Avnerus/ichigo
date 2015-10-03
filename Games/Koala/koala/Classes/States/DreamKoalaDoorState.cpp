#include "DreamKoalaDoorState.h"
#include "DreamKoala.h"
#include "Office.h"

#include "SpriteActorView.h"
#include "DataManager.h"
#include "Animation.h"
#include "Director.h"
#include "Scene.h"


namespace koala
{
    DreamKoalaDoorState::DreamKoalaDoorState()
    {
        _name = "door";
        
        _koala = NULL;
        _office = NULL;
        
        _eventCallbacks["ANIM_OVER_in"] = std::tr1::bind(&DreamKoalaDoorState::onInDoor, this, _1);
        _eventCallbacks["ANIM_OVER_out"] = std::tr1::bind(&DreamKoalaDoorState::onOutOfDoor, this, _1);
    }
    
    
    DreamKoalaDoorState::~DreamKoalaDoorState()
    {
        
    }
    
    
    // Called to init state
    void DreamKoalaDoorState::onEnter()
    {
        FSMState::onEnter();
        
        if (!_koala)
        {
            _koala = (DreamKoala *)_agent;
        }
        if (!_office)
        {
            _office = (Office *)ichigo::Director::getInstance()->getCurrentScene()->findByName("office");
        }
        
        // This should be moved elsewhere if door animation is added
        walkIntoDoor();
    }
    
    
    // Animate koala walking into door
    void DreamKoalaDoorState::walkIntoDoor()
    {
        ichigo::SpriteActorView *koalaView = (ichigo::SpriteActorView *)_koala->getView();
        koalaView->playAnimation("in");
    }
    
    
    // Called when koala finished walking into the door
    void DreamKoalaDoorState::onInDoor(ichigo::Agent *agent)
    {
        // Switch to new area
        ichigo::Point spawnPos = _office->enterPortal();
        
        // Position koala at new door
        _koala->setFloor(_office->getFloorForTilePos(spawnPos.y));
        ichigo::SpriteActorView *koalaView = (ichigo::SpriteActorView *)_koala->getView();
        spawnPos.x += CONST_FLOAT("DKOALA_DOOR_X");
        spawnPos.y += CONST_FLOAT("DKOALA_DOOR_INSIDE_Y");
        koalaView->setPosition(spawnPos);
        
        // Walk into new room
        koalaView->playAnimation("out");
    }
    
    
    // Called when koala finished walking out of the door in the new room
    void DreamKoalaDoorState::onOutOfDoor(ichigo::Agent *agent)
    {
        // Finished entering a new room
        _koala->stopWalking();
        _koala->doorEntered();
        _koala->setTargetX(_koala->getPosX());
        _koala->setTargetFloor(_koala->getFloor());
        _koala->setDir(DKD_OUT);
        _koala->getFSM()->transitionTo("stand");
    }
}
