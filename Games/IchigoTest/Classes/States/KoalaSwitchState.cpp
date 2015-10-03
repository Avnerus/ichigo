#include "KoalaSwitchState.h"
#include "Director.h"
#include "DataManager.h"
#include "SceneView.h"
#include "LayerView.h"


namespace it
{
    KoalaSwitchState::KoalaSwitchState()
    {
        _isViewingReality = true;
        _touchID = 0;
        _touchY = 0;
        _touchEnding = false;
        
        _sceneView = NULL;
        _realityLayer = NULL;
        _dreamLayer = NULL;
        _screenHeight = 320;
        
        _eventCallbacks["OnTouchStarted"] = std::tr1::bind(&KoalaSwitchState::onTouchStarted, this, _1);
        _eventCallbacks["OnTouchMoved"] = std::tr1::bind(&KoalaSwitchState::onTouchMoved, this, _1);
        _eventCallbacks["OnTouchEnded"] = std::tr1::bind(&KoalaSwitchState::onTouchEnded, this, _1);
    }
    
    
    // On first run of this state, save some pointers to often accessed objects
    void KoalaSwitchState::onUpdate(float dt)
    {
        FSMState::onUpdate(dt);
        
        if (!_sceneView)
        {
            ichigo::Director *director = ichigo::Director::getInstance();
            ichigo::Scene *currentScene = director->getCurrentScene();
        
            _sceneView = (ichigo::SceneView *)currentScene->getView();
            _realityLayer = (ichigo::LayerView *)currentScene->getChild("reality")->getView();
            _dreamLayer = (ichigo::LayerView *)currentScene->getChild("dream")->getView();
            
            int screenWidth;
            director->getScreenSize(screenWidth, _screenHeight);
        }
        
        // If a touch just ended and the viewport isn't set yet to one of the modes, animate it
        if (_touchEnding)
        {
            animateTouchEnding(dt);
        }
    }
    
    
    // After a dragging has ended, we animate the viewport to focus on the clossest mode
    void KoalaSwitchState::animateTouchEnding(float dt)
    {
        // Decide which mode is closer
        bool targetReality = false;
        float targetY = -_screenHeight - CONST_FLOAT("REALITY_SWITCHER_BORDER_WIDTH");
        ichigo::Point viewportPos = _sceneView->getPosition();
        if (viewportPos.y > -(_screenHeight / 2))
        {
            targetReality = true;
            targetY = 0;
        }
        
        // Calculate by how much to move this frame
        float distance = fabs(targetY - viewportPos.y);
        float slideBy = (CONST_FLOAT("REALITY_SWITCHER_ANIM_SPEED") + distance) * dt;
        
        // If we are still far from the target position, just animate
        if (distance > slideBy)
        {
            float moveDirection = (targetY - viewportPos.y) / distance;
            viewportPos.y += slideBy * moveDirection;
            _sceneView->setPosition(viewportPos);
        }
        else
        {
            // We are close enough, bring to final position
            viewportPos.y = targetY;
            _sceneView->setPosition(viewportPos);
            
            // End animation and select mode
            _touchEnding = false;
            _isViewingReality = targetReality;
            
            // Bring current mode to the front in Z order, otherwise the other mode might get touch events instead
            _realityLayer->setZOrder(targetReality ? 1 : 0);
            _dreamLayer->setZOrder(targetReality ? 0 : 1);
            ichigo::EventManager::getInstance()->resortSceneEvents();
        }
    }
    
    
    // Check if this touch is meant to switch between dream and reality. If so, do the switch. Otherwise ignore the touch and
    // allow lower layers to handle it
    void KoalaSwitchState::onTouchStarted(ichigo::Agent *agent)
    {
        ichigo::Director *director = (ichigo::Director *)agent;
        
        // Only start drag if this is a start of a new one
        if (!_touchEnding && _touchID == 0 && director->getTouchList().size() == 1)
        {
            ichigo::TouchPoint *tp = director->getTouchList().begin()->second.get();
            
            // Make sure this touch isn't already used by another handler
            if (!tp->wasHandled())
            {
                _touchY = tp->getPos().y;
                
                int screenWidth;
                int screenHeight;
                director->getScreenSize(screenWidth, screenHeight);
                
                float touchMargin = CONST_FLOAT("REALITY_SWITCHER_MARGIN");
                
                // This is a switching touch only if it is in the margin of the screen closer to the other reality/dream layer
                if ((_isViewingReality && _touchY > (float)screenHeight - touchMargin) || (!_isViewingReality && _touchY < touchMargin))
                {
                    _touchID = tp->getID();
                    tp->markAsHandled();
                }
            }
        }
    }
    
    
    // If the dragging touch gas moved, drag the scene's viewport accordingly
    void KoalaSwitchState::onTouchMoved(ichigo::Agent *agent)
    {
        // Did a touch start at all?
        if (_touchID != 0)
        {
            ichigo::Director *director = (ichigo::Director *)agent;
            ichigo::TouchPoint *tp = director->getTouchPoint(_touchID);
            
            // Does this touch still exist? (It should!)
            if (tp)
            {
                float deltaY = tp->getPos().y - tp->getPrevPos().y;
                
                // Move the viewport according to the amount the touch was dragged
                ichigo::Point viewportPos = _sceneView->getPosition();
                viewportPos.y += deltaY;
                _sceneView->setPosition(viewportPos);
            }
            else
            {
                // Touch doesn't exist no more
                _touchID = 0;
            }
        }
    }
    
    
    // When the dragging touch ended, finalize the movement to one of the selections
    void KoalaSwitchState::onTouchEnded(ichigo::Agent *agent)
    {
        // Preform drag to final position
        onTouchMoved(agent);
        
        // End the touch (and begin the end animation)
        _touchID = 0;
        _touchEnding = true;
    }
}