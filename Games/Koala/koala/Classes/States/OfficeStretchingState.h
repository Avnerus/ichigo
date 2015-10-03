#ifndef __KOALA_OFFICESTRETCHINGSTATE_H__
#define __KOALA_OFFICESTRETCHINGSTATE_H__

#include "StretchingState.h"


namespace koala
{
    class OfficeStretchingState : public ichigo::StretchingState
    {
    public:
        
        OfficeStretchingState();
        virtual ~OfficeStretchingState();
        
        void    onTouchMoved(ichigo::Agent *director);
        void    onTouchEnded(ichigo::Agent *director);
        
        void    onLiftOpened(ichigo::Agent *agent);
        void    onLiftArrived(ichigo::Agent *agent);
        void    onLiftClosed(ichigo::Agent *agent);

    protected:
        
        bool            _touchPointMoved;
    };
}


#endif // __KOALA_OFFICESTRETCHINGSTATE_H__
