#include "Animation.h"
#include "Agent.h"
#include "DataManager.h"
#include "EventManager.h"
#include "SpriteActorView.h"


namespace ichigo
{
    Animation::Animation(SpriteActorView *spriteView)
    {
        _spriteView = spriteView;
        _animationName = "";
        _frameName = "";
        _frameExtension = "png";
        _frameCount = 1;
        _frameDelay = 0.1f;         // Default: 10FPS
        _loop = false;
        _generateEvents = false;
    }
    
    
    Animation::~Animation()
    {
    }
    
    
    // Loads the animation using data from a JSON structure
    void Animation::deserialize(Json::Value &configData)
    {
        std::string frame       = DataManager::getString(configData, "frame",   getFrameName());
        std::string extension   = DataManager::getString(configData, "ext",     getFrameExtension());
        int count               = DataManager::getInt   (configData, "frames",  getFrameCount());
        float delay             = DataManager::getFloat (configData, "delay",   getFrameDelay());
        init(frame, extension, count, delay);
        
        setName             (DataManager::getString (configData, "name",    getName()));
        setLooping          (DataManager::getBool   (configData, "loop",    isLooping()));
        allowEventGeneration(DataManager::getBool   (configData, "alert",   isGeneratingEvents()));
    }
    
    
    // Sets the basic parameters of the animation. These are all in one method because often they are dependant on each 
    // other (during inhertance)
    void Animation::init(std::string frameName, std::string frameExtension, int frameCount, float frameDelay)
    {
        _frameName = frameName;
        _frameExtension = frameExtension;
        _frameCount = frameCount;
        _frameDelay = frameDelay;
    }
    
    
    // Sets the name of the animation
    void Animation::setName(std::string name)
    {
        _animationName = name;
    }
    
    
    // Returns the animation name
    const std::string &Animation::getName()
    {
        return _animationName;
    }
    
    
    // Returns the name of the frame, without file extension or the frame number part of the frame filename
    const std::string &Animation::getFrameName()
    {
        return _frameName;
    }
    
    
    // Returns the file extension for the frames
    const std::string &Animation::getFrameExtension()
    {
        return _frameExtension;
    }
    
    
    // Returns the number of frames in this animation
    int Animation::getFrameCount()
    {
        return _frameCount;
    }
    
    
    // Returns the delay in seconds between each frame
    float Animation::getFrameDelay()
    {
        return _frameDelay;
    }
    
    
    // Sets whether the animation should loop from the begining once it reaches the end
    void Animation::setLooping(bool loop)
    {
        _loop = loop;
    }
    
    
    // Returns true if this animation will loop once it reaches its end
    bool Animation::isLooping()
    {
        return _loop;
    }
    
    
    // If set to true, an event will be published once the animation is over (and if the animation is looping, every time the loop restarts)
    void Animation::allowEventGeneration(bool generateEvents)
    {
        _generateEvents = generateEvents;
    }
    
    
    // Returns true if this animation generates events after animation is over
    bool Animation::isGeneratingEvents()
    {
        return _generateEvents;
    }
    
    
    // Once this animation is over, this method should be called to publish an event. This will most probably be called by 
    // a derived class
    void Animation::publishEvent()
    {
        if (_generateEvents)
        {
            EventManager::getInstance()->publish("ANIM_OVER_" + _animationName, _spriteView->getAgent());
        }
    }
}
