#ifndef __ICHIGO_DIRECTORVIEW_H__
#define __ICHIGO_DIRECTORVIEW_H__

#include "View.h"


namespace ichigo
{
    class SceneView;
    
    
    class DirectorView : public View
    {
    public:
        
        DirectorView(Agent *agent);
        virtual ~DirectorView();
        
        virtual void        init();
        virtual void        deserialize(Json::Value &configData);
        virtual void        update(float dt);
        
        virtual void        addScene(SceneView *sceneView) = 0;
        virtual void        removeScene(SceneView *sceneView) = 0;
        virtual void        setCurrentScene(SceneView *sceneView) = 0;
        virtual SceneView  *getCurrentScene() = 0;
        
        virtual void        getScreenSize(int &width, int &height) = 0;
        virtual Rect        getBoundingBox();
        
    protected:
        
        SceneView   *_currentSceneView;
    };
}


#endif  // __ICHIGO_DIRECTORVIEW_H__
