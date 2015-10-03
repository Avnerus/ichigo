#include "Scene.h"
#include "DataManager.h"

#include <iostream>


namespace ichigo {
    
    Scene::Scene() : Agent() {
        _type = "Scene";
        _sceneView = NULL;
        _isCurrent = false;
        _wasLoaded = false;
    }

    
    Scene::~Scene() {
        std::cout << " Scene destroyed" << std::endl;
    }    
    

    // Initialize scene
    bool Scene::init() {
        return Agent::init();
    }
    
    
    // Set the view for this scene
    void Scene::setView(ichigo::SceneView *view)
    {
        Agent::setView(view);
        _sceneView = view;
    }
    
    
    // Loads specific scene parameters from the JSON structure
    void Scene::deserialize(Json::Value &agentConfig)
    {
        Agent::deserialize(agentConfig);
    }
    
    
    // Override the loadFromJSON method so the whole scene will not be created until the first time it is displayed
    void Scene::loadFromJSON(Json::Value &agentConfig)
    {
        // Save the config data for later use
        _configData = agentConfig;
    }
	
    
    // Gets called every frame, but only update if this is the current scene
	void Scene::update(float dt) {   
        if (_isCurrent)
        {
            Agent::update(dt);
        }
	}
    
    
    // Adds a layer to the scene
    bool Scene::addChild(Agent *layer, std::string name /* = "" */)
    {
        // std::cout << "Scene adding layer named " << name << std::endl;
        
        bool retVal = Agent::addChild(layer, name);
        
        if (retVal && _sceneView && layer->getView())
        {
            _sceneView->addLayer((LayerView *)layer->getView());
        }
        
        return retVal;
    }
    
    
    // Adds a retained child as a layer
    bool Scene::addChild(std::tr1::shared_ptr<Agent> agent, std::string name /*= ""*/)
    {
        bool retVal = Agent::addChild(agent, name);
        
        if (retVal && _sceneView && agent->getView())
        {
            _sceneView->addLayer((LayerView *)agent->getView());
        }
        
        return retVal;
    }
    
    
    // Removes a layer from the scene
    void Scene::removeChild(ichigo::Agent *layer)
    {        
        if (_sceneView && layer->getView())
        {
            _sceneView->removeLayer((LayerView *)layer->getView());
        }

        Agent::removeChild(layer);
    }
    
    
    // Set the scene to as the current active scene (or not)
    void Scene::setAsCurent(bool isCurrent)
    {
        // std::cout << "Scene::setAsCurrent" << std::endl;
        
        // Don't do anything if the status ain't changing
        if (isCurrent != _isCurrent)
        {
            // If the scene wasn't loaded yet, load it
            if (!_wasLoaded)
            {
                Agent::loadFromJSON(_configData);
                initChildren();
                _wasLoaded = true;
            }
            
            _isCurrent = isCurrent;
            
            if (_sceneView)
            {
                _sceneView->setAsCurrent(isCurrent);
            }
        }
    }
}