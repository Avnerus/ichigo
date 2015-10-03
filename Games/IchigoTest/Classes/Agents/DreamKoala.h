#ifndef __IT_DREAMKOALA_H__
#define __IT_DREAMKOALA_H__

#include "Actor.h"


namespace it
{
    enum DreamKoalaDirection
    {
        DKD_LEFT,
        DKD_RIGHT,
        DKD_IN,
        DKD_OUT
    };
    
    class DreamKoala : public ichigo::Actor
    {
    public:
        
        DreamKoala();
        virtual ~DreamKoala();
        
        void                setTargetX(float x);
        float               getTargetX();
        void                setPosX(float xPos);
        float               getPosX();
        void                setFloor(int floor);
        int                 getFloor();
        void                setTargetFloor(int floor);
        int                 getTargetFloor();
        void                setDir(DreamKoalaDirection dir);
        DreamKoalaDirection getDir();
        
        void                walkToTargetX();
        void                stopWalking();
        
        bool                isStanding();
    
    protected:
        
        float               _targetX;
        int                 _floor;
        int                 _targetFloor;
        DreamKoalaDirection _dir;
    };
}


#endif // __IT_DREAMKOALA_H__
