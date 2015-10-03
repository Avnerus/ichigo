#ifndef __KOALA_ENERGYGAUGEDECLININGSTATE_H__
#define __KOALA_ENERGYGAUGEDECLININGSTATE_H__

#include "FSMState.h"
#include "Agent.h"
#include "EnergyGauge.h"


namespace koala
{    
    class EnergyGaugeDecliningState : public ichigo::FSMState  
    {
    public:
        
        EnergyGaugeDecliningState();
        virtual ~EnergyGaugeDecliningState();
        
        virtual void    onUpdate(float dt);
        // virtual void    onEnter();   
        // virtual void    onExit();
        virtual void    init();
        
    protected:
        EnergyGauge  *_energyGauge;        
    };
}


#endif // __KOALA_ENERGYGAUGEDECLININGSTATE_H__
