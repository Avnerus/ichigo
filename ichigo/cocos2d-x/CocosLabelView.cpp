#include "CocosLabelView.h"


namespace ichigo {
    
    CocosLabelView::CocosLabelView(Agent *agent)
    : LabelView(agent) {
        _ccLabel = NULL;
        _text = "";
    }
    
    
    CocosLabelView::~CocosLabelView() {
    }
    
    
    // Gets called during initialization
    void CocosLabelView::init()
    {
        LabelView::init();                
    }
    
    
    // Gets called every frame
    void CocosLabelView::update(float dt)
    {
        LabelView::update(dt);
    }
    
    
    // Sets the layer's position
    void CocosLabelView::setPosition(const ichigo::Point &pos)
    {
        LabelView::setPosition(pos);
        
        if (_ccLabel)
        {
            // Set the position
            CCPoint glPos(pos.x, pos.y);
            _ccLabel->setPosition(glPos);
        }
    }
    
    
    // Set the layer's scale
    void CocosLabelView::setScale(float scale)
    {
        LabelView::setScale(scale);
        
        if (_ccLabel)
        {
            _ccLabel->setScale(scale);
        }
    }
    
    
    // Set the layer's angle (rotation)
    void CocosLabelView::setAngle(float angle)
    {
        LabelView::setAngle(angle);
        
        if (_ccLabel)
        {
            _ccLabel->setRotation(angle);
        }
    }
    
    
    // Sets the z-order of the layer
    void CocosLabelView::setZOrder(int zOrder)
    {
        LabelView::setZOrder(zOrder);
        
        // If this layer was already added to a CCScene, tell the CCScene our new z-order
        if (_parent && _ccLabel)
        {
            _ccLabel->getParent()->reorderChild(_ccLabel, zOrder);
        }
    }
    
    
    // Sets the pivot point for scales and rotation
    void CocosLabelView::setPivot(const ichigo::Point &pivot)
    {
        if (_ccLabel)
        {
            // Anchor point gets a normalized point
            CCPoint normalizedPivot;
            normalizedPivot.x = (pivot.x / _ccLabel->boundingBox().size.width) / 2.0f + 0.5f;
            normalizedPivot.y = (pivot.y / _ccLabel->boundingBox().size.height) / 2.0f + 0.5f;
            _ccLabel->setAnchorPoint(normalizedPivot);
        }
    }
    
    
    // Shows or hides the label
    void CocosLabelView::setVisible(bool isVisible)
    {
        LabelView::setVisible(isVisible);
        
        if (_ccLabel)
        {
            _ccLabel->setIsVisible(isVisible);
        }
    }
    
    // Returns the screen position of point in actor's local coordinate system
     Point CocosLabelView::convertLocalToScreen(const ichigo::Point &localPos)
     {
         Point retVal;

         if (_ccLabel)
         {
             CCPoint worldPos = _ccLabel->getParent()->convertToWorldSpace(ccp(localPos.x, localPos.y));

             retVal.x = worldPos.x;
             retVal.y = worldPos.y;
         }

         return retVal;        
     }


     // Converts a point in screen coordinates to local coordinates of this actor
     Point CocosLabelView::convertScreenToLocal(const ichigo::Point &screenPos)
     {
         Point retVal;

         if (_ccLabel)
         {
             CCPoint localPos = _ccLabel->getParent()->convertToNodeSpace(ccp(screenPos.x, screenPos.y));

             retVal.x = localPos.x;
             retVal.y = localPos.y;
         }

         return retVal;
     }
    
    
    // Adds a child actor to this label
    void CocosLabelView::addChild(ichigo::ActorView *child)
    {
        if (_ccLabel)
        {
            _ccLabel->addChild((CCNode *)child->getInternalData(), child->getZOrder());
            child->setParent(this);
        }
    }
    
    
    // Removes a child from this sprite
    void CocosLabelView::removeChild(ichigo::ActorView *child)
    {
        if (_ccLabel)
        {
            _ccLabel->removeChild((CCNode *)child->getInternalData(), false);
            child->setParent(NULL);
        }
    }
    
    void CocosLabelView::setFont(std::string font) {
        LabelView::setFont(font);
        _ccLabel = cocos2d::CCLabelBMFont::labelWithString(_text.c_str(), font.c_str());        
    }
    
    void CocosLabelView::setText(std::string text) {
        LabelView::setText(text);
        if (_ccLabel) {
            _ccLabel->setString(text.c_str());
        }
    }
    
    // Returns the actual cocos node
    void *CocosLabelView::getInternalData()
    {
        return _ccLabel;
    }
}
