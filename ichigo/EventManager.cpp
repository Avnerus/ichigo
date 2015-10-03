#include "EventManager.h"
#include "Agent.h"
#include "Director.h"
#include "FSMState.h"
#include "TouchPoint.h"

#include <iostream>


namespace ichigo {
    
    // This functor is used to sort two states in a set. States belonging to an agent with a higher z-order (taking into consideration
    // all scene graph levels) will appear earlier in the set
    bool StateSort::operator()(FSMState *state1, FSMState *state2)
    {
        return Director::getInstance()->isFirstAgentInFront(*(state1->getAgent()), *(state2->getAgent()));
    }
    
        
    EventManager EventManager::_instance;
    bool EventManager::_instanceInitialized = false;
    
    
    EventManager::EventManager() {
    }
    
    
    EventManager::~EventManager() {
    }   
    
    
    // Returns the singleton instance of this class, initializes on the first time
    EventManager* EventManager::getInstance()
    {
    	if (!_instanceInitialized)
    	{
    		_instance.init();
            _instanceInitialized = true;
    	}

    	return &_instance;
    }
    
    
    // Called during initialization
    bool EventManager::init() {
        std::cout << "Even Manager Initializing" << std::endl;        
		
		return true;
    }
    
    
    // Subscribe an FSMState to an event. Only subscribed states will be alerted when the event occurs
    void EventManager::subscribe(FSMState* state, EventType event) {
        
        // If this is a Director event, add to all scenes
        if (state->getAgent() == Director::getInstance())
        {
            AgentList &sceneList = Director::getInstance()->getChildren();
            for (AgentList::iterator it = sceneList.begin(); it != sceneList.end(); it++)
            {
                SortedStateList &stateList = _subscribers[(Scene *)it->second.get()][event];
                stateList.insert(state);
            }
        }
        else
        {
            // If the agent isn't the director, get events only in the current scene
            SortedStateList &stateList = _subscribers[Director::getInstance()->getCurrentScene()][event];
            stateList.insert(state);   
        }
    }
    
    
    // Unsubscribe an FSMState from an event. This state will no longer get alerted when an event occurs.
    void EventManager::unsubscribe(FSMState* state, EventType event) {
        
        // Go over all scenes in list
        for (SubscriberList::iterator it = _subscribers.begin(); it != _subscribers.end(); it++)
        {
            if (!it->second.empty() && it->second.find(event) != it->second.end())
            {
                SortedStateList *states = &(it->second[event]);
                states->erase(states->find(state));
            }            
        }

    }
    
    
    // This method goes over all subscribed events for the current scene, unsubscribes them and re-subscribes them, thus forcing
    // them to be sorted. This might be needed after z-orders have changed. It might be heavy, and not always needed, so it is not 
    // called automatically after every call to setZOrder, you need to call it when needed
    void EventManager::resortSceneEvents()
    {
        // Go over all event types in the scene
        SceneSubscriberList &sceneEvents = _subscribers[Director::getInstance()->getCurrentScene()];
        for (SceneSubscriberList::iterator it1 = sceneEvents.begin(); it1 != sceneEvents.end(); it1++)
        {
            // Go over all states subscribed to that event
            SortedStateList &stateList = it1->second;
            SortedStateList newStateList;
            for (SortedStateList::iterator it2 = stateList.begin(); it2 != stateList.end(); it2++)
            {
                // We souldn't play with a list's members while iterating it, so we add each state to a new list
                FSMState *state = (*it2);
                newStateList.insert(state);
            }
            
            // Swap the old state list with the new, sorted list
            stateList.swap(newStateList);
        }
    }
    
    
    // An event occured, alert all subscribed states (which are currently running in the current scene)
    void EventManager::publish(EventType event, Agent* agent) 
    {        
        SortedStateList::iterator iter;                
        SortedStateList *states = &_subscribers[Director::getInstance()->getCurrentScene()][event];
                
        for (iter = states->begin(); iter != states->end() ; iter++) 
        {
            if ((*iter)->isCurrent()) 
            {
                (*iter)->dispatchEvent(event, agent);                               
            }   
        }        
    }   

    
    // This method updates the touch list and raises the event of a touch started. It should be called by whatever
    // implementation for each touch starting. So for example, with a cocos2d implementation, some CCLayer should 
    // handle all touch events and pass each one to this method
    void EventManager::onTouchStarted(TouchPoint *touch)
    {
        // Add touch to list in director
        Director *director = Director::getInstance();
        director->addTouchPoint(touch);
        
        // Raise the event
        publish("OnTouchStarted", director);
    }
    
    
    // This method updates the touch list and raises the event of a touch move.
    void EventManager::onTouchMoved(TouchPoint *touch)
    {
        // Find touch in list of touches. Only if it already exists, update it.
        Director *director = Director::getInstance();
        TouchPoint *existingTouch = director->getTouchPoint(touch->getID());
        if (existingTouch)
        {
            existingTouch->setPos(touch->getPos());
            
            // Raise the event
            publish("OnTouchMoved", director);
        }
    }
    
    
    // This method updates the touch list and raises the event of a touch finished
    void EventManager::onTouchEnded(TouchPoint *touch)
    {
        Director *director = Director::getInstance();
        
        // Find the touch in the existing touch list, make sure it was known to the system.
        TouchPoint *existingTouch = director->getTouchPoint(touch->getID());
        if (existingTouch)
        {
            // First update the touch to its final position
            existingTouch->setPos(touch->getPos());
            existingTouch->markAsEnded();
            
            // Raise the event and allow final handling
            publish("OnTouchEnded", director);
            
            // Now that the touch handling has ended, it can be erased from the list
            director->removeTouchPoint(touch->getID());
        }
    }
}