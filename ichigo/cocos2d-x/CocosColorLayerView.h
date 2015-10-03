#ifndef __ICHIGO_COCOSCOLORLAYERVIEW_H__
#define __ICHIGO_COCOSCOLORLAYERVIEW_H__

#include "ColorLayerView.h"
#include "CocosClippingNode.h"

#include "cocos2d.h"
using namespace cocos2d;

namespace ichigo
{
    class CocosColorLayerView : public ColorLayerView
    {
    public:
        
        CocosColorLayerView(Agent *agent);
        virtual ~CocosColorLayerView();
        
        virtual void        init();
        virtual void        update(float dt);
        
        virtual void        setPosition(const Point &pos);
        virtual void        setScale(float scale);
        virtual void        setAngle(float angle);
        virtual void        setZOrder(int zOrder);
        virtual void        setPivot(const Point &pivot);
        virtual void        setVisible(bool isVisible);
        virtual void        setBGColor(const Color &bgColor);
        virtual void        setHeight(float height);
        virtual void        setWidth(float width);
        
        virtual void        clipToBounds(bool clipToBounds);
        virtual void        setClippingBounds(float x, float y, float w, float h);
        
        virtual Point       convertLocalToScreen(const Point &localPos);  
        virtual Point       convertScreenToLocal(const Point &screenPos);  
        
        virtual void        addActor(ActorView *actor);
        virtual void        removeActor(ActorView *actor);
        
        virtual void       *getInternalData();
      
    protected:
        
        CCLayerColor       *_ccLayer;
        CocosClippingNode  *_clippingNode;
    };
}


#endif  // __ICHIGO_COCOSCOLORLAYERVIEW_H__
