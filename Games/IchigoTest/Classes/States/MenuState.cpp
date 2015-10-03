#include "MenuState.h"
#include "Director.h"


namespace it
{
    MenuState::MenuState()
    : FSMState()
    {
        _eventCallbacks["BUTTON_CLICK_goScene1"] = std::tr1::bind(&MenuState::onButton1Click, this, _1);  
        _eventCallbacks["BUTTON_CLICK_goScene2"] = std::tr1::bind(&MenuState::onButton2Click, this, _1);    
        _eventCallbacks["BUTTON_CLICK_goScene3"] = std::tr1::bind(&MenuState::onButton3Click, this, _1);
    }
    
    
    void MenuState::onButton1Click(ichigo::Agent *agent)
    {
        ichigo::Director::getInstance()->setCurrentScene("scene1");
    }
    
    
    void MenuState::onButton2Click(ichigo::Agent *agent)
    {
        ichigo::Director::getInstance()->setCurrentScene("scene2");
    }
    
    
    void MenuState::onButton3Click(ichigo::Agent *agent)
    {
        ichigo::Director::getInstance()->setCurrentScene("scene3");
    }
}
