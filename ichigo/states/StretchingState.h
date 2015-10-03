#ifndef __ICHIGO_STRETCHINGSTATE_H__
#define __ICHIGO_STRETCHINGSTATE_H__

#include "FSMState.h"
#include "Point.h"


namespace ichigo
{
    class StretchingState : public FSMState 
    {
    public:
        
        StretchingState(bool canDrag = true, bool canScale = true, bool canRotate = true, bool limitToBoundingBox = false);
        virtual ~StretchingState();

        virtual void init();
        
        void    setIdleStateName(std::string name);
        void    addTouchPoint(TouchPoint *touchPoint);
        void    setScaleLimits(float maxScale = 0, float minScale = 0);
        void    setTranslateLimits(bool whenMaximized, float minX, float maxX, float minY, float maxY);
        void    setLimitsForBounds(float minX, float minY, float maxX, float maxY);
        void    focusOnPoint(const Point &focusPoint);
        
        void    onTouchBegan(Agent *director);
        void    onTouchMoved(Agent *director);
        void    onTouchEnded(Agent *director);
        
    protected:
        
        virtual void    moveAgentToTouchPosition(TouchPoint *touchPoint);
        void            endDrag();
        void            keepInBounds();
        
        std::string     _idleStateName;
        int             _touchID1;
        int             _touchID2;
        Point           _touchPoint1;
        Point           _touchPoint2;
        bool            _canDrag;
        bool            _canScale;
        bool            _canRotate;
        bool            _limitToBoundingBox;
        float           _maxScale;
        float           _minScale;
        Point           _boundsMin[2];
        Point           _boundsMax[2];
    };
}


#endif // __ICHIGO_STRETCHINGSTATE_H__
