#ifndef __KOALA_DREAMKOALA_H__
#define __KOALA_DREAMKOALA_H__

#include "Character.h"


namespace koala
{
    enum DreamKoalaDirection
    {
        DKD_LEFT,
        DKD_RIGHT,
        DKD_IN,
        DKD_OUT
    };
    
    class DreamKoala : public ichigo::Character
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
        void                enterDoor();
        void                doorEntered();
        bool                isEnteringDoor();
        void                useObject(std::string type, int objZOrder);
        void                endObjectInteraction();
        bool                shouldInteractWithObject();
        DreamKoalaDirection getInteractionDirection();
        std::string         getInteractionType();
        
        void                walkToTargetX();
        void                stopWalking();
        
        bool                isStanding();
    
    protected:
        
        float               _targetX;
        int                 _floor;
        int                 _targetFloor;
        bool                _enterDoor;
        DreamKoalaDirection _dir;
        std::string         _interactWithObjectType;
        int                 _interactWithZOrder;
    };
}


#endif // __KOALA_DREAMKOALA_H__
