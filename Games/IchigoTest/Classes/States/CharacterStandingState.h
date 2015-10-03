#ifndef __IT_CHARACTERSTANDING_H__
#define __IT_CHARACTERSTANDING_H__

#include "FSMState.h"


namespace it
{
    class CharacterStandingState : public ichigo::FSMState
    {
    public:
        
        CharacterStandingState();
        
        virtual void    onEnter();
        
        void            onTouchStarted(ichigo::Agent *director);
    };
}


#endif // __IT_CHARACTERSTANDING_H__
