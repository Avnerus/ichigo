#ifndef __KOALA_OFFICE_H__
#define __KOALA_OFFICE_H__

#include "Actor.h"
#include "Point.h"
#include "TileMapView.h"
#include "DataManager.h"

#include <map>


namespace koala
{
    class DreamKoala;
    class Item;
    
    
    class LiftData 
    {
    public:
        
        ichigo::Agent  *doorSprite;
        bool            isOpen;
    };
    
    
    class PortalData
    {
    public:
        PortalData(std::string area, int row, int col) : targetArea(area), targetRow(row), targetCol(col) {};
        
        std::string     targetArea;
        int             targetRow;
        int             targetCol;
    };
    
    
    class ObjectData
    {
    public:
        ObjectData(std::string objType, ichigo::Agent *objAgent, float interPtX, const ichigo::Point &itemPos) 
        : type(objType), agent(objAgent), interactionPointX(interPtX), itemAnchor(itemPos), item(NULL) {};
        
        std::string     type;
        ichigo::Agent  *agent;
        float           interactionPointX;
        ichigo::Point   itemAnchor;
        Item           *item;
    };
    
    
    class AreaData
    {
    public:
        AreaData(std::string areaName) : name(areaName), tileMap(NULL) {};
        
        std::string                                 name;
        ichigo::TileMapView                        *tileMap;
        std::map<int, LiftData *>                   lifts;
        std::map<int, std::map<int, PortalData *> > portals;
        std::map<int, std::map<int, ObjectData *> > objects;
    };

    
    class Office : public ichigo::Actor
    {
    public:
        
        Office();
        virtual ~Office();
        
        virtual bool    init();
        virtual void    deserialize(Json::Value &agentConfig);
        
        void            setCurrentArea(const std::string &areaName);
        AreaData       *getCurrentArea();
        ichigo::Point   enterPortal();
        
        void            handleClick(ichigo::Point &touchPoint);
        void            orderLift();
        void            moveLiftToFloor(int floor);
        void            openLift();
        void            closeLift();
        int             getFloorForTilePos(float y);
        
        void            onLiftOpened();
        void            onLiftClosed();
        
    protected:
        
        void                                initOffice();
        void                                initArea(const std::string &areaName);
        void                                initPortal(Json::Value &portalData);
        void                                initObject(Json::Value &objectData);
        Item                               *initItem(const std::string &item);
        void                                setViewForArea();
        
        DreamKoala                         *_dreamKoala;
        AreaData                           *_currArea;
        std::map<std::string, AreaData *>   _areas;
        
        Json::Value                         _initData;
    };
}


#endif // __KOALA_OFFICE_H__
