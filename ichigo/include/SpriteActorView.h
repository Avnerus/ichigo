#ifndef __ICHIGO_SPRITEACTORVIEW_H__
#define __ICHIGO_SPRITEACTORVIEW_H__

#include "ActorView.h"
#include <string>
#include <map>
#include <tr1/memory>
#include <deque>


namespace ichigo
{
    class Animation;
    typedef std::map< std::string, std::tr1::shared_ptr<Animation> > AnimationList;
    
    class Movement {
    public:        
        std::string animationName;
        Point target;
        float duration;
    };
    
    
    class SpriteActorView : public ActorView
    {
    public:
        
        SpriteActorView(Agent *agent);
        virtual ~SpriteActorView();
        
        virtual void                update(float dt);
        virtual void                deserialize(Json::Value &configData);
        
        virtual void                addAnimation(const std::string &name, Animation *animation);
        virtual void                removeAnimation(const std::string &name);
        virtual void                playAnimation(const std::string &name);
        virtual void                playAndMoveTo(const std::string &name, const Point &target, float speed = 0); 
        virtual void                queueMovement(const std::string &name, const Point &target, float speed = 0);
        virtual void                clearMovementQueue();
        virtual void                playAndMoveBy(const std::string &name, const Point &delta, float speed = 0);
        virtual void                restartCurrentAnimation() = 0;
        virtual const std::string  &getCurrentAnimation();
        virtual Animation          *getAnimation(std::string name);
        
        virtual void                setAlpha(float alpha);
        virtual float               getAlpha();
        virtual void                fadeTo(float alpha, float duration);
        virtual void                stopFading();

        virtual void                loadFramesFromAtlas(const std::string &atlasFile) = 0;
        virtual void                setRadiusFromWidth() = 0;
        virtual void                setRadiusFromHeight() = 0;
        virtual float               getHeight() = 0;
        virtual float               getWidth() = 0;   
        
        virtual Animation          *createAnimation() = 0;
        virtual Rect                getBoundingBox();
        
        std::deque<Movement>       &getMovementQueue();
        Movement                   *getCurrentMovement();
        
        
    protected:
                
        AnimationList           _animations;
        std::string             _currentAnimation;
        std::deque<Movement>    _movementQueue;
        Movement                *_currentMovement;
        
        float                   _alpha;
        float                   _targetAlpha;
        float                   _fadeDuration;
    };
}


#endif  // __ICHIGO_SPRITEACTORVIEW_H__
