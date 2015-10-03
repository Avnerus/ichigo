#ifndef __KOALA_DREAMKOALAWALKSTATE_H__
#define __KOALA_DREAMKOALAWALKSTATE_H__

#include "FSMState.h"


namespace koala
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


#endif // __KOALA_DREAMKOALAWALKSTATE_H__
