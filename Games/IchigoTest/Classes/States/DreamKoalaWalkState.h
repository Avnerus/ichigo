#ifndef __IT_DREAMKOALAWALKSTATE_H__
#define __IT_DREAMKOALAWALKSTATE_H__

#include "FSMState.h"


namespace it
{
    class DreamKoala;
    
    class DreamKoalaWalkState : public ichigo::FSMState
    {
    public:
        
        DreamKoalaWalkState();
        virtual ~DreamKoalaWalkState();
        
        virtual void        onEnter();
        
        void                onLeftWalkEnded(ichigo::Agent *agnet);
        void                onRightWalkEnded(ichigo::Agent *agent);
        
    protected:
        
        DreamKoala         *_koala;
    };
}


#endif // __IT_DREAMKOALAWALKSTATE_H__
