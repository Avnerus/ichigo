#ifndef __IT_MENUSTATE_H__
#define __IT_MENUSTATE_H__

#include "FSMState.h"

namespace it
{
    class MenuState : public ichigo::FSMState
    {
    public:
        
        MenuState();
        
        void    onButton1Click(ichigo::Agent *agent);
        void    onButton2Click(ichigo::Agent *agent);
        void    onButton3Click(ichigo::Agent *agent);
    };
}

#endif // __IT_MENUSTATE_H__
