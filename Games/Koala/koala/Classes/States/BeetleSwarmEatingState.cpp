#include "BeetleSwarmEatingState.h"
#include "ichigo.h"


namespace koala
{    
    BeetleSwarmEatingState::BeetleSwarmEatingState() {
        // My event table        
                
        _name = "Eating";
    }
    
    
    BeetleSwarmEatingState::~BeetleSwarmEatingState() {
    }
    
    
    void BeetleSwarmEatingState::onUpdate(float dt)  {   
        _percentageEaten += _swarm->getEatingSpeed() * _swarm->getLevel() * dt;
        if (_percentageEaten >= 1.0f) {
            std::cout << "BeetleSwarmEatingState::onUpdate() EAATATTTTT!!!" << std::endl;
            _swarm->Eat();
            _percentageEaten = 0.0f;
        }

    }
    
    void BeetleSwarmEatingState::init() {
        FSMState::init();        
        _swarm = (BeetleSwarm *)_agent;
    }
    
    
    void BeetleSwarmEatingState::onEnter() {
        std::cout << "BeetleSwarmEatingState onEnter" << endl;  
        _percentageEaten = 0.0f;     
    }
    
    
    void BeetleSwarmEatingState::onExit() {
        std::cout << "BeetleSwarmEatingState onExit" << endl;    
    } 
}