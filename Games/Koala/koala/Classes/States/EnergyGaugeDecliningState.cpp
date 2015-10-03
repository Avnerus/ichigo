#include "EnergyGaugeDecliningState.h"
#include "Director.h"

namespace koala 
{    
    EnergyGaugeDecliningState::EnergyGaugeDecliningState() 
    {
        // My event table
        _name = "Declining";  
    }
    
    
    void EnergyGaugeDecliningState::init() {
        FSMState::init();
        _energyGauge = (EnergyGauge *)_agent;
    }
    
    EnergyGaugeDecliningState::~EnergyGaugeDecliningState() {

    }
    
    
    void EnergyGaugeDecliningState::onUpdate(float dt) {
        float decrease = _energyGauge->getDeclineSpeed() * dt;
        _energyGauge->setEnergy(_energyGauge->getEnergy() - decrease);
    }
}