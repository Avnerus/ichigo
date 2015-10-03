#ifndef __ICHIGO_LAYERVIEW_H__
#define __ICHIGO_LAYERVIEW_H__

#include "View.h"
#include "Point.h"
#include "SceneView.h"


namespace ichigo
{
    class ActorView;
    
    
    class LayerView : public View
    {
    public:
        
        LayerView(Agent *agent);
        virtual ~LayerView();
        
        virtual void            init();
        virtual void            deserialize(Json::Value &configData);
        virtual void            update(float dt);
        
        virtual void            setViewportPosMultiplier(const Point &multiplier);
        virtual const Point    &getViewportPosMultiplier();
        virtual void            clipToBounds(bool clip);
        virtual bool            isClippingToBounds();
        virtual void            setClippingBounds(float x, float y, float w, float h);
        
        virtual void            addActor(ActorView *actor) = 0;
        virtual void            removeActor(ActorView *actor) = 0;
        virtual void            setParent(SceneView *sceneView);
        virtual Rect            getBoundingBox();        
        
    protected:
        
        SceneView  *_parent;
        
        Point       _viewportPosMultiplier;
        bool        _clipToBounds;
        Point       _clippingOrigin;
        Point       _clippingSize;
        
        float           _weight;
    };
}


#endif  // __ICHIGO_LAYERVIEW_H__
