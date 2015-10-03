#ifndef __ICHIGO_COCOSSPRITEACTORVIEW_H__
#define __ICHIGO_COCOSSPRITEACTORVIEW_H__

#include "SpriteActorView.h"

#include "cocos2d.h"
using namespace cocos2d;


namespace ichigo 
{
    class CocosSpriteActorView : public SpriteActorView
    {
    public:
        
        CocosSpriteActorView(Agent *);
        virtual ~CocosSpriteActorView();
        
        virtual void                init();
        virtual void                update(float dt);
        
        virtual void                setPosition(const Point &pos);
        virtual void                setScale(float scale);
        virtual void                setAngle(float angle);
        virtual void                setZOrder(int zOrder);
        
        virtual void                playAnimation(const std::string &name);
        virtual void                restartCurrentAnimation();
        virtual Animation          *createAnimation();
        virtual void                setRadiusFromWidth();
        virtual void                setRadiusFromHeight();
        virtual float               getHeight();
        virtual float               getWidth();
        
        virtual void                setAlpha(float alpha);
        
        virtual void                setPivot(const Point &pivot);
        virtual void                setVisible(bool isVisible);

        virtual void                loadFramesFromAtlas(const std::string &atlasFile);
        virtual Point               convertLocalToScreen(const Point &localPos);  
        virtual Point               convertScreenToLocal(const Point &screenPos); 
        
        virtual void                addChild(ActorView *child);
        virtual void                removeChild(ActorView *child);
        
        virtual void               *getInternalData();
        
    protected:  

        CCSprite           *_ccSprite;
    };
}


#endif  // __ICHIGO_COCOSSPRITEACTORVIEW_H__
