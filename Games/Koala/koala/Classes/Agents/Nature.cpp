#include "Nature.h"
#include "Agent.h"
#include "BeetleSwarm.h"


namespace koala
{
    Nature::Nature() {
    }    
    
    Nature::~Nature() {        
    }
    
    bool Nature::init() {       
        Actor::init();   
        return true;
    }
    
    void Nature::setCurrentTree(Tree *tree) {
        _currentTree = tree;
        
        // Set stretching bounds
        ichigo::StretchingState *stretchingState = (ichigo::StretchingState *)getFSM()->getState("Default");
        ichigo::Rect clipBounds = _currentTree->getTileMap()->getBoundingBox();
        stretchingState->setLimitsForBounds(clipBounds.minX, clipBounds.minY, clipBounds.maxX, clipBounds.maxY);
    }
    
    void Nature::spawnBeetleSwarm() {
        std::cout << "Nature spawning a beetle swarm. Max level: " << _maxBeetleSwarmLevel << std::endl;
        
        BeetleSwarm *swarm = (BeetleSwarm *)ichigo::AgentFactory::createAgent("BeetleSwarm");
        Json::Value swarmJson = ichigo::DataManager::getInstance()->loadFromJSON("BeetleSwarm.json");
        swarm->loadFromJSON(swarmJson);
        
        // Choose a random level
        swarm->setLevel(ichigo::Utils::randi(_maxBeetleSwarmLevel) + 1);
        
        swarm->init();
        swarm->setTree(_currentTree);                
        _currentTree->addChild(swarm);
    }
    
     void Nature::deserialize(Json::Value &agentConfig) {
         ichigo::Actor::deserialize(agentConfig);        
         setMaxBeetleSwarmLevel(ichigo::DataManager::getInt(agentConfig, "maxBeetleSwarmLevel", 1));        
     }
     
     void Nature::setMaxBeetleSwarmLevel(int level) {
         _maxBeetleSwarmLevel = level;
     }
}