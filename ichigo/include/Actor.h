#ifndef __ICHIGO_ACTOR_H__
#define __ICHIGO_ACTOR_H__

#include "Agent.h"
#include "Point.h"
#include "ActorView.h"


namespace ichigo {
        
    class Actor : public Agent {

    public:
        
        Actor();
        virtual ~Actor(); 

        virtual bool init();
        virtual void setView(ActorView *view);
        virtual void deserialize(Json::Value &agentConfig);
        virtual void update(float dt);

        virtual bool addChild(Agent *actor, std::string name = "");
        virtual bool addChild(std::tr1::shared_ptr<Agent> agent, std::string name = "");
        virtual void removeChild(ichigo::Agent *actor);
        
    protected:
        
        ActorView  *_actorView;
    };    
}


#endif // __ICHIGO_ACTOR_H__