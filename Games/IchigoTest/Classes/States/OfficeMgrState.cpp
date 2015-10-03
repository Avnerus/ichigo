#include "OfficeMgrState.h"
#include "Office.h"


namespace it
{
    OfficeMgrState::OfficeMgrState()
    {
        _name = "OfficeMgr";
        _stretchingStateName = "OfficeStretching";

        _eventCallbacks["ANIM_OVER_opening"] = std::tr1::bind(&OfficeMgrState::onLiftOpened, this, _1);
        _eventCallbacks["ANIM_OVER_closing"] = std::tr1::bind(&OfficeMgrState::onLiftClosed, this, _1);
        _eventCallbacks["LiftArrived"] = std::tr1::bind(&OfficeMgrState::onLiftArrived, this, _1);
    }
    
    
    OfficeMgrState::~OfficeMgrState()
    {
    }
    
    
    // Called when a lift door finished opening
    void OfficeMgrState::onLiftOpened(ichigo::Agent *agent)
    {
        ((Office *)_agent)->onLiftOpened();
    }
    
    
    // Called when lift arrived at the wanted floor and is ready to open
    void OfficeMgrState::onLiftArrived(ichigo::Agent *agent)
    {
        ((Office *)_agent)->openLift();
    }
    
    
    // Called when the lift doors finished closing
    void OfficeMgrState::onLiftClosed(ichigo::Agent *agent)
    {
        ((Office *)_agent)->onLiftClosed();
    }
}