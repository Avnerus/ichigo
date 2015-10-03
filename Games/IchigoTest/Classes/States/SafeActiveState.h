#ifndef __IT_SAFEACTIVESTATE_H__
#define __IT_SAFEACTIVESTATE_H__

#include "FSMState.h"
#include "Agent.h"


namespace it
{
    class SafeActiveState : public ichigo::FSMState
    {
    public:
        
        SafeActiveState();
        
        virtual void    onEnter();
        virtual void    onUpdate(float dt);
        
        void            enableCollisionDetection(ichigo::Agent *director);
        
    protected:
        
        void            handleCollision();
        
        ichigo::Agent  *_tzahiAgent;
        ichigo::Agent  *_hitCounter;
        ichigo::Agent  *_ouchAgent;
        int             _hits;
        bool            _canDetectCollisions;
        float           _initialSafeX;
    };
}


#endif // __IT_SAFEACTIVESTATE_H__
