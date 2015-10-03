#ifndef __ICHIGO_ANIMATION_H__
#define __ICHIGO_ANIMATION_H__

#include "Json/json.h"
#include <string>


namespace ichigo
{
    class SpriteActorView;
    
    
    class Animation
    {
    public:
        
        Animation(SpriteActorView *spriteView);
        virtual ~Animation();
        
        virtual void                deserialize(Json::Value &configData);
        
        virtual void                init(std::string frameName, std::string frameExtension, int frameCount, float frameDelay);
        virtual void                setName(std::string name);
        virtual const std::string  &getName();
        virtual const std::string  &getFrameName();
        virtual const std::string  &getFrameExtension();
        virtual int                 getFrameCount();
        virtual float               getFrameDelay();
        virtual void                setLooping(bool loop);
        virtual bool                isLooping();
        virtual void                allowEventGeneration(bool generateEvents);
        virtual bool                isGeneratingEvents();
        
        virtual void                publishEvent();
        
    protected:
        
        SpriteActorView    *_spriteView;
        std::string         _animationName;
        std::string         _frameName;
        std::string         _frameExtension;
        int                 _frameCount;
        float               _frameDelay;
        bool                _loop;
        bool                _generateEvents;
    };
}


#endif // __ICHIGO_ANIMATION_H__
