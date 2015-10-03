#include "StretchingState.h"
#include "TouchPoint.h"
#include "Director.h"
#include "View.h"
#include "Utils.h"


namespace ichigo
{
    StretchingState::StretchingState(
        bool canDrag /* = true */, 
        bool canScale /* = true */, 
        bool canRotate /* = true */, 
        bool limitToBoundingBox /* = true */
    ) {
        _name = "Stretching";
        _touchID1 = 0;
        _touchID2 = 0;
        _canDrag = canDrag;
        _canScale = canScale;
        _canRotate = canRotate;
        _limitToBoundingBox = limitToBoundingBox;
        _maxScale = 0;
        _minScale = 0;
        
        for (int i = 0; i < 2; i++)
        {
            _boundsMin[i] = Point(-4000, -4000);
            _boundsMax[i] = Point(4000, 4000);
        }
        
        _eventCallbacks["OnTouchStarted"] = std::tr1::bind(&StretchingState::onTouchBegan, this, _1);
        _eventCallbacks["OnTouchMoved"] = std::tr1::bind(&StretchingState::onTouchMoved, this, _1);
        _eventCallbacks["OnTouchEnded"] = std::tr1::bind(&StretchingState::onTouchEnded, this, _1);
    }
    
    
    StretchingState::~StretchingState()
    {
    }
    
    void StretchingState::init() {
        if (_limitToBoundingBox) {
            View *view = _agent->getView();
            Rect boundingBox = view->getBoundingBox();
            std::cout << "StrechingState::init() " << _agent->getName() << " Limit Bounds " << boundingBox.minX << "," <<  boundingBox.minY << "," << boundingBox.maxX << "," << boundingBox.maxY << std::endl;
            setLimitsForBounds(boundingBox.minX, boundingBox.minY, boundingBox.maxX, boundingBox.maxY);   
        }           
    }
    
    // Set the name of the state to return to once touchy-time is over
    void StretchingState::setIdleStateName(std::string name)
    {
        _idleStateName = name;
    }
    
    
    // Add a touch point to this state
    void StretchingState::addTouchPoint(TouchPoint *touchPoint)
    {
        if (_touchID1 == 0)
        {
            _touchID1 = touchPoint->getID();
            _touchPoint1 = touchPoint->getPos();
            
            touchPoint->markAsHandled();
            
            // std::cout << "Stretching added tp1 for " << _agent->getType() << std::endl;
        }
        else if (_touchID2 == 0)
        {
            _touchID2 = touchPoint->getID();
            _touchPoint2 = touchPoint->getPos();
            
            touchPoint->markAsHandled();
            
            // std::cout << "Strtching added tp2 for " << _agent->getType() << std::endl;
        }
    }
    
    
    // Sets the min and max scales the agent can get. Value of 0 means unlimited
    void StretchingState::setScaleLimits(float maxScale /* = 0 */, float minScale /* = 0 */)
    {
        _maxScale = maxScale;
        _minScale = minScale;
        
        // Make sure current scale is correct
        if (_agent && _agent->getView())
        {
            float scale = _agent->getView()->getScale();
            if (scale < minScale)
            {
                _agent->getView()->setScale(minScale);
            }
            if (scale > maxScale)
            {
                _agent->getView()->setScale(maxScale);
            }
        }
    }
    
    
    // Sets the min and max bounds the agent can be positioned at. Bounds can be different depending on the current agent's scale,
    // so use whenMaximized to determine which bounds we are setting
    void StretchingState::setTranslateLimits(bool whenMaximized, float minX, float maxX, float minY, float maxY)
    {
        int scaleIndex = (whenMaximized ? 1 : 0);
        
        _boundsMin[scaleIndex].x = minX;
        _boundsMin[scaleIndex].y = minY;
        _boundsMax[scaleIndex].x = maxX;
        _boundsMax[scaleIndex].y = maxY;
    }
    
    
    // Automatically set scale and translate limits based on the given bounds so the agent will fill the whole screen at all times
    void StretchingState::setLimitsForBounds(float minX, float minY, float maxX, float maxY)
    {
        // std::cout << "StrechingState::setLimitsForBounds() " << _agent->getName() << " limits to " << minX << "," << minY << "," << maxX << "," << maxY << std::endl;
        int screenWidth;
        int screenHeight;
        Director::getInstance()->getScreenSize(screenWidth, screenHeight);
        
        // Find minimal zoom for both width and height. The larger one is the minimal zoom with the object covering the whole screen.
        float boundsWidth = maxX - minX;
        float boundsHeight = maxY - minY;
        
        // std::cout << "StrechingState::setLimitsForBounds() " << _agent->getName() << " Bounds width: " << boundsWidth << "Bounds height: " << boundsHeight << std::endl;
        
        float minWidthZoom = (float)screenWidth / boundsWidth;
        float minHeightZoom = (float)screenHeight / boundsHeight;
        float minZoom = (minWidthZoom > minHeightZoom ? minWidthZoom : minHeightZoom);
    
        // std::cout << "StrechingState::setLimitsForBounds() " << _agent->getName() << " mininimum zoom " << minZoom << std::endl;        
        setScaleLimits(1.0f, minZoom);        
        
        // Find min and max agent coordinates based on agent bounds around the center and screen size
        float minPosX = -maxX + (float)screenWidth;
        float maxPosX = -minX;
        if (maxPosX < minPosX)
        {
            maxPosX = minPosX = (float)screenWidth / 2.0f;
        }
        float minPosY = -maxY + (float)screenHeight;
        float maxPosY = -minY;
        if (maxPosY < minPosY)
        {
            maxPosY = minPosY = (float)screenHeight / 2.0f;
        }
        // std::cout << "StrechingState::setLimitsForBounds() " << _agent->getName() << " translate limits when maximized (x,X,y,Y): " << minPosX << "," << maxPosX << "," << minPosY << "," << maxPosY << std::endl;
        setTranslateLimits(true, minPosX, maxPosX, minPosY, maxPosY);
        
        // Do the same, but for minimal zoom
        minPosX = -maxX * minZoom + (float)screenWidth;
        maxPosX = -minX * minZoom;
        if (maxPosX < minPosX)
        {
            maxPosX = minPosX;
        }
        minPosY = -maxY * minZoom + (float)screenHeight;
        maxPosY = -minY * minZoom;
        if (maxPosY < minPosY)
        {
            maxPosY = minPosY;
        }

        // std::cout << "StrechingState::setLimitsForBounds() " << _agent->getName() << " translate limits when minimized (x,X,y,Y): " << minPosX << "," << maxPosX << "," << minPosY << "," << maxPosY << std::endl;
        setTranslateLimits(false, minPosX, maxPosX, minPosY, maxPosY);
    }
    
    
    // Move agent so focusPoint will be in the middle of the screen
    void StretchingState::focusOnPoint(const ichigo::Point &focusPoint)
    {
        int screenWidth;
        int screenHeight;
        Director::getInstance()->getScreenSize(screenWidth, screenHeight);
        
        // Find focus offset in screen coordinates
        Point screenFocus = _agent->getView()->convertLocalToScreen(focusPoint);
        screenFocus.x = ((float)screenWidth / 2.0f) - screenFocus.x;
        screenFocus.y = ((float)screenHeight / 2.0f) - screenFocus.y;
        
        // Find the needed offset in local coordinates and move agent by it
        Point localOffset = _agent->getView()->convertScreenToLocal(screenFocus);
        _agent->getView()->setPosition(localOffset);
    }
    
    
    // Callback function for when a touch has started
    void StretchingState::onTouchBegan(ichigo::Agent *director)
    {
        View *view = _agent->getView();
        
        // Go over all current touches
        TouchList &touches = ((Director *)director)->getTouchList();
        std::cout << "Stretching for " << _agent->getType() << " touches: " << touches.size() << std::endl;
        for (TouchList::iterator it = touches.begin(); it != touches.end(); it++)
        {
            // Check that this touch wasn't handled by other agents and that it is within agent bounds
            if (!it->second->wasHandled() && it->second->getID() != _touchID1 && !it->second->hasEnded() && view->isTouched(it->second->getPos()))
            {
                // New point detected, add it to the list
                addTouchPoint(it->second.get());
            }
        }
    }
    
    
    // Callback function for when an existing touch has moved
    void StretchingState::onTouchMoved(ichigo::Agent *director)
    {
        //onTouchBegan(director);
        
        if (_touchID2 == 0)
        {
            // We only have one touch point, so this is a drag
            TouchPoint *touchPoint = ((Director *)director)->getTouchPoint(_touchID1);
            if (touchPoint)
            {
                // Drag it
                moveAgentToTouchPosition(touchPoint);
                _touchPoint1 = touchPoint->getPos();
            }
            
            if (!touchPoint || touchPoint->hasEnded())
            {
                // Can't find the only touch point, probably missed it. End the state.
                endDrag();
            }
        }
        else
        {
            // Both touch points are active, scale and rotate!
            TouchPoint *tp1 = ((Director *)director)->getTouchPoint(_touchID1);
            TouchPoint *tp2 = ((Director *)director)->getTouchPoint(_touchID2);
            
            if (tp1 && tp2)
            {
                bool tp1IsAnchor = true;
                Point anchorPoint = tp1->getPos();
                TouchPoint *movingPoint = tp2;
                
                // Check which of the points has moved
                if (tp1->getPos() != _touchPoint1)
                {
                    tp1IsAnchor = false;
                    anchorPoint = tp2->getPos();
                    movingPoint = tp1;
                }
                
                // Find how points moved in relation to each other
                float scale = 0;
                float rotation = 0;
                Utils::calcMultitouchTransform(&anchorPoint, movingPoint, &scale, &rotation);
                
                // Apply transformations around anchor point
                View *agentView = _agent->getView();
                Point localAnchorBefore = agentView->convertScreenToLocal(anchorPoint);
                agentView->setPivot(localAnchorBefore);
                
                if (_canScale)
                {
                    scale = agentView->getScale() * scale;
                    
                    if (scale < _minScale)
                    {
                        scale = _minScale;
                    }
                    if (_maxScale > 0 && scale > _maxScale)
                    {
                        scale = _maxScale;
                    }
                    
                    agentView->setScale(scale);                    
                }
                
                if (_canRotate)
                {
                    rotation = agentView->getAngle() + rotation;
                    agentView->setAngle(rotation);
                }
                
                agentView->setPivot(Point(0, 0));
                
                if (_canDrag)
                {
                    // Attempt to fix offset (pivot doesn't seem to work always)
                    Point localAnchorAfter = agentView->convertScreenToLocal(anchorPoint);
                    Point transformationDelta = localAnchorBefore - localAnchorAfter;
                    agentView->setPosition(agentView->getPosition() - transformationDelta);
                }
               
                // Save touch positions for next time
                _touchPoint1 = tp1->getPos();
                _touchPoint2 = tp2->getPos();
                
                // Both points are ending now
                if (tp1->hasEnded() && tp2->hasEnded())
                {
                    endDrag();
                }
            }
            else if (!tp1)
            {
                // Lost touchpoint 1
                _touchID1 = _touchID2;
                _touchID2 = 0;
                _touchPoint1 = _touchPoint2;
                moveAgentToTouchPosition(tp2);
                _touchPoint1 = tp2->getPos();
            }
            else if (!tp2)
            {
                // Lost touchpoint 2
                _touchID2 = 0;
                moveAgentToTouchPosition(tp1);
                _touchPoint1 = tp1->getPos();
            }
            else
            {
                // Lost both touchpoints
                endDrag();
            }
        }
        
        // Make sure all the transformations didn't move the agent outside the bounds
        keepInBounds();
    }
    
    
    // Callback function for when an existing touch ended
    void StretchingState::onTouchEnded(ichigo::Agent *director)
    {
        onTouchMoved(director);
    }
    
    
    // Moves the agent to the position of the touch
    void StretchingState::moveAgentToTouchPosition(ichigo::TouchPoint *touchPoint)
    {
        if (touchPoint && _canDrag)
        {
            View *view = _agent->getView();
            Point touchOffset = touchPoint->getPos() - touchPoint->getPrevPos();
            Point newLocalPos = view->convertScreenToLocal(view->getPositionOnScreen() + touchOffset);
            view->setPosition(newLocalPos);
        }
    }
    
    
    // Ends this charade
    void StretchingState::endDrag()
    {
        _touchID1 = 0;
        _touchID2 = 0;
        _agent->getFSM()->transitionTo(_idleStateName);
    }
    
    
    // Keeps the object inside the given bounds.
    void StretchingState::keepInBounds()
    {
        // Calculate bounds by interpolation based on the current scale of the agent
        float currentScaleFactor = 1.0f;
        if (_maxScale > 0 && _maxScale != _minScale)
        {
                currentScaleFactor = (_agent->getView()->getScale() - _minScale) / (_maxScale - _minScale);
        }
        Point boundsMin = _boundsMin[0] + ((_boundsMin[1] - _boundsMin[0]) * currentScaleFactor);
        Point boundsMax = _boundsMax[0] + ((_boundsMax[1] - _boundsMax[0]) * currentScaleFactor);
        
        Point pos = _agent->getView()->getPosition();
        
        if (pos.x < boundsMin.x)
        {
            pos.x = boundsMin.x;
        }
        if (pos.x > boundsMax.x)
        {
            pos.x = boundsMax.x;
        }
        if (pos.y < boundsMin.y)
        {
            pos.y = boundsMin.y;
        }
        if (pos.y > boundsMax.y)
        {
            pos.y = boundsMax.y;
        }
        
        _agent->getView()->setPosition(pos);
    }
}
