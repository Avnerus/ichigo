#ifndef __IT_DIRECTORRUNNING_H__
#define __IT_DIRECTORRUNNING_H__

#include "FSMState.h"
#include "Agent.h"


namespace it 
{    
    class DirectorRunningState : public ichigo::FSMState  
    {
    public:
        
        DirectorRunningState();
        virtual ~DirectorRunningState();
        
        virtual void    onBackButton(ichigo::Agent *button);
    };
}


#endif // __IT_DIRECTORRUNNING_H__