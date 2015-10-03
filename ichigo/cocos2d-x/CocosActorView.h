#ifndef __ICHIGO_COCOSACTORVIEW_H__
#define __ICHIGO_COCOSACTORVIEW_H__

#include "ActorView.h"

#include "cocos2d.h"
using namespace cocos2d;


namespace ichigo
{
    class CocosActorView : public ActorView
    {
    public:
      
        CocosActorView(Agent *agent);
        virtual ~CocosActorView();
        
        virtual void            init();
        virtual void            update(float dt);
       
        virtual void            setPosition(const Point &pos);
        virtual void            setScale(float scale);
        virtual void            setAngle(float angle);
        virtual void            setZOrder(int zOrder);
        virtual void            setPivot(const Point &pivot);
        virtual void            setVisible(bool isVisible);
        
        virtual Point           convertLocalToScreen(const Point &localPos);
        virtual Point           convertScreenToLocal(const Point &screenPos);
        
        virtual void            addChild(ActorView *child);
        virtual void            removeChild(ActorView *child);
        
        virtual void           *getInternalData();
        
    protected:
        
        CCNode                 *_ccNode;
    };
}


#endif  // __ICHIGO_COCOSACTORVIEW_H__
