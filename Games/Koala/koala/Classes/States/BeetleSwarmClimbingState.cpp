#include "BeetleSwarmClimbingState.h"
#include "ichigo.h"
#include <vector>
#include <tr1/memory>


namespace koala
{    
    BeetleSwarmClimbingState::BeetleSwarmClimbingState() {
        // My event table        
        _eventCallbacks["MOVEMENT_QUEUE_ENDED"] = std::tr1::bind(&BeetleSwarmClimbingState::onMovementQueueEnded, this, _1);        
                        
        _name = "Climbing";
    }
    
    
    BeetleSwarmClimbingState::~BeetleSwarmClimbingState() {
    }
    
    
    void BeetleSwarmClimbingState::onUpdate(float dt)  {        
    }
    
    void BeetleSwarmClimbingState::init() {
        FSMState::init();        
        _swarm = (BeetleSwarm *)_agent;
    }
    
    
    void BeetleSwarmClimbingState::onEnter() {
        std::cout << "BeetleSwarmClimbingState onEnter" << endl;      
        // Place beetle at the bottom of the tree
        ichigo::Tile *tile = _swarm->getTree()->getTileMap()->getTile(1,0);
        _swarm->getView()->setPosition(
            ichigo::Point(
                tile->getPosition().x,
                tile->getPosition().y - (tile->getSize().y / 2.0f) + (_swarm->getSpriteView()->getHeight() / 2.0f)
            )
        );  
        // Choose target branch
        chooseTargetBranch();
    }
    
    void BeetleSwarmClimbingState::chooseTargetBranch() {
        BranchLevelList branchLevelList = _swarm->getTree()->getBranchLevelList();
        std::vector<std::tr1::shared_ptr<BranchData> > candidates;
        for (BranchLevelList::iterator it = branchLevelList.begin(); it != branchLevelList.end(); it++) {
            std::tr1::shared_ptr<LevelData> level = (*it);
            if (level->leftBranch) {
                if (level->leftBranch->foliageLevel > 0) {
                    candidates.push_back(level->leftBranch);
                }
            }
            if (level->rightBranch) {
                if (level->rightBranch->foliageLevel > 0) {
                    candidates.push_back(level->rightBranch);
                }
            }
        }
        int chosenIndex;
        
        if (candidates.size() == 0) {
            return ;
        }
        else if (candidates.size() == 1) {
            chosenIndex = 0;            
        }
        else {
           chosenIndex = ichigo::Utils::randi(candidates.size() - 1);
        }        
        _chosenBranch = candidates[chosenIndex].get();        
        std::cout << "Moving from " << _swarm->getView()->getPosition() << " to branch at " << _chosenBranch->tile->getPosition() << " at speed " << _swarm->getClimbSpeed() << std::endl;
        ichigo::Point target1 = _chosenBranch->tile->getPosition();
        target1.x = _swarm->getView()->getPosition().x;
        std::string verticalAnimation = "beetleSwarm" + ichigo::Utils::intToZeroPaddedString(_swarm->getLevel(), 1) + "V";
        std::string horizontalAnimation = "beetleSwarm" + ichigo::Utils::intToZeroPaddedString(_swarm->getLevel(), 1) + "H";
        std::cout << "Queueing animation " << verticalAnimation << std::endl;
        _swarm->getSpriteView()->queueMovement(verticalAnimation, target1, _swarm->getClimbSpeed());        
        _swarm->getSpriteView()->queueMovement(horizontalAnimation, _chosenBranch->tile->getPosition(), _swarm->getClimbSpeed()); 
        
    }
    
    void BeetleSwarmClimbingState::onMovementQueueEnded(ichigo::Agent *waitingAgent) {
        if (_agent == waitingAgent) {
            std::cout << "BeetleSwarmClimbingState::onMovementQueueEnded()" << std::endl;
            _swarm->setCurrentBranch(_chosenBranch);
            _agent->getFSM()->transitionTo("Eating");
        }
    }
    
    
    void BeetleSwarmClimbingState::onExit() {
        std::cout << "BeetleSwarmClimbingState onExit" << endl;    
    } 
}