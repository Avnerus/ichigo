#ifndef __IT_OFFICEMGRSTATE_H__
#define __IT_OFFICEMGRSTATE_H__

#include "StretchableState.h"


namespace it
{    
    class OfficeMgrState : public ichigo::StretchableState
    {
    public:
        
        OfficeMgrState();
        virtual ~OfficeMgrState();
        
        void    onLiftOpened(ichigo::Agent *agent);
        void    onLiftArrived(ichigo::Agent *agent);
        void    onLiftClosed(ichigo::Agent *agent);
    };
}


#endif // __IT_OFFICEMGRSTATE_H__
