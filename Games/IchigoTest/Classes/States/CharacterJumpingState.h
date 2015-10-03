#ifndef __IT_CHARACTERJUMPING_H__
#define __IT_CHARACTERJUMPING_H__

#include "FSMState.h"
#include "Point.h"


namespace it
{
    class CharacterJumpingState : public ichigo::FSMState
    {
    public:
        
        CharacterJumpingState();
        
        virtual void        onEnter();
        virtual void        onUpdate(float dt);
        
    protected:
        
        ichigo::Point       _initialPos;
        float               _jumpPhase;
    };
}


#endif // __IT_CHARACTERJUMPING_H__
