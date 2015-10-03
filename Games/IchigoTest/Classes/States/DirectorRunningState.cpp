#include "DirectorRunningState.h"
#include "ichigo.h"


namespace it 
{    
    DirectorRunningState::DirectorRunningState() 
    {
        // My event table
        _eventCallbacks["BUTTON_CLICK_backButton"] = std::tr1::bind(&DirectorRunningState::onBackButton, this, _1);        
        
        _name = "mainState";
    }
    
    
    DirectorRunningState::~DirectorRunningState() 
    {
        std::cout << "DirectorRunningState destroyed" << std::endl;
    }
    
    
    // Occurs when back button was pressed
    void DirectorRunningState::onBackButton(ichigo::Agent *button)
    {
        // Return to main menu
        ichigo::Director::getInstance()->setCurrentScene("menu");
    }
}