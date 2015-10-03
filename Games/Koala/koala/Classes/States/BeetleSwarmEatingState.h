#ifndef __KOALA_BEETLEEATINGSTATE_H__
#define __KOALA_BEETLEEATINGSTATE_H__

#include "FSMState.h"
#include "Agent.h"
#include "BeetleSwarm.h"


namespace koala
{    
    class BeetleSwarmEatingState : public ichigo::FSMState  
    {
    public:
        
        BeetleSwarmEatingState();
        virtual ~BeetleSwarmEatingState();
        
        virtual void    onUpdate(float dt);
        virtual void    onEnter();
        virtual void    onExit();
        virtual void    init();
        
    protected:
        float        _percentageEaten;
        BeetleSwarm  *_swarm;        
    };
}


#endif // __KOALA_BEETLEEATINGSTATE_H__
