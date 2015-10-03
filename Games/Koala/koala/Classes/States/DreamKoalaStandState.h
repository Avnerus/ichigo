#ifndef __KOALA_DREAMKOALASTANDSTATE_H__
#define __KOALA_DREAMKOALASTANDSTATE_H__

#include "CharacterState.h"


namespace koala
{
    class DreamKoala;
    
    class DreamKoalaStandState : public ichigo::CharacterState
    {
    public:
        
        DreamKoalaStandState();
        virtual ~DreamKoalaStandState();
        
        virtual void        onEnter();
        virtual void        onUpdate(float dt);
        
        void                turnLeft();
        void                turnRight();
        void                turnIn();
        void                turnOut();
        void                walk();
        void                startLiftSequence();
        void                goIntoDoor();
        void                useObject();
        
        void                onTurnRightComplete(ichigo::Agent *agnet);
        void                onTurnLeftComplete(ichigo::Agent *agent);
        void                onTurnInComplete(ichigo::Agent *agent);
        void                onTurnOutComplete(ichigo::Agent *agent);
        
    protected:
        
        DreamKoala         *_koala;
        bool                _isTurning;
        bool                _twoPhaseTurn;
    };
}

#endif // __KOALA_DREAMKOALASTANDSTATE_H__
