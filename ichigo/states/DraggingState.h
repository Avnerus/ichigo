#ifndef __ICHIGO_DRAGGINGSTATE_H__
#define __ICHIGO_DRAGGINGSTATE_H__


#include "FSMState.h"
#include "Point.h"


namespace ichigo {
    
    class DraggingState : public FSMState  {

    public:
        
        DraggingState();
        virtual ~DraggingState();
      
        void setIdleStateName(std::string name);
        void setDraggingTouchID(int id);
        void setTouchOffset(const Point &touchOffset);
        void setPositionBounds(float minX, float maxX, float minY, float maxY);
        
        void onTouchMoved(Agent* director);
        void onTouchEnded(Agent* director);

    protected:
        
        void moveActorToTouchPosition(TouchPoint *touchPoint);
        void endDrag();
        
        std::string _idleStateName;
        int         _draggingTouchID;
        Point       _touchOffset;
        Point       _boundsMin;
        Point       _boundsMax;
    };
}

#endif  // __ICHIGO_DRAGGINGSTATE_H__