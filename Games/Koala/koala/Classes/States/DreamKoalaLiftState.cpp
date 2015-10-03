#include "DreamKoalaLiftState.h"
#include "DreamKoala.h"
#include "Office.h"

#include "SpriteActorView.h"
#include "TileMapView.h"
#include "DataManager.h"
#include "Animation.h"
#include "Director.h"
#include "Scene.h"


namespace koala
{
    DreamKoalaLiftState::DreamKoalaLiftState()
    {
        _name = "lift";
        
        _koala = NULL;
        _office = NULL;
        _isInLift = false;

        _eventCallbacks["ANIM_OVER_opening"] = std::tr1::bind(&DreamKoalaLiftState::onLiftOpened, this, _1);
        _eventCallbacks["ANIM_OVER_closing"] = std::tr1::bind(&DreamKoalaLiftState::onLiftClosed, this, _1);
        _eventCallbacks["ANIM_OVER_in"] = std::tr1::bind(&DreamKoalaLiftState::onInLift, this, _1);
        _eventCallbacks["ANIM_OVER_out"] = std::tr1::bind(&DreamKoalaLiftState::onOutLift, this, _1);
        _eventCallbacks["LiftAtFloor"] = std::tr1::bind(&DreamKoalaLiftState::onLiftAtTarget, this, _1);
    }
    
    
    DreamKoalaLiftState::~DreamKoalaLiftState()
    {
        
    }
    
    
    // Called on state init
    void DreamKoalaLiftState::onEnter()
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
        
        // Order the lift on current floor
        _office->orderLift();
    }
    
    
    // Called every frame
    void DreamKoalaLiftState::onUpdate(float dt)
    {
        FSMState::onUpdate(dt);
    }
    
    
    // Called when the lift door opened (it should always be the lift on the floor with the koala)
    void DreamKoalaLiftState::onLiftOpened(ichigo::Agent *agent)
    {
        // Going in or out?
        if (!_isInLift)
        {
            // Walk into lift
            ichigo::SpriteActorView *koalaSprite = (ichigo::SpriteActorView *)_koala->getView();
        
            // Find koala offset in lift tile
            ichigo::Point offsetInTile;
            _office->getCurrentArea()->tileMap->getTileAtPosition(_koala->getView()->getPosition().x, 
                                                                  _koala->getView()->getPosition().y, 
                                                                  &offsetInTile);
        
            // Find how much koala needs to move from current position to destination
            offsetInTile.x = CONST_FLOAT("DKOALA_LIFT_INSIDE_X") - offsetInTile.x;
            offsetInTile.y = CONST_FLOAT("DKOALA_LIFT_INSIDE_Y") - offsetInTile.y;
        
            // Move into lift
            koalaSprite->playAndMoveBy("in", offsetInTile);
 
            _isInLift = true;
        }
        else
        {
            // Walk out of lift
            ichigo::SpriteActorView *koalaSprite = (ichigo::SpriteActorView *)_koala->getView();
            
            // Put koala in front of doors
            koalaSprite->setZOrder(3);
            
            // Find koala offset in lift tile
            ichigo::Point offsetInTile;
            _office->getCurrentArea()->tileMap->getTileAtPosition(_koala->getView()->getPosition().x, 
                                                                  _koala->getView()->getPosition().y, 
                                                                  &offsetInTile);
            
            // Find how much koala needs to move from current position to destination
            offsetInTile.x = CONST_FLOAT("DKOALA_LIFT_ENTRY_X") - offsetInTile.x;
            offsetInTile.y = CONST_FLOAT("DKOALA_LIFT_ENTRY_Y") - offsetInTile.y;
            
            // Move out of lift
            koalaSprite->playAndMoveBy("out", offsetInTile);
            
            _isInLift = false;
        }
    }
    
    
    // Called when lift doors finished closing
    void DreamKoalaLiftState::onLiftClosed(ichigo::Agent *agent)
    {
        if (_isInLift)
        {
            _office->moveLiftToFloor(_koala->getTargetFloor());
        }
    }
    
    
    // Called when koala finished walking into the lift
    void DreamKoalaLiftState::onInLift(ichigo::Agent *agent)
    {
        // Stand still
        ichigo::SpriteActorView *koalaSprite = (ichigo::SpriteActorView *)_koala->getView();
        koalaSprite->playAnimation("inside");
        
        // Move koala to behind the doors
        koalaSprite->setZOrder(1);
        
        // Close lift doors
        _office->closeLift();
    }
    
    
    // Called when koala finished walking out of the lift
    void DreamKoalaLiftState::onOutLift(ichigo::Agent *agent)
    {
        // Stand still
        ichigo::SpriteActorView *koalaSprite = (ichigo::SpriteActorView *)_koala->getView();
        koalaSprite->playAnimation("standOut");
        
        // Close lift doors
        _office->closeLift();
        
        // Return to standing mode
        _agent->getFSM()->transitionTo("stand");
    }
    
    
    // Called when lift arrived to target floor
    void DreamKoalaLiftState::onLiftAtTarget(ichigo::Agent *agent)
    {
        if (_isInLift)
        {
            // Arrive at floor
            ichigo::SpriteActorView *koalaView = (ichigo::SpriteActorView *)_koala->getView();
            ichigo::TileMapView *officeView = _office->getCurrentArea()->tileMap;
            ichigo::Point koalaPos = koalaView->getPosition();
            koalaPos.y += (_koala->getTargetFloor() - _koala->getFloor()) * officeView->getTileHeight();
            koalaView->setPosition(koalaPos);
            
            // Set koala animation
            koalaView->playAnimation("insideOut");
            _koala->setDir(DKD_OUT);
            _koala->setFloor(_koala->getTargetFloor());
            
            // Open lift doors
            _office->openLift();
        }
    }
}
