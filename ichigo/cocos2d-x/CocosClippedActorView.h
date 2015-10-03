#ifndef __ICHIGO_COCOSCLIPPEDACTORVIEW_H__
#define __ICHIGO_COCOSCLIPPEDACTORVIEW_H__

#include "ClippedActorView.h"
#include "CocosClippingNode.h"

#include "cocos2d.h"
using namespace cocos2d;


namespace ichigo
{
    class CocosClippedActorView : public ClippedActorView
    {
    public:
      
        CocosClippedActorView(Agent *agent);
        virtual ~CocosClippedActorView();
        
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
        
        virtual void            clipToBounds(bool clipToBounds);
        virtual void            setClippingBounds(float x, float y, float w, float h);
        
    protected:
        CocosClippingNode  *_clippingNode;
    };
}


#endif  // __ICHIGO_COCOSCLIPPEDACTORVIEW_H__
