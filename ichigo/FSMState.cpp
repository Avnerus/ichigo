#include "FSMState.h"
#include "Agent.h"

#include <iostream>


namespace ichigo {
    
    FSMState::FSMState() {
        // std::cout << "FSMState created." << std::endl;
        
        _agent = NULL;
        _hasSubscribed = false;
        _name = "unnamed_state";
    }
    
    
    FSMState::~FSMState() {
        // std::cout << "FSMState destroyed. Usubscribing events" << std::endl;
        
        unsubscribeEvents();
    }
      
    
    // Returns the name of this state. A derived class should set the name in its constructor
    std::string FSMState::getName()  {
        return _name;
    }


    // Point the state to the agent it is managing
    void FSMState::setAgent(Agent* agent) {
        _agent = agent;
    }
    
    
    // Returns the agent the state is managing
    Agent *FSMState::getAgent()
    {
        return _agent;
    }
    
    
    // Is this state the currently running one in the FSM?
    bool FSMState::isCurrent() {
        bool retVal = false;
        
        if (_agent) {
            retVal = (_agent->getFSM()->getCurrentState() == this);
        }

        return retVal;   
    }


    // Subscribe this state to all the events in the list (hopefully) filled in by the derived class's constructor. This method is called
    // during the first onUpdate of the FSM
    void FSMState::subscribeEvents() {
        
        if (!_hasSubscribed)
        {
            EventManager* eventManager = EventManager::getInstance(); 
            std::map<EventType, EventCallback>::iterator eventIterator;
        
            for (eventIterator = _eventCallbacks.begin(); eventIterator != _eventCallbacks.end(); eventIterator++) {
                eventManager->subscribe(this, eventIterator->first);
            }
            
            _hasSubscribed = true;
        }
    }

    
    // Unsubscribe this state from all the events
    void FSMState::unsubscribeEvents() {        
        EventManager* eventManager = EventManager::getInstance(); 
        std::map<EventType, EventCallback>::iterator eventIterator;
        
        for (eventIterator = _eventCallbacks.begin(); eventIterator != _eventCallbacks.end(); eventIterator ++) {
            eventManager->unsubscribe(this, eventIterator->first);
        }     
    }
    
    
    // Default empty update function for state
    void FSMState::onUpdate(float dt)
    {
    
    }
        
    
    // Default enter function for state. Handles event subscribing on first run
    void FSMState::onEnter() {

    }   
    
    
    // Default empty exit function for state
    void FSMState::onExit() {
    }
    
    
    // Default empty init function for state
    void FSMState::init() {
    }
    
    
    // Gets called when this state is the current state and a subscribed event has fired.
    // This method calls the appropriate callback function (in the derived class)
    void FSMState::dispatchEvent(EventType event, Agent* agent) {
        _eventCallbacks[event](agent);
    }
}