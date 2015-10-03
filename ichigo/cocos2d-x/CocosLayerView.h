#ifndef __ICHIGO_COCOSLAYERVIEW_H__
#define __ICHIGO_COCOSLAYERVIEW_H__

#include "LayerView.h"
#include "CocosClippingNode.h"

#include "cocos2d.h"
using namespace cocos2d;


namespace ichigo
{
    class CocosLayerView : public LayerView
    {
    public:
        
        CocosLayerView(Agent *agent);
        virtual ~CocosLayerView();
        
        virtual void        init();
        virtual void        update(float dt);
        
        virtual void        setPosition(const Point &pos);
        virtual void        setScale(float scale);
        virtual void        setAngle(float angle);
        virtual void        setZOrder(int zOrder);
        virtual void        setPivot(const Point &pivot);
        virtual void        setVisible(bool isVisible);
        
        virtual void        clipToBounds(bool clipToBounds);
        virtual void        setClippingBounds(float x, float y, float w, float h);
        
        virtual Point       convertLocalToScreen(const Point &localPos);  
        virtual Point       convertScreenToLocal(const Point &screenPos);  
        
        virtual void        addActor(ActorView *actor);
        virtual void        removeActor(ActorView *actor);
        
        virtual void       *getInternalData();
      
    protected:
        
        CCLayer            *_ccLayer;
        CocosClippingNode  *_clippingNode;
    };
}


#endif  // __ICHIGO_COCOSLAYERVIEW_H__
