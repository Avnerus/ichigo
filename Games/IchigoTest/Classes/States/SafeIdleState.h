#ifndef __IT_SAFEIDLESTATE_H__
#define __IT_SAFEIDLESTATE_H__

#include "FSMState.h"
#include "Agent.h"


namespace it
{
    class SafeIdleState : public ichigo::FSMState
    {
    public:
        
        SafeIdleState();
        
        void                onStartButtonPressed(ichigo::Agent *button);
        void                onCanRestart(ichigo::Agent *director);
        
    protected:
        
        ichigo::Agent      *_startButton;
        ichigo::Agent      *_hitCounter;
        ichigo::Agent      *_tryAgain;
    };
}


#endif // __IT_SAFEIDLESTATE_H__
