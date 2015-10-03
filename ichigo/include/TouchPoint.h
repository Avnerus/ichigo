#ifndef __ICHIGO_TOUCHPOINT_H__
#define __ICHIGO_TOUCHPOINT_H__

#include "Point.h"


namespace ichigo 
{
    class TouchPoint
    {
    public:
        
        TouchPoint(int touchID = 0, float x = 0, float y = 0);
        ~TouchPoint();
        
        int             getID();
        void            setPos(const Point &pos);
        void            setPos(float x, float y);
        const Point    &getPos();
        const Point    &getPrevPos();
        void            markAsHandled(bool handled = true);
        bool            wasHandled();
        void            markAsEnded();
        bool            hasEnded();
        
    protected:
        
        int     _touchID;
        Point   _pos;
        Point   _prevPos;
        bool    _handled;
        bool    _hasEnded;
    };
}


#endif  // __ICHIGO_TOUCHPOINT_H__
