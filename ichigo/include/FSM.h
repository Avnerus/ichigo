#ifndef __ICHIGO_FSM_H__
#define __ICHIGO_FSM_H__


#include <string>
#include <vector>
#include <tr1/memory>


namespace ichigo 
{
    class Agent;
    class FSMState;

    //A vector of shared pointers housing all the states in the machine
    typedef std::vector< std::tr1::shared_ptr<FSMState> > StateList;

    
    //A Simple Finite State Machine
    class FSM 
    {
    public:
        
        FSM(Agent *agent);
        ~FSM();
        
        void        update(float dt);
        
        FSMState   *transitionTo(std::string stateName);
        void        addState(FSMState *newState, bool makeCurrent);
        FSMState   *getCurrentState();    
        FSMState   *getState(std::string stateName);
        StateList &getStates();

    protected:

        void            transitionTo(FSMState *state);

        Agent          *_agent;
        FSMState       *_currentState;
        FSMState       *_delayedState;
        StateList       _states; 
        bool            _statesSubscribed;
    };
}


#endif // __ICHIGO_FSM_H__