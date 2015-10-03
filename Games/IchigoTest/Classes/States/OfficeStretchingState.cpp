#include "OfficeStretchingState.h"
#include "Office.h"

#include "Director.h"
#include "TouchPoint.h"
#include "Point.h"
#include "DataManager.h"


namespace it
{
    OfficeStretchingState::OfficeStretchingState()
    : ichigo::StretchingState(true, true, false)
    {
        _name = "OfficeStretching";
        _touchPointMoved = false;

        // Override StretchingState touch handlers
        _eventCallbacks["OnTouchMoved"] = std::tr1::bind(&OfficeStretchingState::onTouchMoved, this, _1);
        _eventCallbacks["OnTouchEnded"] = std::tr1::bind(&OfficeStretchingState::onTouchEnded, this, _1);
        _eventCallbacks["ANIM_OVER_opening"] = std::tr1::bind(&OfficeStretchingState::onLiftOpened, this, _1);
        _eventCallbacks["ANIM_OVER_closing"] = std::tr1::bind(&OfficeStretchingState::onLiftClosed, this, _1);
        _eventCallbacks["LiftArrived"] = std::tr1::bind(&OfficeStretchingState::onLiftArrived, this, _1);
    }
    
    
    OfficeStretchingState::~OfficeStretchingState()
    {
        
    }
    
    
    // Gets called when a touch is dragging or stretching the office. In this case we mark it so touch isn't considered as an
    // interaction with the office itself
    void OfficeStretchingState::onTouchMoved(ichigo::Agent *director)
    {
        ichigo::TouchPoint *tp = ((ichigo::Director *)director)->getTouchPoint(_touchID1);
        if (tp && !_touchPointMoved && tp->getPos().distanceTo(_touchPoint1) >= CONST_FLOAT("OFFICE_INTERACTION_DRAG_THRESHOLD"))
        {
            _touchPointMoved = true;
        }
        
        StretchingState::onTouchMoved(director);
    }
    
    
    // Handle touch ended events. If office was touched without moving, OfficeMgr should handle it. Otherwise drag or stretch.
    void OfficeStretchingState::onTouchEnded(ichigo::Agent *director)
    {
        // When touch has ended, consider it as an office interaction only if there was one touch, it hadn't moved, and it is this touch which
        // is ending
        ichigo::TouchPoint *tp = ((ichigo::Director *)director)->getTouchPoint(_touchID1);
        if (!_touchPointMoved && _touchID2 == 0 && (!tp || tp->hasEnded()))
        {
            _touchID1 = 0;
            _touchID2 = 0;
            
            Office *office = (Office *)_agent;
            office->handleClick(_touchPoint1);
        }
        else
        {
            // Handle dragging normally
            ichigo::StretchingState::onTouchEnded(director);
        }
        
        // If touch ended with (office interaction or without), reset move flag
        if (_touchID1 == 0)
        {
            _touchPointMoved = false;
        }
    }
    
    
    // Called when an elivator door finished opening
    void OfficeStretchingState::onLiftOpened(ichigo::Agent *agent)
    {
        ((Office *)_agent)->onLiftOpened();
    }
    
    
    // Called when lift arrived at the wanted floor and is ready to open
    void OfficeStretchingState::onLiftArrived(ichigo::Agent *agent)
    {
        ((Office *)_agent)->openLift();
    }
    
    
    // Called when the lift doors finished closing
    void OfficeStretchingState::onLiftClosed(ichigo::Agent *agent)
    {
        ((Office *)_agent)->onLiftClosed();
    }
}
