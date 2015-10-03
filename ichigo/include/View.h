#ifndef __ICHIGO_VIEW_H__
#define __ICHIGO_VIEW_H__

#include "Json/json.h"
#include "Point.h"
#include "Rect.h"

#include <string>
#include <queue>


namespace ichigo
{
    class Agent;
    
    
    class View
    {
    public:
        
        View(Agent *agent);
        virtual ~View();
        
        virtual void            init();
        virtual void            deserialize(Json::Value &configData);
        virtual void            update(float dt);
        
        virtual bool            isMoving();
        virtual void            moveTo(const Point &target, float duration);
        virtual void            moveBy(const Point &delta, float duration);
        virtual void            stopMoving();
        
        virtual void            setPosition(const Point &position);
        virtual const Point    &getPosition();
        virtual void            setScale(float scale);
        virtual float           getScale();
        virtual void            setAngle(float angle);
        virtual float           getAngle();
        virtual void            setZOrder(int zOrder);
        virtual int             getZOrder();
        virtual void            getZOrderPath(std::queue<int> &path);
        virtual void            setVisible(bool isVisible);
        virtual bool            isVisible();
        virtual void            setPivot(const Point &pivot) = 0;
        
        virtual bool            isTouched(const Point &touchPos);
        virtual Point           getPositionOnScreen();
        virtual bool            isScreenPointInside(const Point &screenPoint);
        virtual Point           convertLocalToScreen(const Point &localPos) = 0;
        virtual Point           convertScreenToLocal(const Point &screenPos) = 0;
        virtual float           getWorldScale();
        virtual Rect            getBoundingBox() = 0;
       
        Agent                  *getAgent();
        std::string             getType();
        virtual void           *getInternalData() = 0;
        
    protected:
        
        std::string     _type;
        Agent          *_agent;
        int             _zOrder;
        Point           _position;
        float           _scale;
        float           _angle;
        bool            _isVisible;
        
        bool            _isMoving;
        Point           _moveTarget;
        float           _moveDuration;
    };
}


#endif  // __ICHIGO_VIEW_H__
