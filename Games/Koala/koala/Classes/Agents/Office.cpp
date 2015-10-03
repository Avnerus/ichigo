#include "Office.h"
#include "OfficeMgrState.h"
#include "OfficeStretchingState.h"
#include "DreamKoala.h"
#include "Item.h"

#include "TileMapView.h"
#include "Tile.h"
#include "Agent.h"
#include "DataManager.h"
#include "AgentFactory.h"
#include "Director.h"
#include "Utils.h"
#include "SpriteActorView.h"


namespace koala
{
    Office::Office()
    {
        // Init data
        _dreamKoala = NULL;
        _currArea = NULL;
    }
    
    
    Office::~Office()
    {
        // Release all area meta data
        for (std::map<std::string, AreaData *>::iterator it = _areas.begin(); it != _areas.end(); it++)
        {
            AreaData *area = it->second;
            
            // Release all lift data for this area
            for (std::map<int, LiftData *>::iterator liftIt = area->lifts.begin(); liftIt != area->lifts.end(); liftIt++)
            {
                delete liftIt->second;
            }
            
            // Release all portal data for this area
            for (std::map<int, std::map<int, PortalData *> >::iterator rowIt = area->portals.begin(); rowIt != area->portals.end(); rowIt++)
            {
                for (std::map<int, PortalData *>::iterator colIt = rowIt->second.begin(); colIt != rowIt->second.end(); colIt++)
                {
                    delete colIt->second;
                }
            }
            
            // Release all object data for this area
            for (std::map<int, std::map<int, ObjectData *> >::iterator objRowIt = area->objects.begin(); objRowIt != area->objects.end(); objRowIt++)
            {
                for (std::map<int, ObjectData *>::iterator objColIt = objRowIt->second.begin(); objColIt != objRowIt->second.end(); objColIt++)
                {
                    delete objColIt->second;
                }
            }
            
            // Release the area
            delete area;
        }
    }
    
    
    // Hold json data and use it later to initialize
    void Office::deserialize(Json::Value &agentConfig)
    {
        ichigo::Actor::deserialize(agentConfig);
        
        _initData = agentConfig;
    }
    
    
    // Initialize stuff
    bool Office::init()
    {
        bool retVal = ichigo::Actor::init();
        
        _dreamKoala = (DreamKoala *)findByName("dreamKoala");
        
        initOffice();
        
        setViewForArea();

        return retVal;
    }
    
    
    // Initializes all meta data for the office
    void Office::initOffice()
    {
        // Initialize an area for each child which is a tilemap
        for (ichigo::AgentList::iterator it = _children.begin(); it != _children.end(); it++)
        {
            if (it->second->getView()->getType() == "TileMapView")
            {
                initArea(it->first);
            }
        }
        
        // Set first area
        setCurrentArea(ichigo::DataManager::getString(_initData, "firstArea"));
        
        // Initialize all portals
        Json::Value &portals = _initData["portals"];
        if (!portals.isNull())
        {
            int portalCount = portals.size();
            for (int i = 0; i < portalCount; i++)
            {
                initPortal(portals[i]);
            }
        }
        
        // Initialize all object
        Json::Value &objects = _initData["objects"];
        if (!objects.isNull())
        {
            int objectCount = objects.size();
            for (int i = 0; i < objectCount; i++)
            {
                initObject(objects[i]);
            }
        }
    }
    
    
    // Initializes one area of the office
    void Office::initArea(const std::string &areaName)
    {
        ichigo::Agent *areaAgent = getChild(areaName);
        if (areaAgent)
        {
            AreaData *ad = new AreaData(areaName);
            ad->tileMap = (ichigo::TileMapView *)areaAgent->getView();
            _areas[areaName] = ad;
            
            // Go over all tiles in the area and search for special tiles
            int rows = ad->tileMap->getTileRows();
            int cols = ad->tileMap->getTileColumns();
            for (int x = 0; x < cols; x++)
            {
                for (int y = 0; y < rows; y++)
                {
                    ichigo::Tile *currTile = ad->tileMap->getTile(x, y);
                    
                    if (currTile->getID() == CONST_STRING("OFFICE_TILE_LIFT"))
                    {
                        // Tile is a lift, load doors sprite
                        ichigo::Agent *door = ichigo::AgentFactory::createAgent("Sprite");
                        Json::Value doorJson = ichigo::DataManager::getInstance()->loadFromJSON(CONST_STRING("OFFICE_LIFT_ANIM"));
                        door->loadFromJSON(doorJson);
                        areaAgent->addChild(door);
                        
                        ichigo::Point doorPos;
                        doorPos.x = currTile->getPosition().x + CONST_FLOAT("OFFICE_LIFT_OFFSET_X");
                        doorPos.y = currTile->getPosition().y + CONST_FLOAT("OFFICE_LIFT_OFFSET_Y");
                        door->getView()->setPosition(doorPos);
                        
                        // Create LiftData class to hold extra data about each lift
                        LiftData *liftData = new LiftData;
                        liftData->isOpen = false;
                        liftData->doorSprite = door;
                        ad->lifts[y] = liftData;
                    }
                }
            }
        }
    }
    
    
    // Initializes a portal meta data from Json
    void Office::initPortal(Json::Value &portalData)
    {
        // Get all values
        std::string srcArea = ichigo::DataManager::getString(portalData, "area");
        int srcRow = ichigo::DataManager::getInt(portalData, "row");
        int srcCol = ichigo::DataManager::getInt(portalData, "col");
        std::string targetArea = ichigo::DataManager::getString(portalData, "targetArea");
        int targetRow = ichigo::DataManager::getInt(portalData, "targetRow");
        int targetCol = ichigo::DataManager::getInt(portalData, "targetCol");
        
        // Do the areas exist?
        if (_areas.find(srcArea) != _areas.end() && _areas.find(targetArea) != _areas.end())
        {
            // Create portal
            _areas[srcArea]->portals[srcCol][srcRow] = new PortalData(targetArea, targetRow, targetCol);
            
            // If needed, create the opposite portal
            if (ichigo::DataManager::getBool(portalData, "bidirectional"))
            {
                _areas[targetArea]->portals[targetCol][targetRow] = new PortalData(srcArea, srcRow, srcCol);
            }
        }
    }
    
    
    // Initialize an interactive office object from Json data
    void Office::initObject(Json::Value &objectData)
    {
        // Get all values
        std::string type = ichigo::DataManager::getString(objectData, "type");
        std::string area = ichigo::DataManager::getString(objectData, "area");
        int row = ichigo::DataManager::getInt(objectData, "row");
        int col = ichigo::DataManager::getInt(objectData, "col");
        
        // Does the area exist?
        if (_areas.find(area) != _areas.end())
        {
            ichigo::TileMapView *areaView = _areas[area]->tileMap;
            
            // Load object into area
            ichigo::Agent *objAgent = ichigo::AgentFactory::createAgent("Sprite");
            Json::Value objJson = ichigo::DataManager::getInstance()->loadFromJSON(type + ".json");
            objAgent->loadFromJSON(objJson);
            areaView->getAgent()->addChild(objAgent);
            
            // Position object in correct place
            ichigo::Point objPos = objAgent->getView()->getPosition();
            objPos.x += col * areaView->getTileWidth();
            objPos.y += row * areaView->getTileHeight();
            objAgent->getView()->setPosition(objPos);
            
            // Read extra object data
            float interactionPointX = ichigo::DataManager::getFloat(objJson, "interactionPointX");
            ichigo::Point itemAnchor = ichigo::DataManager::getPoint(objJson, "itemAnchor");
            
            // Save object data
            ObjectData *objData = new ObjectData(type, objAgent, interactionPointX, itemAnchor);
            objData->item = initItem(ichigo::DataManager::getString(objectData, "item"));
            
            // Add item to scene and position
            if (objData->item)
            {
                objAgent->addChild(objData->item);
                objData->item->getView()->setPosition(itemAnchor);
            }
            
            _areas[area]->objects[col][row] = objData;
        }
    }
    
    
    // Initializes an item and returns it
    Item *Office::initItem(const std::string &item)
    {
        Item *retVal = NULL;
        
        if (item != "")
        {
            retVal = (Item *)ichigo::AgentFactory::createAgent("Item");
        
            if (retVal)
            {
                Json::Value itemJson = ichigo::DataManager::getInstance()->loadFromJSON(item + ".json");
                retVal->loadFromJSON(itemJson);
            }
        }
        
        return retVal;
    }
    
    
    // Sets the view to current position of the koala in the office, and the StretchableState limits to the size of current area
    void Office::setViewForArea()
    {
        int tileCols = _currArea->tileMap->getTileColumns();
        int tileRows = _currArea->tileMap->getTileRows();
        float tileWidth = _currArea->tileMap->getTileWidth();
        float tileHeight = _currArea->tileMap->getTileHeight();
        
        
        ((OfficeStretchingState *)_fsm.getState("OfficeStretching"))->setLimitsForBounds(-tileWidth / 2.0f, 
                                                                                         -tileHeight / 2.0f,
                                                                                        (tileWidth - 1.0f) * ((float)tileCols - 0.5f),  
                                                                                         tileHeight * ((float)tileRows - 0.5f));
    }
    
    
    // Sets the office view to the current area
    void Office::setCurrentArea(const std::string &areaName)
    {
        // Go over all areas
        for (std::map<std::string, AreaData *>::iterator it = _areas.begin(); it != _areas.end(); it++)
        {
            // If this is the current area, save it and show it. Hide all the others
            if (it->second->name == areaName)
            {
                _currArea = it->second;
                _currArea->tileMap->setVisible(true);
                
                // Also make the koala a child of this tilemap
                std::tr1::shared_ptr<Agent> retainedCopy = _dreamKoala->getParent()->retainChild(_dreamKoala);
                _dreamKoala->getParent()->removeChild(_dreamKoala);
                _currArea->tileMap->getAgent()->addChild(retainedCopy, "dreamKoala");
            }
            else
            {
                it->second->tileMap->setVisible(false);
            }
        }
    }
    
    
    // Returns data of current area
    AreaData *Office::getCurrentArea()
    {
        return _currArea;
    }
    
    
    // Changes area to target area of given portal at current koala position. Returns local coordinates of target tile.
    ichigo::Point Office::enterPortal()
    {
        ichigo::Point retVal;
        
        // Find portal at koala's position
        ichigo::Point koalaPos = _dreamKoala->getView()->getPosition();
        int col = koalaPos.x / _currArea->tileMap->getTileWidth() + 0.5f;
        int row = koalaPos.y / _currArea->tileMap->getTileHeight() + 0.5f;
        PortalData *currPortal = _currArea->portals[col][row];
        
        if (currPortal)
        {
            // Change area
            setCurrentArea(currPortal->targetArea);
        
            // Get position of target tile
            retVal = _currArea->tileMap->getTile(currPortal->targetCol, currPortal->targetRow)->getPosition();
            
            // Focus new area at koala
            setViewForArea();
            ((OfficeStretchingState *)_fsm.getState("OfficeStretching"))->focusOnPoint(retVal);
        }
                
        return retVal;
    }
    
    
    // Gets called by the stretching state when the player clicked the office but didn't drag or stretch it. This means he clicked to
    // initiate an action, and this method handles it.
    void Office::handleClick(ichigo::Point &touchPoint)
    {
        ichigo::Point localTouch = _currArea->tileMap->convertScreenToLocal(touchPoint);
        ichigo::Tile *touchedTile = _currArea->tileMap->getTileAtPosition(localTouch.x, localTouch.y, NULL);
        
        ichigo::Point koalaPos = _dreamKoala->getView()->getPosition();
        ichigo::Tile *koalaTile = _currArea->tileMap->getTileAtPosition(koalaPos.x, koalaPos.y, NULL);
        
        int touchCol = _currArea->tileMap->getTileCol(localTouch.x);
        int touchRow = _currArea->tileMap->getTileRow(localTouch.y);
        
        if (touchedTile && koalaTile)
        {
            // Check if player is standing next to a lift and trying to go to another floor
            if (koalaTile->getID() == CONST_STRING("OFFICE_TILE_LIFT") && touchedTile->getID() == CONST_STRING("OFFICE_TILE_LIFT") &&
                _dreamKoala->getFloor() != getFloorForTilePos(localTouch.y))
            {
                _dreamKoala->setTargetFloor(getFloorForTilePos(localTouch.y));
                _dreamKoala->setTargetX(touchedTile->getPosition().x + CONST_FLOAT("DKOALA_LIFT_ENTRY_X"));
            }
            else if (koalaTile == touchedTile && koalaTile->getID() == CONST_STRING("OFFICE_TILE_DOOR"))
            {
                // Koala is standing next to a door and player touched the door. Enter it.
                _dreamKoala->enterDoor();
                _dreamKoala->setTargetX(touchedTile->getPosition().x + CONST_FLOAT("DKOALA_DOOR_X"));
            }
            else if (koalaTile == touchedTile && _currArea->objects.find(touchCol) != _currArea->objects.end() &&
                     _currArea->objects[touchCol].find(touchRow) != _currArea->objects[touchCol].end())
            {
                // Koala is standing next to an object, interact with it
                ObjectData *objData = _currArea->objects[touchCol][touchRow];
                _dreamKoala->setTargetX(touchedTile->getPosition().x + objData->interactionPointX);
                _dreamKoala->useObject(objData->type, objData->agent->getView()->getZOrder());
            }
            else
            {
                // Find where player has clicked, make sure it is within office bounds
                float targetX = _currArea->tileMap->convertScreenToLocal(touchPoint).x;
                if (targetX < CONST_FLOAT("OFFICE_MIN_X"))
                {
                    targetX = CONST_FLOAT("OFFICE_MIN_X");
                }
                
                // Right bound depends on nuber of tile colums
                float officeMaxX = ((float)_currArea->tileMap->getTileColumns() - 0.5f) * (_currArea->tileMap->getTileWidth() - 1.0f);
                officeMaxX -= CONST_FLOAT("OFFICE_MAX_X");
                if (targetX > officeMaxX)
                {
                    targetX = officeMaxX;
                }
                
                _dreamKoala->setTargetX(targetX);
            }
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
        LiftData *lift = _currArea->lifts[floor];
        
        ((ichigo::SpriteActorView *)lift->doorSprite->getView())->playAnimation("opening");
    }
    
    
    // Starts closing lift doors
    void Office::closeLift()
    {
        // Find lift on koala's floor
        int floor = _dreamKoala->getFloor();
        LiftData *lift = _currArea->lifts[floor];
        
        ((ichigo::SpriteActorView *)lift->doorSprite->getView())->playAnimation("closing");
    }
    
    
    // Called by a state when the lift doors finished opening animation
    void Office::onLiftOpened()
    {
        LiftData *lift = _currArea->lifts[_dreamKoala->getFloor()];
        lift->isOpen = true;
        ((ichigo::SpriteActorView *)lift->doorSprite->getView())->playAnimation("open");
    }
    
    
    // Called by a state when the lift doors finished closing animation
    void Office::onLiftClosed()
    {
        LiftData *lift = _currArea->lifts[_dreamKoala->getFloor()];
        lift->isOpen = false;
        ((ichigo::SpriteActorView *)lift->doorSprite->getView())->playAnimation("closed");        
    }
    
    
    // For position Y in local tilemap coordinates, returns which floor it is
    int Office::getFloorForTilePos(float y)
    {
        float tileHeight = _currArea->tileMap->getTileHeight();
        return (int)((y + (tileHeight / 2.0f)) / tileHeight);
    }
}
