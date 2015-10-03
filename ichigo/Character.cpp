#include "Character.h"
#include "SpriteActorView.h"
#include "LabelState.h"
#include "Director.h"

#include <iostream>


namespace ichigo {
    
    Character::Character() 
    : Actor()
    {
        _type = "Character";
        _actorView = NULL;
        _talkLabelView = NULL;  
    }

    
    Character::~Character() {
    }    
    
    
    // Initialize the character
    bool Character::init() {
        Actor::init();
        
        // Init the label
        Agent *label = getChild("talkLabel");
        if (label) {
            _talkLabel = (Actor *)label;
            _talkLabelView = (ichigo::LabelView *)label->getView();
            _talkLabelView->setPosition(ichigo::Point(_spriteView->getWidth() / 2 + 50.0f, _spriteView->getHeight() / 2.0 + 100.0f));            
        }
        
        return true;
    }	
    
    
    // Set the view of the character
    void Character::setView(ichigo::ActorView *view)
    {
        Actor::setView(view);
        _spriteView = std::tr1::static_pointer_cast<SpriteActorView>(_view);        

    }
    
    
    // Config the actor from data in Json structure
    void Character::deserialize(Json::Value &agentConfig)
    {
        Actor::deserialize(agentConfig);        
    }


    // Gets called every frame
    void Character::update(float dt) {
        Actor::update(dt);
    }
    
    void Character::say(std::string text) {    
        LabelState *labelState = (LabelState *)(_talkLabel->getFSM()->getCurrentState());
        _talkLabelView->setText(text);
        labelState->showFor(2.0f);
    }
    
    void Character::touch() {
        // Let the script handle that      
        if (isScripted()) {
            Director::getInstance()->getScriptingEngine()->executeFunction(getName() + "_touch");            
        }
    }
}