#ifndef __ICHIGO_SCENE_H__
#define __ICHIGO_SCENE_H__

#include "Agent.h"
#include "SceneView.h"


namespace ichigo {

    class Scene : public Agent {
    
    public:
        
        Scene();
        virtual ~Scene();              
          
        virtual bool init();
        virtual void setView(SceneView *view);
        virtual void deserialize(Json::Value &agentConfig);
        virtual void loadFromJSON(Json::Value &agentConfig);
        virtual void update(float dt);      
        
        virtual bool addChild(Agent *layer, std::string name = "");
        virtual bool addChild(std::tr1::shared_ptr<Agent> agent, std::string name = "");
        virtual void removeChild(ichigo::Agent *layer);

        virtual void setAsCurent(bool isCurrent);
        
    protected:
        
        SceneView  *_sceneView;
        bool        _isCurrent;
        Json::Value _configData;
        bool        _wasLoaded;
    };    
}



#endif // __ICHIGO_SCENE_H__