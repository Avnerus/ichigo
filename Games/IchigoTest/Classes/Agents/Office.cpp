#include "Office.h"
#include "OfficeMgrState.h"
#include "OfficeStretchingState.h"
#include "DreamKoala.h"

#include "TileMapView.h"
#include "Tile.h"
#include "Agent.h"
#include "DataManager.h"
#include "AgentFactory.h"
#include "Director.h"
#include "Utils.h"
#include "SpriteActorView.h"


namespace it
{
    Office::Office()
    {
        // Add states to the office
        _fsm.addState(new it::OfficeMgrState(), true);
        it::OfficeStretchingState *stretchingState = new it::OfficeStretchingState();
        stretchingState->setScaleLimits(1.0f, 0.34f);
        stretchingState->setTranslateLimits(true, -1275, 160, -478, 160);
        stretchingState->setTranslateLimits(false, -116, 54, 54, 54);
        _fsm.addState(stretchingState, false);
        
        // Init data
        _dreamKoala = NULL;
        _tilemap = NULL;
    }
    
    
    Office::~Office()
    {
        // Release all lift data for each floor
        for (std::map<int, LiftData *>::iterator it = _liftsData.begin(); it != _liftsData.end(); it++)
        {
            delete it->second;
        }
    }
    
    
    // Gets called each frame
    void Office::update(float dt)
    {
        Actor::update(dt);
        
        // Initialize stuff
        if (!_tilemap)
        {
            _tilemap = (ichigo::TileMapView *)getView();
            initOfficeMgr();
        }
        if (!_dreamKoala)
        {
            _dreamKoala = (DreamKoala *)findByName("dreamKoala");
            
            // Tell koala its original position
            float koalaCurrX = _dreamKoala->getView()->getPosition().x;
            int koalaCurrFloor = getFloorForTilePos(_dreamKoala->getView()->getPosition().y);
            _dreamKoala->setPosX(koalaCurrX);
            _dreamKoala->setTargetX(koalaCurrX);
            _dreamKoala->setDir(DKD_RIGHT);
            _dreamKoala->setFloor(koalaCurrFloor);
            _dreamKoala->setTargetFloor(koalaCurrFloor);
        }
    }
    
    
    // Gets called by the stretching state when the player clicked the office but didn't drag or stretch it. This means he clicked to
    // initiate an action, and this method handles it.
    void Office::handleClick(ichigo::Point &touchPoint)
    {
        ichigo::Point localTouch = _tilemap->convertScreenToLocal(touchPoint);
        ichigo::Tile *touchedTile = _tilemap->getTileAtPosition(localTouch.x, localTouch.y, NULL);
        
        ichigo::Point koalaPos = _dreamKoala->getView()->getPosition();
        ichigo::Tile *koalaTile = _tilemap->getTileAtPosition(koalaPos.x, koalaPos.y, NULL);
        
        // Check if player is standing next to a lift and trying to go to another floor
        if (koalaTile->getID() == CONST_STRING("OFFICE_TILE_LIFT") && touchedTile->getID() == CONST_STRING("OFFICE_TILE_LIFT") &&
            _dreamKoala->getFloor() != getFloorForTilePos(localTouch.y))
        {
            _dreamKoala->setTargetFloor(getFloorForTilePos(localTouch.y));
            _dreamKoala->setTargetX(touchedTile->getPosition().x + CONST_FLOAT("DKOALA_LIFT_ENTRY_X"));
        }
        else
        {
            // Find where player has clicked, make sure it is within office bounds
            float targetX = _tilemap->convertScreenToLocal(touchPoint).x;
            if (targetX < CONST_FLOAT("OFFICE_MIN_X"))
            {
                targetX = CONST_FLOAT("OFFICE_MIN_X");
            }
            if (targetX > CONST_FLOAT("OFFICE_MAX_X"))
            {
                targetX = CONST_FLOAT("OFFICE_MAX_X");
            }
            
            _dreamKoala->setTargetX(targetX);
        }
    }
    
    
    // Requests the lift on the floor with the koala
    void Office::orderLift()
    {
        ichigo::Director::getInstance()->addTimer(this, "LiftArrived", ichigo::Utils::randf(CONST_FLOAT("OFFICE_LIFT_WAIT_MAX")));
    }
    
    
    // Move lift from floor with koala to requested floor
    void Office::moveLiftToFloor(int floor)
    {
        int sourceFloor = _dreamKoala->getFloor();
        int floorsToTravel = abs(floor - sourceFloor);
        
        float liftTravelTime = CONST_FLOAT("OFFICE_LIFT_FLOOR_TIME") * floorsToTravel;        
        ichigo::Director::getInstance()->addTimer(this, "LiftAtFloor", liftTravelTime);
    }
    
    
    // Start opening lift doors for floor with koala
    void Office::openLift()
    {
        // Find lift on koala's floor
        int floor = _dreamKoala->getFloor();
        LiftData *lift = _liftsData[floor];
        
        ((ichigo::SpriteActorView *)lift->doorSprite->getView())->playAnimation("opening");
    }
    
    
    // Starts closing lift doors
    void Office::closeLift()
    {
        // Find lift on koala's floor
        int floor = _dreamKoala->getFloor();
        LiftData *lift = _liftsData[floor];
        
        ((ichigo::SpriteActorView *)lift->doorSprite->getView())->playAnimation("closing");
    }
    
    
    // Called by a state when the lift doors finished opening animation
    void Office::onLiftOpened()
    {
        LiftData *lift = _liftsData[_dreamKoala->getFloor()];
        lift->isOpen = true;
        ((ichigo::SpriteActorView *)lift->doorSprite->getView())->playAnimation("open");
    }
    
    
    // Called by a state when the lift doors finished closing animation
    void Office::onLiftClosed()
    {
        LiftData *lift = _liftsData[_dreamKoala->getFloor()];
        lift->isOpen = false;
        ((ichigo::SpriteActorView *)lift->doorSprite->getView())->playAnimation("closed");        
    }

    
    // Reads the office tiles and initializes the OfficeManager accordingly
    void Office::initOfficeMgr()
    {
        // Go over all tiles in map
        int rows = _tilemap->getTileRows();
        int cols = _tilemap->getTileColumns();
        for (int x = 0; x < cols; x++)
        {
            for (int y = 0; y < rows; y++)
            {
                ichigo::Tile *currTile = _tilemap->getTile(x, y);
                
                if (currTile->getID() == CONST_STRING("OFFICE_TILE_LIFT"))
                {
                    // Tile is a lift, load doors sprite
                    ichigo::Agent *door = ichigo::AgentFactory::createAgent("Sprite");
                    Json::Value doorJson = ichigo::DataManager::getInstance()->loadFromJSON(CONST_STRING("OFFICE_LIFT_ANIM"));
                    door->loadFromJSON(doorJson);
                    addChild(door);
                    
                    ichigo::Point doorPos;
                    doorPos.x = currTile->getPosition().x + CONST_FLOAT("OFFICE_LIFT_OFFSET_X");
                    doorPos.y = currTile->getPosition().y + CONST_FLOAT("OFFICE_LIFT_OFFSET_Y");
                    door->getView()->setPosition(doorPos);
                    
                    // Create LiftData class to hold extra data about each lift
                    LiftData *liftData = new LiftData;
                    liftData->isOpen = false;
                    liftData->doorSprite = door;
                    _liftsData[y] = liftData;
                }
            }
        }
    }
    
    
    // For position Y in local tilemap coordinates, returns which floor it is
    int Office::getFloorForTilePos(float y)
    {
        float tileHeight = _tilemap->getTileHeight();
        return (int)((y + (tileHeight / 2.0f)) / tileHeight);
    }
}
