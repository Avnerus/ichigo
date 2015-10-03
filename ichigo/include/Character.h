#ifndef __ICHIGO_CHARACTER_H__
#define __ICHIGO_CHARACTER_H__

#include "Actor.h"
#include "LabelView.h"
#include "SpriteActorView.h"


namespace ichigo {
        
    class Character : public Actor {

    public:
        
        Character();
        virtual ~Character(); 

        virtual bool init();
        virtual void setView(ActorView *view);
        virtual void deserialize(Json::Value &agentConfig);
        virtual void update(float dt);
        
        virtual void say(std::string text);
        virtual void touch();
        
    protected:        
        std::tr1::shared_ptr<SpriteActorView> _spriteView;
        LabelView *_talkLabelView;
        Actor  *_talkLabel;        
    };    
}


#endif // __ICHIGO_CHARACTER_H__