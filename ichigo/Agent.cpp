#include "Agent.h"
#include "AgentFactory.h"
#include "DataManager.h"
#include "Director.h"
#include "FSMState.h"

#include <iostream>


namespace ichigo 
{
    Agent::Agent() : _fsm(this) {
        _type = "Agent";
        _childCounter = 0;
        _parent = NULL;
        _scripted = false;
    }

    
    Agent::~Agent() {
        // std::cout << _type << " really destroyed" << std::endl;
        
        _children.clear();
    }
    
	
    // Return the type of the agent
	std::string Agent::getType() {
		return _type;
	}
    
    
    // Returns the name of the agent
    std::string Agent::getName()
    {
        std::string retVal = "";
        
        // The name is saved in the parent, so we first need to get it, if one exists
        if (_parent)
        {
            bool foundName = false;
            AgentList &siblins = _parent->getChildren();
            for (AgentList::iterator it = siblins.begin(); it != siblins.end() && !foundName; it++)
            {
                // If this child is the current agent, save the name and exit
                if (it->second.get() == this)
                {
                    retVal = it->first;
                    foundName = true;
                }
            }
        }
        
        return retVal;
    }
	
    
    // Get a pointer to the Agent's FSM
	FSM* Agent::getFSM() {
		return &_fsm;
	}
    
    
    // Get a pointer to the Agent's View
    View *Agent::getView()
    {
        return _view.get();
    }
	
    
    // Initialize Agent
	bool Agent::init() {  
	    // Init all states first
        StateList &stateList = _fsm.getStates();
        for (StateList::iterator it = stateList.begin(); it != stateList.end(); it++) {
            (*it)->init();
        }
	    
        return true;	    
	}
    
    
    // Set the view for this agent
    void Agent::setView(ichigo::View *view) {
        _view = std::tr1::shared_ptr<View>(view);    
        _view->init();   
    }    
    
    
    // Upate agent
    void Agent::update(float dt)
    {
        // First update this agent's FSM
        _fsm.update(dt);
        
        // Update the agent's view
        if (_view)
        {
            _view->update(dt);
        }
        
        // Update all children
        for (AgentList::iterator it = _children.begin(); it != _children.end(); it++)
        {
            it->second->update(dt);
        }
    }
    
    
    // Add a child agent under this agent, with the given name. If the name already exists in the child list,
    // return false. If no name is given, give some unique name.
    bool Agent::addChild(Agent *agent, std::string name /* = "" */)
    {
        // If name wasn't provided, select a unique name
        if (name == "")
        {
            name = "child" + _childCounter;
        }
        else if (_children.find(name) != _children.end())
        {
            // Make sure the name wasn't used
            return false;
        }
        
        // Add agent to child list
        agent->setParent(this);
        _children[name] = std::tr1::shared_ptr<Agent>(agent);
        _childCounter++;
        
        return true;
    }
    
    
    // Add a retained agent as a child. Probably retained before removed from different parent
    bool Agent::addChild(std::tr1::shared_ptr<Agent> agent, std::string name /* = "" */)
    {
        // If name wasn't provided, select a unique name
        if (name == "")
        {
            name = "child" + _childCounter;
        }
        else if (_children.find(name) != _children.end())
        {
            // Make sure the name wasn't used
            return false;
        }
        
        // Add agent to child list
        agent->setParent(this);
        _children[name] = agent;
        _childCounter++;
        
        return true;
    }
    
    
    // Remove a given agent from the child list
    void Agent::removeChild(Agent *agent)
    {
        // Find agent in child list
        AgentList::iterator it;
        for (it = _children.begin(); it != _children.end(); it++)
        {
            // If this is the correct agent, remove it and exit
            if (it->second.get() == agent)
            {
                agent->setParent(NULL);
                _children.erase(it);
                return;
            }
        }
    }
    
    
    // Remove an agent with the provided name from the child list
    void Agent::removeChild(std::string name)
    {
        // Find agent in child list
        Agent *childAgent = getChild(name);
        
        // If found, delete
        if (childAgent)
        {
            removeChild(childAgent);
        }
    }
    
    
    // Locate a child agent with a given name
    Agent *Agent::getChild(std::string name)
    {
        Agent *retVal = NULL;
        
        // Find agent in child list
        AgentList::iterator it = _children.find(name);
        if (it != _children.end())
        {
            // Agent found, return pointer to it
            retVal = it->second.get();
        }
        
        // No child with given name found
        return retVal;
    }
    
    
    // Returns a smart pointer to a child, so caller can hold onto it to retain it
    std::tr1::shared_ptr<Agent> Agent::retainChild(Agent *agent)
    {
        // Find agent in child list
        for (AgentList::iterator it = _children.begin(); it != _children.end(); it++)
        {
            if (it->second.get() == agent)
            {
                return it->second;
            }
        }
        
        return std::tr1::shared_ptr<Agent>();
    }
    
    
    // Locate a descendant agent (recursivly through the tree) with the provided name, NULL if not found
    Agent *Agent::findByName(std::string name)
    {
        // First check if requested agent is in the direct descendants
        Agent *retVal = getChild(name);
        
        // If not found, look for it in all of the agent's children
        if (!retVal)
        {
            for (AgentList::iterator it = _children.begin(); it != _children.end() && !retVal; it++)
            {
                retVal = it->second->findByName(name);
            }
        }
        
        return retVal;
    }
    
    void Agent::initWithChildren() {
        // std::cout << "Agent::initWithChildren() - Init " << getName() << std::endl;
        init();
        initChildren();
    }
    
    void Agent::initChildren() {
          
        // std::cout << "Agent::initChildren() - " << _children.size() << " children " << std::endl;
        for (AgentList::iterator it = _children.begin(); it != _children.end(); it++) {
            it->second->initWithChildren();
        }
    }    
    
    // Locate a descendant agent (recursivly through the tree) with the provided type, NULL if not found
    Agent *Agent::findByType(std::string type)
    {
        Agent *retVal = NULL;
        
        // First look for the requested agent type in the direct descendants
        AgentList::iterator it;
        for (it = _children.begin(); it != _children.end() && !retVal; it++)
        {
            if (it->second->getType() == type)
            {
                retVal = it->second.get();
            }
        }
        
        // If not found, look for it in all of the agent's children
        if (!retVal)
        {
            for (it = _children.begin(); it != _children.end() && !retVal; it++)
            {
                retVal = findByType(type);
            }
        }
        
        return retVal;
    }
    
    
    // Returns the whole list of child agents
    AgentList &Agent::getChildren()
    {
        return _children;
    }
    
    
    // Sets the parent for this agent
    void Agent::setParent(ichigo::Agent *parent)
    {
        _parent = parent;
    }
    
    
    // Returns this agent's parent
    Agent *Agent::getParent()
    {
        return _parent;
    }
    
    
    Agent* Agent::getParentScene() {
        Agent* parent = getParent();
        while (parent) {
            if (parent->getParent()->getType() == "Director") {
                return parent;
            }
            else {
                parent = parent->getParent();
            }
        }
        return NULL;
    }
    
    // Loads data for this agent from a JSON value, and goes on to create its children if there are any.
    void Agent::loadFromJSON(Json::Value &agentConfig)
    {        
        // If the JSON file indicates this agent has children, create them and add.
        Json::Value &children = agentConfig["children"];
        for (int i = 0; i < children.size(); i++)
        {
            Json::Value &child = children[i];
            
            // If this child is in an external file, load it
            if (child.isMember("useFile"))
            {
                std::cout << "Using child JSON: " << child["useFile"].asString() << std::endl;
                Json::Value externalData = DataManager::getInstance()->loadFromJSON(child["useFile"].asString());
                child.swap(externalData);
            }
            
            // Make sure this is a legal agent, it must have a type
            if (child.isMember("type"))
            {
                // Attempt to create the agent
                Agent *childAgent = AgentFactory::createAgent(child["type"].asString());
                if (childAgent)
                {
                    // Load the child agent from it's data (recursivly)
                    childAgent->loadFromJSON(child);
                    
                    // Add to current agent
                    addChild(childAgent, DataManager::getString(child, "name", ""));
                }
            }
        }
        
        // Update parameters for this agent
        deserialize(agentConfig);
    }
    
    
    // Reads values from a JSON::Value and sets the agent's parameters accordingly
    void Agent::deserialize(Json::Value &agentConfig)
    {
        if (_view)
        {
            _view->deserialize(agentConfig);
        }
    }
    
    // Load a script
    void Agent::loadScript() {
        std::string scriptFileName = getName() + ".lua";
        bool result = Director::getInstance()->getScriptingEngine()->executeScriptFile(scriptFileName);
        if (result) {
            _scripted = true;
        }     
    }
    
    bool Agent::isScripted() {
        return _scripted;
    }    
    
}
