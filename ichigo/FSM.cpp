#include "FSM.h"
#include "ichigo.h"

#include <iostream>


namespace ichigo 
{    
    FSM::FSM(Agent *agent)
    {
        // std::cout << "FSM Created" << std::endl;
        
        _agent = agent;
        _currentState = NULL;
        _delayedState = NULL;
        _statesSubscribed = false;
    }
    
    
    FSM::~FSM()
    {
        // std::cout << "FSM Destroyed" << std::endl;
    
        _states.clear();
    }
    
    
    // Gets called each tick by the Agent
    void FSM::update(float dt)
    {     
        // Check if there is a transition request
        if (_delayedState)
        {
            transitionTo(_delayedState);
            _delayedState = NULL;
        }
        
        // On first update, subscribe events of all states. This is done here to make sure all states were already added, and
        // the director has an active scene (needed for subscribing to the EventManager)
        if (!_statesSubscribed)
        {
            for (StateList::iterator it = _states.begin(); it != _states.end(); it++)
            {
                (*it)->subscribeEvents();
            }
            
            _statesSubscribed = true;
        }
        
        // Call the update function of the current state
        if (_currentState)  
        {
            _currentState->onUpdate(dt);
        }        
    }
    
    
    // Called to transition to another state. The transition will occur during next update. The schedualled state is returned
    // and can be used to call methods before it's onEnter, or NULL if the state doesn't exist.
    FSMState *FSM::transitionTo(std::string stateName)
    {        
        // Find the named state
        StateList::iterator stateIter;
        
        for(stateIter = _states.begin(); stateIter != _states.end(); stateIter++)
        {
            if ((*stateIter)->getName() == stateName)
            {
                _delayedState = (*stateIter).get();
            }
        }
        
        return _delayedState;
    }
    
    
    // Actual transition between states, called by an update() method of a state with a delayed transition request
    void FSM::transitionTo(FSMState *state)
    {        
        // Error, trying to transition to a non-existant state
        if (!state)
        {
            return;
        }

        std::cout << _agent->getName() <<  ": Transition to " << state->getName() << std::endl;

        // Finish up current state
        if (_currentState) 
        {
            _currentState->onExit();      
        }
        
        // Start new state and make it current
        state->onEnter();
        _currentState = state;
        
        // std::cout << "Finished transition to " << state->getName() << std::endl;
    }
    
    
    //Add a state to the list, optionally make it the current state
    void FSM::addState(FSMState *newState, bool makeCurrent = false)
    {
        //Add this state to the FSM
        newState->setAgent(_agent);  
        std::tr1::shared_ptr<FSMState> sharedState = std::tr1::shared_ptr<FSMState>(newState);
        _states.push_back(sharedState);
        
        //Make this the current state?
        if (makeCurrent) 
        {
            _delayedState = sharedState.get();
        }

        // std::cout << "Added state " << newState->getName() << std::endl;
    }
    
    
    // Returns the current state running
    FSMState *FSM::getCurrentState() 
    {
        if (_delayedState) {
            return _delayedState;
        }
        else {
            return _currentState;
        }        
    }
    
    
    // Returns a requested state by state name, null if state doesn't exist in FSM
    FSMState *FSM::getState(std::string stateName)
    {
        FSMState *retVal = NULL;
        
        for (StateList::iterator it = _states.begin(); it != _states.end(); it++)
        {
            if ((*it)->getName() == stateName)
            {
                retVal = (*it).get();
            }
        }        
        return retVal;
    }
    
    StateList &FSM::getStates() {
        return _states;
    }
}