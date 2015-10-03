#include "NatureDefaultState.h"
#include "ichigo.h"


namespace koala
{    
    NatureDefaultState::NatureDefaultState():
        ichigo::StretchingState(true, true, false) {
        // My event table        
                
        _name = "Default";
    }
    
    
    NatureDefaultState::~NatureDefaultState() {
    }
    
    // Initialize state
    void NatureDefaultState::init()
    {
        StretchingState::init();
        
        _nature = (Nature *)_agent;
    }
    
    
    void NatureDefaultState::onUpdate(float dt)  {
    }
    
    
    void NatureDefaultState::onEnter() {
        std::cout << "NatureDefaultState onEnter" << endl;        
        _nature->spawnBeetleSwarm();               
    }
    
    
    void NatureDefaultState::onExit() {
        std::cout << "NatureDefaultState onExit" << endl;    
    } 
}