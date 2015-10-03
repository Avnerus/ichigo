#ifndef __ICHIGO_LAYER_H__
#define __ICHIGO_LAYER_H__

#include "Agent.h"
#include "LayerView.h"


namespace ichigo {
        
    class Layer : public Agent {

    public:
        
        Layer();
        virtual ~Layer(); 

        virtual bool init();
        virtual void setView(LayerView *view);
        virtual void deserialize(Json::Value &agentConfig);
        virtual void update(float dt);
        
        virtual bool addChild(Agent *actor, std::string name = "");
        virtual bool addChild(std::tr1::shared_ptr<Agent> agent, std::string name = "");
        virtual void removeChild(ichigo::Agent *actor);

    protected:
        
        LayerView  *_layerView;
    };    
}


#endif // __ICHIGO_LAYER_H__