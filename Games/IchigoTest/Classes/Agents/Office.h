#ifndef __IT_OFFICE_H__
#define __IT_OFFICE_H__

#include "Actor.h"
#include "Point.h"
#include "TileMapView.h"
#include <map>


namespace it
{
    class DreamKoala;
    
    class LiftData 
    {
    public:
        
        ichigo::Agent  *doorSprite;
        bool            isOpen;
    };
    
    class Office : public ichigo::Actor
    {
    public:
        
        Office();
        virtual ~Office();
        
        virtual void    update(float dt);
        
        void            handleClick(ichigo::Point &touchPoint);
        void            orderLift();
        void            moveLiftToFloor(int floor);
        void            openLift();
        void            closeLift();
        
        void            onLiftOpened();
        void            onLiftClosed();
        
    protected:
        
        void                        initOfficeMgr();
        int                         getFloorForTilePos(float y);
        
        DreamKoala                 *_dreamKoala;
        ichigo::TileMapView        *_tilemap;
        
        std::map<int, LiftData *>   _liftsData;
    };
}


#endif // __IT_OFFICE_H__
