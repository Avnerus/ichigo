#ifndef __ICHIGO_ACTORVIEW_H__
#define __ICHIGO_ACTORVIEW_H__

#include "View.h"
#include "Point.h"


namespace ichigo
{
    class ActorView : public View
    {
    public:
        
        ActorView(Agent *agent);
        virtual ~ActorView();
        
        virtual void            init();
        virtual void            deserialize(Json::Value &configData);
        virtual void            update(float dt);
        
        virtual void            setRadius(float radius);
        virtual float           getRadius();

        virtual bool            isScreenPointInside(const Point &screenPos);
        
        virtual void            addChild(ActorView *child) = 0;
        virtual void            removeChild(ActorView *child) = 0;
        virtual void            setParent(View *parentView);
        virtual Rect            getBoundingBox();
        
    protected:
        
        View       *_parent;
        
        float       _radius;
    };
}


#endif  // __ICHIGO_ACTORVIEW_H__
