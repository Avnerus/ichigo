#include "ItemDragState.h"

#include "Director.h"
#include "SpriteActorView.h"
#include "TouchPoint.h"
#include "DataManager.h"


namespace koala
{
    ItemDragState::ItemDragState()
    {
        _name = "drag";
        _itemView = NULL;
        _touchID = -1;
        
        _eventCallbacks["OnTouchMoved"] = std::tr1::bind(&ItemDragState::onTouchMoved, this, _1);
        _eventCallbacks["OnTouchEnded"] = std::tr1::bind(&ItemDragState::onTouchEnded, this, _1);
    }
    
    
    ItemDragState::~ItemDragState()
    {
        
    }
    
    
    // Initialize state
    void ItemDragState::init()
    {
        FSMState::init();
        
        _itemView = (ichigo::SpriteActorView *)_agent->getView();
    }
    
    
    // Called when entering state
    void ItemDragState::onEnter()
    {
        FSMState::onEnter();
        
        if (_itemView && _touchID != -1)
        {
            _itemView->playAnimation(_name);
            _itemView->fadeTo(0.6f, 1.5f);
            
            _initialPos = _itemView->getPosition();
        }
    }
    
    
    // Called when transitioning to another state
    void ItemDragState::onExit()
    {
        FSMState::onExit();
        
        if (_itemView)
        {
            _itemView->fadeTo(1.0f, 0.5f);
            _itemView->moveTo(_initialPos, 0.5f);
        }
    }
    
    
    // Called every frame
    void ItemDragState::onUpdate(float dt)
    {
        FSMState::onUpdate(dt);
    }
    
    
    // Called by the previous state to set the touch ID the drag should follow
    void ItemDragState::setTouchID(int touchID)
    {
        _touchID = touchID;
    }
    
    
    // Called every time touch has been moved
    void ItemDragState::onTouchMoved(ichigo::Agent *agent)
    {
        ichigo::Director *director = (ichigo::Director *)agent;
        ichigo::TouchPoint *tp = director->getTouchPoint(_touchID);
        
        if (tp)
        {
            ichigo::Point localPos = _itemView->convertScreenToLocal(tp->getPos());
            localPos.x += CONST_FLOAT("ITEM_DRAG_OFFSET_X");
            localPos.y += CONST_FLOAT("ITEM_DRAG_OFFSET_Y");
            _itemView->setPosition(localPos);
        }
        else
        {
            endDrag();
        }
    }
    
    
    // Called when touch has ended
    void ItemDragState::onTouchEnded(ichigo::Agent *agent)
    {
        ichigo::Director *director = (ichigo::Director *)agent;
        ichigo::TouchPoint *tp = director->getTouchPoint(_touchID);
        
        if (tp && tp->hasEnded())
        {
            endDrag();
        }
    }
    
    
    // Ends the dragging process
    void ItemDragState::endDrag()
    {
        _touchID = -1;
        _agent->getFSM()->transitionTo("onTable");
    }
}