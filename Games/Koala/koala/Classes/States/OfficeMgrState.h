#ifndef __KOALA_OFFICEMGRSTATE_H__
#define __KOALA_OFFICEMGRSTATE_H__

#include "StretchableState.h"


namespace koala
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


#endif // __KOALA_OFFICEMGRSTATE_H__
