#include "BeetleSwarm.h"
#include "TileMapView.h"

#include "ichigo.h"


namespace koala
{
    BeetleSwarm::BeetleSwarm() {
        _tree = NULL;
        _currentBranch = NULL;
        _climbSpeed = 0.0f;
        _level = 1;
    }    
    
    BeetleSwarm::~BeetleSwarm() {        
    }
    
    Tree *BeetleSwarm::getTree() {
        return _tree;
    }
    void BeetleSwarm::setTree(Tree *tree) {
        _tree = tree;
    }
    
    float BeetleSwarm::getClimbSpeed() {
        return _climbSpeed;
    }
    void BeetleSwarm::setClimbSpeed(float climbSpeed) {
        _climbSpeed = climbSpeed;
    }
    
    bool BeetleSwarm::init() {
        Actor::init();
        _swarmView = (ichigo::SpriteActorView *)getView();           
        
           
        return true;
    }   
    
    ichigo::SpriteActorView *BeetleSwarm::getSpriteView() {
        return _swarmView;
    }
    
    // Hold json data and use it later to initialize
    void BeetleSwarm::deserialize(Json::Value &agentConfig) {
        ichigo::Actor::deserialize(agentConfig);        
        setClimbSpeed(ichigo::DataManager::getFloat(agentConfig, "climbSpeed", 1.0f));        
        setEatingSpeed(ichigo::DataManager::getFloat(agentConfig, "eatingSpeed", 0.0f));
    }
    
    float BeetleSwarm::getEatingSpeed() {
        return _eatingSpeed;
    }
    void BeetleSwarm::setEatingSpeed(float eatingSpeed) {
        _eatingSpeed = eatingSpeed;
    }
    
    void BeetleSwarm::setLevel(int level) {
        _level = level;
    }
    int BeetleSwarm::getLevel() {
        return _level;
    }
    
    BranchData *BeetleSwarm::getCurrentBranch() {
        return _currentBranch;
    }
    void BeetleSwarm::setCurrentBranch(BranchData *branch) {
        _currentBranch = branch;
    }
    
    void BeetleSwarm::Eat() {
        _tree->SetFoliageLevel(_currentBranch, _currentBranch->foliageLevel - 1);
    }
}