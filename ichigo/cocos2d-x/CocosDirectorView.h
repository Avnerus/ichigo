#ifndef __ICHIGO_COCOSDIRECTORVIEW_H__
#define __ICHIGO_COCOSDIRECTORVIEW_H__

#include "DirectorView.h"

#include "cocos2d.h"


namespace ichigo
{
    class CocosDirectorView : public DirectorView
    {
    public:
        
        CocosDirectorView(Agent *agent);
        virtual ~CocosDirectorView();
        
        virtual void       *getInternalData();
        virtual void        setPivot(const Point &pivot);
        
        virtual void        addScene(SceneView *sceneView);
        virtual void        removeScene(SceneView *sceneView);
        virtual void        setCurrentScene(SceneView *sceneView);
        virtual SceneView  *getCurrentScene();
        
        virtual Point       convertLocalToScreen(const Point &localPos);  
        virtual Point       convertScreenToLocal(const Point &screenPos);  
        
        virtual void        getScreenSize(int &width, int &height);
        
    protected:
        
        cocos2d::CCDirector    *_ccDirector;
    };
}


#endif // __ICHIGO_COCOSDIRECTORVIEW_H__
