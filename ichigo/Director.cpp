#include "Director.h"
#include "Scene.h"
#include "TouchPoint.h"
#include "DataManager.h"
#include "ScriptingEngine.h"
#include "Utils.h"

#include <iostream>
#include <queue>


namespace ichigo 
{   
    // Singleton instance
    Director Director::_instance;
    bool Director::_isInitialized = false;
    
    
    Director::Director() : Agent() {
        // std::cout << _type << " director constructed" << std::endl;  
        
        _type = "Director";
        _directorView = NULL;
        _currentScene = NULL;
        _nextTimerID = 0;
    }
    
    std::string Director::getName() {
        return "Director";
    }
    
    Director::~Director() {
        std::cout << _type << " destroyed" << std::endl;   
    }    
    
    
    void Director::setScenesFileName(std::string fileName) {
        _scenesFilename = fileName;
    }
    
    // Singleton static method get instance, initialize if needed
    Director* Director::getInstance()
    {
        if (!_isInitialized)
    	{
    		_instance.init();
            _isInitialized = true;
    	}
    	
    	return &_instance;
    }

    
    // Initialize Director agent
    bool Director::init() {
        Agent::init();
        
        _type = "Director";

        return true;
    }
    
    
    // Set the view for the agent
    void Director::setView(ichigo::DirectorView *view)
    {
        Agent::setView(view);
        
        _directorView = view;
    }
    
    
    void Director::start() {
        Utils::seedRand();
        
        Json::Value root = ichigo::DataManager::getInstance()->loadFromJSON(_scenesFilename);
        loadFromJSON(root);
        initWithChildren();
        setCurrentScene(_currentSceneName);
    }
    
    
    // Sets the directors value according to a Json structure
    void Director::deserialize(Json::Value &agentConfig)
    {
        Agent::deserialize(agentConfig);
        
        if (agentConfig.isMember("firstScene"))
        {
            _currentSceneName = DataManager::getString(agentConfig, "firstScene", "");
        }
    }
    
    
    // Gets called every frame
    void Director::update(float dt) 
    {
        Agent::update(dt);
        
        // Go over the timers and dispatch the needed ones
        for (TimerList::iterator it = _timers.begin(); it != _timers.end(); it++)
        {
            handleTimer(it->first, it->second.get(), dt);
        }
    }
    
    
    // Adds a scene to the director
    bool Director::addChild(Agent *scene, std::string name /* = "" */)
    {
        bool retVal = Agent::addChild(scene, name);
        
        if (retVal && _directorView && scene->getView())
        {
            _directorView->addScene((SceneView *)scene->getView());
        }
        
        return retVal;
    }
    
    
    // Adds a retained child as a scene
    bool Director::addChild(std::tr1::shared_ptr<Agent> agent, std::string name /*= ""*/)
    {
        bool retVal = Agent::addChild(agent, name);
        
        if (retVal && _directorView && agent->getView())
        {
            _directorView->addScene((SceneView *)agent->getView());
        }
        
        return retVal;
    }
    
    
    // Removes a scene from the director
    void Director::removeChild(ichigo::Agent *scene)
    {        
        if (_directorView && scene->getView())
        {
            _directorView->removeScene((SceneView *)scene->getView());
        }
        
        Agent::removeChild(scene);
    }
    
    
    // Set the scene with the given name as the currently running scene
    void Director::setCurrentScene(std::string name) {
        Agent *currScene = getChild(name);
        if (currScene)
        {
            _currentScene = (Scene *)currScene;
            
            // Update the directo's view to the current scene
            if (_directorView)
            {
                _directorView->setCurrentScene((SceneView *)currScene->getView());
            }
            
            // Go over all the scenes and update their "currentability"
            for (AgentList::iterator it = _children.begin(); it != _children.end(); it++)
            {
                Scene *itScene = (Scene *)it->second.get();
                itScene->setAsCurent(itScene == currScene);
            }
        }
    }
    
    
    // Returns the currently active scene
    Scene *Director::getCurrentScene() {
        return _currentScene;
    }
    	

    // Add a new touch point to the list of active touchpoints
    void Director::addTouchPoint(TouchPoint *touchPoint)
    {
        _touchPoints[touchPoint->getID()] = std::tr1::shared_ptr<TouchPoint>(touchPoint);
    }
    
    
    // Remove a touch point from the list (normally should be called when a touch ended)
    void Director::removeTouchPoint(int touchID)
    {
        // Find touch point in the list and make sure it exists
        TouchList::iterator it = _touchPoints.find(touchID);
        if (it != _touchPoints.end())
        {
            _touchPoints.erase(it);
        }
    }
    
    
    // Returns a touch point by its id, or null if id doesn't exist
    TouchPoint *Director::getTouchPoint(int touchID)
    {
        TouchPoint *retVal = NULL;
        
        if (_touchPoints.find(touchID) != _touchPoints.end())
        {
            retVal = _touchPoints[touchID].get();
        }
        
        return retVal;
    }
    
    
    // Returns the whole list of currently active touches
    TouchList &Director::getTouchList()
    {
        return _touchPoints;
    }
    
    
    // Creates a new timer. When "time" passes, "event" is published. If "loop" is true, the timer will be called until it is cancelled.
    // This method returns a unique timer ID. The ID can be used to remove a timer.
    int Director::addTimer(Agent* waitingAgent, const EventType &event, float time, bool loop /* = false */)
    {
        TimerTask *timer = new TimerTask();
        timer->event = event;
        timer->timer = time;
        timer->timeToNext = time;
        timer->loop = loop;
        timer->waitingAgent = waitingAgent;
        
        
        int timerID = _nextTimerID++;
        
        _timers[timerID] = std::tr1::shared_ptr<TimerTask>(timer);
        
        return timerID;
    }
    
    
    // Removes a specific timer. The ID is obtained while creating the timer, or recieved as an argument in the callback function
    void Director::removeTimer(int timerID)
    {
        TimerList::iterator it = _timers.find(timerID);
        if (it != _timers.end())
        {
            _timers.erase(it);
        }
    }
    
    
    // Clears all timers in the system
    void Director::clearAllTimers()
    {
        _timers.clear();
    }
    
    
    // Updates a single timer, dispatches the alert if it is time
    void Director::handleTimer(int timerID, ichigo::TimerTask *timer, float dt)
    {
        timer->timeToNext -= dt;
        
        // Time to dispatch?
        if (timer->timeToNext <= 0)
        {
            EventManager::getInstance()->publish(timer->event, timer->waitingAgent);
            
            if (timer->loop)
            {
                // Looping timer, restart it
                timer->timeToNext = timer->timer;
            }
            else
            {
                removeTimer(timerID);
            }
        }
    }
    
    
    // This method gets two agents and returns true if the first one if more forward (in z order) than the second one.
    // Notice that if one of the agents is null, isn't part of the scene graph, or both agents are not part of the same
    // scene, the result is meaningless.
    bool Director::isFirstAgentInFront(ichigo::Agent &firstAgent, ichigo::Agent &secondAgent)
    {
        // When comparing an gent with itself, shorten the precess
        if (&firstAgent == &secondAgent)
        {
            return true;
        }

        bool retVal = false;
        bool foundAnswer = false;
                
        // Get the z-order path of each agent
        std::queue<int> firstOrderPath;
        std::queue<int> secondOrderPath;
        firstAgent.getView()->getZOrderPath(firstOrderPath);
        secondAgent.getView()->getZOrderPath(secondOrderPath);
        
        // Go over both paths until we find a definite answer
        int firstPathCount = firstOrderPath.size();
        int secondPathCount = secondOrderPath.size();
        while (!foundAnswer)
        {
            if (firstPathCount == 0)
            {
                // If first path is shorter, then the second one is more forward
                retVal = false;
                foundAnswer = true;
            }
            else if (secondPathCount == 0)
            {
                // If the second path is shorter, then the first on is more forward
                retVal = true;
                foundAnswer = true;
            }
            else
            {
                // Get the heads of both paths. They should be the same level in the tree
                int firstZOrder = firstOrderPath.front();
                firstOrderPath.pop();
                firstPathCount--;
                int secondZOrder = secondOrderPath.front();
                secondOrderPath.pop();
                secondPathCount--;
                
                // If both values are different, the larger one is more forward
                if (firstZOrder > secondZOrder)
                {
                    retVal = true;
                    foundAnswer = true;
                }
                else if (secondZOrder > firstZOrder)
                {
                    retVal = false;
                    foundAnswer = true;
                }
            }
        }
        
        return retVal;
    }
	
    
    // Returns the dimension of screen (in pixels)
    void Director::getScreenSize(int &width, int &height)
    {
        if (_directorView)
        {
            _directorView->getScreenSize(width, height);
        }
    }
    
    void Director::setScriptingEngine(ScriptingEngine* scriptingEngine) {
        _scriptingEngine = std::tr1::shared_ptr<ScriptingEngine>(scriptingEngine);
        _scriptingEngine->init();
    }
    
    ScriptingEngine* Director::getScriptingEngine() {
        return _scriptingEngine.get();
    }
}
