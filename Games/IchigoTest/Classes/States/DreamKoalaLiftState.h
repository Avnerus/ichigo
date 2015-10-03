#ifndef __IT_DREAMKOALALIFT_STATE_H__
#define __IT_DREAMKOALALIFT_STATE_H__

#include "FSMState.h"

namespace it
{
    class DreamKoala;
    class Office;
    
    class DreamKoalaLiftState : public ichigo::FSMState
    {
    public:
        
        DreamKoalaLiftState();
        virtual ~DreamKoalaLiftState();
        
        virtual void        onEnter();
        virtual void        onUpdate(float dt);
        
        virtual void        onLiftOpened(ichigo::Agent *agent);
        virtual void        onLiftClosed(ichigo::Agent *agent);
        virtual void        onInLift(ichigo::Agent *agent);
        virtual void        onOutLift(ichigo::Agent *agent);
        virtual void        onLiftAtTarget(ichigo::Agent *agent);
        
    protected:
        
        DreamKoala         *_koala;
        Office             *_office;
        
        bool                _isInLift;
    };
}


#endif // __IT_DREAMKOALALIFT_STATE_H__
