#ifndef __ICHIGO_FSMSTATE_H__
#define __ICHIGO_FSMSTATE_H__

#include <map>

#include "EventManager.h"


using namespace std::tr1::placeholders;


namespace ichigo {

    class Agent;
    	
    class FSMState {
        
    public:
        FSMState();
        virtual ~FSMState();
        
        virtual void onUpdate(float dt);
        virtual void onEnter();
        virtual void onExit();
        virtual void init();
        
        void        subscribeEvents();
        void        dispatchEvent(EventType event, Agent* agent);
        bool        isCurrent();
        
        std::string getName();
        void        setAgent(Agent* agent);
        Agent      *getAgent();
        
    protected:        
        Agent                              *_agent;
        std::map<EventType, EventCallback>  _eventCallbacks;          
        std::string                         _name;
        bool                                _hasSubscribed;
        
        void unsubscribeEvents();   
    };
}


#endif  // __ICHIGO_FSMSTATE_H__