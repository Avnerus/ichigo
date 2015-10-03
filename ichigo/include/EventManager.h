#ifndef __ICHIGO_EVENTMANAGER_H__
#define __ICHIGO_EVENTMANAGER_H__

#include <tr1/functional>
#include <string>
#include <set>
#include <map>


namespace ichigo {
            
    class Agent;
    class Scene;
    class FSMState;
    class TouchPoint;
    
    
    class StateSort
    {
    public:
        bool operator()(FSMState *state1, FSMState *state2);
    };
    
    
    typedef std::string                             EventType;
    typedef std::tr1::function<void (Agent *)>      EventCallback;
    typedef std::multiset<FSMState *, StateSort>    SortedStateList;
    typedef std::map<EventType, SortedStateList>    SceneSubscriberList;
    typedef std::map<Scene *, SceneSubscriberList>  SubscriberList;
    
    class EventManager {
            
    public:

        ~EventManager();
        static EventManager* getInstance();
        
        bool init();
        void subscribe(FSMState* state, EventType event);
        void unsubscribe(FSMState* state, EventType event);
        void resortSceneEvents();
        void publish(EventType event, Agent* agent);
        
        void onTouchStarted(TouchPoint *touch);
        void onTouchMoved(TouchPoint *touch);
        void onTouchEnded(TouchPoint *touch);

    protected:

        EventManager();
        static EventManager _instance;
        static bool         _instanceInitialized;

        SubscriberList      _subscribers;
    };    
}



#endif // __ICHIGO_EVENTMANAGER_H__