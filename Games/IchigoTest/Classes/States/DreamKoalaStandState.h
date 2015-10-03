#ifndef __IT_DREAMKOALASTANDSTATE_H__
#define __IT_DREAMKOALASTANDSTATE_H__

#include "FSMState.h"


namespace it
{
    class DreamKoala;
    
    class DreamKoalaStandState : public ichigo::FSMState
    {
    public:
        
        DreamKoalaStandState();
        virtual ~DreamKoalaStandState();
        
        virtual void        onEnter();
        virtual void        onUpdate(float dt);
        
        void                turnLeft();
        void                turnRight();
        void                turnIn();
        void                walk();
        void                startLiftSequence();
        
        void                onTurnRightComplete(ichigo::Agent *agnet);
        void                onTurnLeftComplete(ichigo::Agent *agent);
        void                onTurnInComplete(ichigo::Agent *agent);
        
    protected:
        
        DreamKoala         *_koala;
        bool                _isTurning;
        bool                _twoPhaseTurn;
    };
}

#endif // __IT_DREAMKOALASTANDSTATE_H__
