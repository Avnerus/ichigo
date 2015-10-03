#ifndef __KOALA_DREAMKOALADOORSTATE_H__
#define __KOALA_DREAMKOALADOORSTATE_H__

#include "FSMState.h"


namespace koala
{
    class DreamKoala;
    class Office;
    
    class DreamKoalaDoorState : public ichigo::FSMState
    {
    public:
        
        DreamKoalaDoorState();
        virtual ~DreamKoalaDoorState();
        
        virtual void        onEnter();
        
        virtual void        onInDoor(ichigo::Agent *agent);
        virtual void        onOutOfDoor(ichigo::Agent *agent);
        
    protected:
        
        void                walkIntoDoor();
        
        DreamKoala         *_koala;
        Office             *_office;
    };
}


#endif // __KOALA_DREAMKOALADOORSTATE_H__
