#include "ItemOnTableState.h"
#include "ItemDragState.h"

#include "Agent.h"
#include "Director.h"
#include "TouchPoint.h"


namespace koala
{
    ItemOnTableState::ItemOnTableState()
    {
        _name = "onTable";
        _itemView = NULL;
        
        _eventCallbacks["OnTouchStarted"] = std::tr1::bind(&ItemOnTableState::onTouchStarted, this, _1);
    }
    
    
    ItemOnTableState::~ItemOnTableState()
    {
        
    }
    
    
    // Initialize state
    void ItemOnTableState::init()
    {
        FSMState::init();
        
        _itemView = (ichigo::SpriteActorView *)_agent->getView();
    }
    
    
    // Called when state is entered
    void ItemOnTableState::onEnter()
    {
        FSMState::onEnter();
        
        if (_itemView)
        {
            _itemView->playAnimation(_name);
        }
    }
    
    
    // Called when transitioning to another state
    void ItemOnTableState::onExit()
    {
        FSMState::onExit();
    }
    
    
    // Called every frame
    void ItemOnTableState::onUpdate(float dt)
    {
        FSMState::onUpdate(dt);
    }
    
    
    // Called when touch has begun
    void ItemOnTableState::onTouchStarted(ichigo::Agent *agent)
    {
        ichigo::Director *director = (ichigo::Director *)agent;
        ichigo::TouchList &touches = director->getTouchList();
        
        if (touches.size() == 1)
        {
            ichigo::TouchPoint *tp = touches.begin()->second.get();
            
            if (!tp->wasHandled() && _itemView && _itemView->isTouched(tp->getPos()))
            {
                tp->markAsHandled();
                ItemDragState *dragState = (ItemDragState *)_agent->getFSM()->transitionTo("drag");
                dragState->setTouchID(tp->getID());
            }
        }
    }
}
