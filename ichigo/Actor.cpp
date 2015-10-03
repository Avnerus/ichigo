#include "Actor.h"
#include "DataManager.h"

#include <iostream>


namespace ichigo {
    
    Actor::Actor() 
    : Agent()
    {
        _type = "Actor";
        _actorView = NULL;
    }

    
    Actor::~Actor() {
    }    
    
    
    // Initialize the actor
    bool Actor::init() {
        return Agent::init();
    }	
    
    
    // Set the view of this actor
    void Actor::setView(ActorView *view)
    {
        Agent::setView(view);
        _actorView = view;
    }
    
    
    // Config the actor from data in Json structure
    void Actor::deserialize(Json::Value &agentConfig)
    {
        Agent::deserialize(agentConfig);
    }


    // Gets called every frame
    void Actor::update(float dt) {
        Agent::update(dt);
    }
    
    
    // Adds a child to the actor
    bool Actor::addChild(Agent *actor, std::string name /* = "" */)
    {
        bool retVal = Agent::addChild(actor, name);
        
        if (retVal && _actorView && actor->getView())
        {
            _actorView->addChild((ActorView *)actor->getView());
        }
        
        return retVal;
    }
    
    
    // Adds a retained child as an actor
    bool Actor::addChild(std::tr1::shared_ptr<Agent> agent, std::string name /*= ""*/)
    {
        bool retVal = Agent::addChild(agent, name);
        
        if (retVal && _actorView && agent->getView())
        {
            _actorView->addChild((ActorView *)agent->getView());
        }
        
        return retVal;
    }

    
    // Removes a child from the actor
    void Actor::removeChild(ichigo::Agent *actor)
    {        
        if (_actorView && actor->getView())
        {
            _actorView->removeChild((ActorView *)actor->getView());
        }
        
        Agent::removeChild(actor);
    }
}