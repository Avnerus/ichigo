#ifndef __KOALA_ENERGYGAUGE_H__
#define __KOALA_ENERGYGAUGE_H__

#include "Actor.h"
#include "ClippedActorView.h"
#include <tr1/memory>

namespace koala {
    
    class EnergyGauge : public ichigo::Actor {
    public:
        
        EnergyGauge();
        virtual ~EnergyGauge();
        
        
        virtual bool init();        
        virtual void deserialize(Json::Value &agentConfig);
        
        float   getEnergy();
        void    setEnergy(float energy);
        
        float   getDeclineSpeed();
        
    protected:
        
        std::tr1::shared_ptr<ichigo::ClippedActorView>  _clippedActorView;
        ichigo::Point       _maxClippingSize;
        float               _maxEnergy;
        float               _declineSpeed;
        float               _energy;
    };
}


#endif // __KOALA_ENERGYGAUGE_H__
