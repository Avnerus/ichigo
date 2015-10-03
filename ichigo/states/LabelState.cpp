#include "LabelState.h"
#include "Director.h"

namespace ichigo 
{    
    LabelState::LabelState() 
    {
        // My event table
        _eventCallbacks["LabelTimerEnded"] = std::tr1::bind(&LabelState::onTimerEnded, this, _1);        
        _name = "Label";  
        
    }
    
    
    void LabelState::init() {
        FSMState::init();
        _labelView = (LabelView *)_agent->getView();
    }
    
    LabelState::~LabelState() {

    }
    
    void LabelState::onTimerEnded(Agent *waitingAgent) {
        if (waitingAgent == _agent) {
            _labelView->setVisible(false);
        }
    }
    
    void LabelState::onEnter() {
        FSMState::onEnter();
    }
    
    void LabelState::showFor(float seconds) {
        
        _labelView->setVisible(true);
        Director::getInstance()->addTimer(_agent, "LabelTimerEnded", seconds,false);
    }  
}