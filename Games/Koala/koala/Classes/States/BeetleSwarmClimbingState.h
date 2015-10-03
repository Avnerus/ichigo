#ifndef __KOALA_BEETLECLIMBINGSTATE_H__
#define __KOALA_BEETLECLIMBINGSTATE_H__

#include "FSMState.h"
#include "Agent.h"
#include "Tree.h"
#include "BeetleSwarm.h"



namespace koala
{    
    class BeetleSwarmClimbingState : public ichigo::FSMState  
    {
    public:
        
        BeetleSwarmClimbingState();
        virtual ~BeetleSwarmClimbingState();
        
        void            chooseTargetBranch();
        void            onMovementQueueEnded(ichigo::Agent *waitingAgent);
        
        virtual void    onUpdate(float dt);
        virtual void    onEnter();
        virtual void    onExit();
        virtual void    init();

        
    protected:
        BeetleSwarm  *_swarm;      
        BranchData  *_chosenBranch;
    };
}


#endif // __KOALA_BEETLECLIMBINGSTATE_H__
