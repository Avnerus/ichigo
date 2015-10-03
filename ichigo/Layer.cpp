#include "Layer.h"
#include "DataManager.h"

#include <iostream>


namespace ichigo {
    
    Layer::Layer() : Agent() {
        _type = "Layer";
        _layerView = NULL;
    }

    
    Layer::~Layer() {
        std::cout << " Layer destroyed" << std::endl;
    }    
    
    
    // Initialize the layer
    bool Layer::init() {
        return Agent::init();
    }	   
    
    
    // Set the view of this layer
    void Layer::setView(ichigo::LayerView *view)
    {
        Agent::setView(view);
        _layerView = view;
    }
    
    
    // Load Layer paramteres from JSON structure
    void Layer::deserialize(Json::Value &agentConfig)
    {
        Agent::deserialize(agentConfig);
    }


    // Gets called every frame
    void Layer::update(float dt) {
        Agent::update(dt);
    }
    
    
    // Adds an actor to the layer
    bool Layer::addChild(Agent *actor, std::string name /* = "" */)
    {
        bool retVal = Agent::addChild(actor, name);
        
        if (retVal && _layerView && actor->getView())
        {
            _layerView->addActor((ActorView *)actor->getView());
        }
        
        return retVal;
    }
    
    
    // Adds a retained child as an actor
    bool Layer::addChild(std::tr1::shared_ptr<Agent> agent, std::string name /*= ""*/)
    {
        bool retVal = Agent::addChild(agent, name);
        
        if (retVal && _layerView && agent->getView())
        {
            _layerView->addActor((ActorView *)agent->getView());
        }
        
        return retVal;
    }
    
    
    // Removes an actor from the layer
    void Layer::removeChild(ichigo::Agent *actor)
    {        
        if (_layerView && actor->getView())
        {
            _layerView->removeActor((ActorView *)actor->getView());
        }

        Agent::removeChild(actor);
    }
}