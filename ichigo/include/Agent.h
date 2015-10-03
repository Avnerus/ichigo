#ifndef __ICHIGO_AGENT_H__
#define __ICHIGO_AGENT_H__

#include <string>
#include <map>
#include "FSM.h"
#include "View.h"
#include "Json/json.h"


namespace ichigo {
    
    typedef std::map< std::string, std::tr1::shared_ptr<Agent> > AgentList;
        
    
    class Agent {
        
    public:
        
        Agent();
        virtual ~Agent();
        
        virtual bool                init();     
        virtual void                initWithChildren();
        virtual void                initChildren();        
        virtual void                update(float dt);
        
        std::string                 getType();    
        virtual std::string         getName();
        FSM                        *getFSM();
        View                       *getView();
        void                        setView(View *view);
        
        virtual bool                addChild(Agent *agent, std::string name = "");
        virtual bool                addChild(std::tr1::shared_ptr<Agent> agent, std::string name = "");
        virtual void                removeChild(Agent *agent);
        virtual void                removeChild(std::string name);
        virtual Agent              *getChild(std::string name);
        std::tr1::shared_ptr<Agent> retainChild(Agent *agent);
        virtual Agent              *findByName(std::string name);
        virtual Agent              *findByType(std::string type);
        virtual AgentList          &getChildren();
        virtual void                setParent(Agent *parent);
        virtual Agent              *getParent();
        virtual Agent              *getParentScene();       
        
        virtual void                loadFromJSON(Json::Value &agentConfig);
        virtual void                deserialize(Json::Value &agentConfig);
        
        virtual void                loadScript();    
        
        virtual bool                isScripted();
                
        
    protected:
        
        std::string                 _type;
        FSM                         _fsm;
        std::tr1::shared_ptr<View>  _view;
        AgentList                   _children;
        Agent                      *_parent;
        int                         _childCounter;
        bool                        _scripted;
    };    
}


#endif // __ICHIGO_AGENT_H__