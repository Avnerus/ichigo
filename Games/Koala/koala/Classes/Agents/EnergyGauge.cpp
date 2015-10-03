#include "EnergyGauge.h"
#include "DataManager.h"


namespace koala
{
    EnergyGauge::EnergyGauge() {
        // std::cout << "EnergyGauge::EnergyGauge() - Energy Gauge Created" << std::endl;
    }
    
    
    EnergyGauge::~EnergyGauge() {
        
    }
    
    bool EnergyGauge::init() {
        ichigo::Actor::init();
        _clippedActorView = std::tr1::static_pointer_cast<ichigo::ClippedActorView>(_view);        
        _maxClippingSize = _clippedActorView->getClippingSize();
        
        _energy = _maxEnergy;
        std::cout << "EnergyGauge::init() - Initialized energy with " << _energy << std::endl;
        
        return true;
    }
    
    
    void EnergyGauge::deserialize(Json::Value &agentConfig)
    {
        Actor::deserialize(agentConfig);
        _maxEnergy = ichigo::DataManager::getFloat  (agentConfig, "maxEnergy", 0.0f);
        _declineSpeed = ichigo::DataManager::getFloat  (agentConfig, "declineSpeed", 0.0f);
    }
    
    float EnergyGauge::getEnergy() {
        return _energy;
    }  
    
    void EnergyGauge::setEnergy(float energy) {
        _energy = energy;
        if (_energy < 0) {
            _energy = 0;
        }
        float newClippingX = _maxClippingSize.x * (_energy / _maxEnergy);
        _clippedActorView->setClippingSize(ichigo::Point(newClippingX,_maxClippingSize.y));
        
        // If clipping area is 0, no clipping will occur, so we hide the gauge
        if (newClippingX == 0)
        {
            _clippedActorView->setVisible(false);
        }
        else
        {
            _clippedActorView->setVisible(true);
        }
    } 
    
    float EnergyGauge::getDeclineSpeed() {
       return _declineSpeed;
    }
}
