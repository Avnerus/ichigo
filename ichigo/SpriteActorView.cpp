#include "SpriteActorView.h"
#include "DataManager.h"
#include "Animation.h"
#include "EventManager.h"


namespace ichigo
{
    SpriteActorView::SpriteActorView(Agent *agent)
    : ActorView(agent)
    {
        _alpha = 1.0f;
        _targetAlpha = 1.0f;
        _fadeDuration = 0;
    }
    
    
    SpriteActorView::~SpriteActorView()
    {
    }
    
    
    // Called every frame
    void SpriteActorView::update(float dt)
    {
        ActorView::update(dt);
        
        // If sprite needs to fade, fade according to passed time from last frame
        if (_fadeDuration > 0)
        {
            float fadeDelta = _targetAlpha - _alpha;
            float timeDelta = _fadeDuration / dt;
            setAlpha(_alpha + (fadeDelta / timeDelta));
            
            _fadeDuration -= dt;
        }
        // Check if we need to move
        if (!_isMoving && !_movementQueue.empty()) {
            // std::cout << "SpriteActorView::update - Popping movement " << _movementQueue.front().animationName << std::endl;
            Movement movement = _movementQueue.front();
            _currentMovement = &movement;
                                    
            // Start animation 
            playAnimation(movement.animationName);            
            // Move
            moveTo(movement.target, movement.duration);
            
            _movementQueue.pop_front();
            

            
        } else if (!_isMoving && _movementQueue.empty() && _currentMovement != NULL) {
            // Just finished queue,publish event
            _currentMovement = NULL;
            EventManager::getInstance()->publish("MOVEMENT_QUEUE_ENDED", _agent);
        }
    }
    
    
    // Config the view from a Json data structure
    void SpriteActorView::deserialize(Json::Value &configData)
    {
        ActorView::deserialize(configData);
        
        // std::cout << "SpriteActorView::deserialize" << std::endl;
        
        setAlpha(DataManager::getFloat(configData, "alpha", getAlpha()));
        
        if (configData.isMember("loadAtlas"))
        {
            loadFramesFromAtlas(DataManager::getString(configData, "loadAtlas"));
        }
        
        Json::Value &animations = configData["animations"];
        if (!animations.isNull() && animations.isArray() && animations.size() > 0)
        {
            for (int i = 0; i < animations.size(); i++) 
            {
                Json::Value &animationData = animations[i];
                if (animationData.isMember("name"))
                {
                    Animation *newAnimation = createAnimation();
                    newAnimation->deserialize(animationData);
                    addAnimation(animationData["name"].asString(), newAnimation);
                }
            }
            
            playAnimation(DataManager::getString(configData, "firstAnimation", ""));
        }
        
        bool getRadiusFromWidth = DataManager::getBool(configData, "radiusFromWidth", false);
        if (getRadiusFromWidth)
        {
            setRadiusFromWidth();
        }
        
        bool getRadiusFromHeight = DataManager::getBool(configData, "radiusFromHeight", false);
        if (getRadiusFromHeight)
        {
            setRadiusFromHeight();
        }
    }
    
    
    // Add an animation to the list
    void SpriteActorView::addAnimation(const std::string &name, Animation *animation)
    {
        _animations[name] = std::tr1::shared_ptr<Animation>(animation);
    }
    
    
    // Remove an animation from the list
    void SpriteActorView::removeAnimation(const std::string &name)
    {
        AnimationList::iterator it = _animations.find(name);
        if (it != _animations.end())
        {
            _animations.erase(it);
        }
    }
    
    
    // Starts playing the animation, if it is a valid name
    void SpriteActorView::playAnimation(const std::string &name)
    {
        AnimationList::iterator it = _animations.find(name);
        if (it != _animations.end())
        {
            _currentAnimation = name;
        }
    }
    
    
    // Starts playing an animation while linearly moving to a point. The speed it will move at will be as much as "speed"
    // but might be slower in order to arrive at the target exactly when an animation cycle ends.
    // If speed is 0, speed will be calculated to arrive at target after one animation cycle.
    void SpriteActorView::playAndMoveTo(const std::string &name, const ichigo::Point &target, float speed /* = 0 */)
    {
     
    }
    
    
    // Starts playing an animation while linearly moving by [x,y] points. The speed it will move at will be as much as "speed"
    // but might be slower in order to arrive at the target exactly when an animation cycle ends.
    // If speed is 0, speed will be calculated to arrive at target after one animation cycle.
    void SpriteActorView::playAndMoveBy(const std::string &name, const ichigo::Point &delta, float speed /* = 0 */)
    {
        Animation *anim = getAnimation(name);
        
        if (anim)
        {
            // Calculate duration for speed
            float duration;
            float cycleDuration = anim->getFrameCount() * anim->getFrameDelay();
            
            if (speed == 0)
            {
                // Get to target in one cycle
                duration = cycleDuration;
            }
            else
            {
                float travelDistance = delta.distanceTo(Point());
                duration = travelDistance / speed;
                
                if (cycleDuration > 0) {
                    // Fix duration to animation cycle
                    int cyclesToTarget = (int)(duration / cycleDuration);
                    if (cycleDuration * cyclesToTarget < duration)
                    {
                       duration = cycleDuration * (cyclesToTarget + 1);
                    }
                }   
            }
            
            // Start animation 
            playAnimation(name);
            
            // Move
            moveBy(delta, duration);
        }
    }
    
    void SpriteActorView::queueMovement(const std::string &name, const Point &target, float speed) {
        // Check the movement origin
        ichigo::Point origin;
        if (_movementQueue.empty()) {
            origin = getPosition();            
        } else {
            origin = _movementQueue[0].target;
        }
        Animation *anim = getAnimation(name);

        if (anim)
        {
            // Calculate duration for speed
            float duration;
            float cycleDuration = (anim->getFrameCount() - 1) * anim->getFrameDelay();

            if (speed == 0)
            {
                // Get to target in one cycle
                duration = cycleDuration;
            }
            else
            {
                float travelDistance = origin.distanceTo(target);
                duration = travelDistance / speed;

                // Fix duration to animation cycle
                if (cycleDuration > 0) {
                    int cyclesToTarget = (int)(duration / cycleDuration);
                    if (cycleDuration * cyclesToTarget < duration)
                    {
                        duration = cycleDuration * (cyclesToTarget + 1);
                    }
                }
            }
            
            Movement newMovement;
            newMovement.animationName = name;
            newMovement.target = target;    
            newMovement.duration = duration;
            _movementQueue.push_back(newMovement);
        }
    }
    void SpriteActorView::clearMovementQueue() {
        _movementQueue.clear();        
    }
    
    
    // Returns the name of the current animation
    const std::string &SpriteActorView::getCurrentAnimation()
    {
        return _currentAnimation;
    }
    
    
    // Returns a pointer to an Animation with the given name
    Animation *SpriteActorView::getAnimation(std::string name)
    {
        Animation *retVal = NULL;
        
        // If name exists, point to the animation
        AnimationList::iterator it = _animations.find(name);
        if (it != _animations.end())
        {
            retVal = it->second.get();
        }
        
        return retVal;
    }
    
    
    // Set opacity of sprite (1 = opaque, 0 = invisible)
    void SpriteActorView::setAlpha(float alpha)
    {
        _alpha = alpha;
        
        if (_alpha < 0)
        {
            _alpha = 0;
        }
        else if (_alpha > 1)
        {
            _alpha = 1.0f;
        }
    }
    
    
    // Returns the opacity of the sprite (between 0.0 and 1.0)
    float SpriteActorView::getAlpha()
    {
        return _alpha;
    }
    
    
    // Fades to alpha in _duration_ seconds
    void SpriteActorView::fadeTo(float alpha, float duration)
    {
        _targetAlpha = alpha;
        _fadeDuration = duration;
    }
    
    
    // Stops fading at current alpha
    void SpriteActorView::stopFading()
    {
        _fadeDuration = 0;
    }
    
    Rect SpriteActorView::getBoundingBox() {
        return Rect(-getWidth() / 2.0f, -getHeight() /2.0f, getWidth() /2.0f, getHeight() / 2.0f);
    }
    
    std::deque<Movement> &SpriteActorView::getMovementQueue() {
        return _movementQueue;        
    }
    
    Movement *SpriteActorView::getCurrentMovement() {
        return _currentMovement;
    }

}
