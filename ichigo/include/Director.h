#ifndef __ICHIGO_DIRECTOR_H__
#define __ICHIGO_DIRECTOR_H__

#include "Agent.h"
#include "DirectorView.h"
#include "EventManager.h"
#include "ScriptingEngine.h"

#include <map>
#include <tr1/functional>
#include <tr1/memory>


namespace ichigo {
    
    class Scene;
    class TouchPoint;

    struct TimerTask {
        EventType       event;
        float           timer;
        float           timeToNext;
        bool            loop;
        Agent*          waitingAgent;
    };
    
    typedef std::map< int, std::tr1::shared_ptr<TimerTask> > TimerList;
    
    typedef std::map< int, std::tr1::shared_ptr<TouchPoint> > TouchList;
        
    class Director : public Agent {
                
    public:
        
        virtual ~Director();     
        static Director* getInstance();
        
        virtual bool    init();
        virtual void    setView(DirectorView *view);
        virtual void    update(float dt);
        virtual void    deserialize(Json::Value &agentConfig);
        virtual std::string getName();

        void            start();
        
        virtual bool    addChild(Agent *scene, std::string name = "");
        virtual bool    addChild(std::tr1::shared_ptr<Agent> agent, std::string name = "");
        virtual void    removeChild(Agent *scene);

        Scene          *getCurrentScene();
        void            setCurrentScene(std::string); 
        
        void            addTouchPoint(TouchPoint *touchPoint);
        void            removeTouchPoint(int touchID);
        TouchPoint     *getTouchPoint(int touchID);
        TouchList      &getTouchList();

        
        int             addTimer(Agent* waitingAgent, const EventType &event, float time, bool loop = false);
        void            removeTimer(int timerID);
        void            clearAllTimers();

        bool            isFirstAgentInFront(Agent &firstAgent, Agent &secondAgent);
        void            getScreenSize(int &width, int &height);
        void                                setScriptingEngine(ScriptingEngine* scriptingEngine);
        ScriptingEngine* getScriptingEngine();
        void            setScenesFileName(std::string fileName);
        
    protected:

        Director();
        static Director _instance;
        static bool     _isInitialized;
        std::string     _scenesFilename;
        std::tr1::shared_ptr<ScriptingEngine> _scriptingEngine;

        
        void            handleTimer(int timerID, TimerTask *timer, float dt);
        
        DirectorView                   *_directorView;

        std::string                    _currentSceneName;
        Scene                          *_currentScene;        
        TouchList                       _touchPoints;
        
        TimerList                       _timers;
        int                             _nextTimerID;
    };    
}



#endif // __ICHIGO_AGENT_H__