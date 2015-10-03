#include "CocosClippingNode.h"
#include <cmath>
#include <iostream>


namespace ichigo
{
    CocosClippingNode::CocosClippingNode()
    {
        _shouldClip = false;
    }
    
    
    CocosClippingNode::~CocosClippingNode()
    {        
    }
    
    
    // Static method to create a new autoreleased clipping node
    CocosClippingNode *CocosClippingNode::clippingNode()
    {
        CocosClippingNode *retVal = new CocosClippingNode();
        retVal->autorelease();
        return retVal;
    }
    
    
    // This method gets called by cocos and draws the node and its children. If clipping is activated, we will use OpenGL
    // to mask out drawing calls to pixels outside bounds
    void CocosClippingNode::visit()
    {
        if (!m_bIsVisible)
        {
            return;
        }
        
        // If clipping disabled, no need for this
        if (_shouldClip && _clippingRect.size.width > 0 && _clippingRect.size.height > 0)
        {
            // Translate the clipping rect from local coordiantes to screen coordiantes (take into account screen orientation)
            CCDirector *director = CCDirector::sharedDirector();
            CCSize winSize = director->getWinSize();
            CCPoint origin = convertToWorldSpaceAR(_clippingRect.origin);
            CCPoint topRight = convertToWorldSpaceAR(ccpAdd(_clippingRect.origin, ccp(_clippingRect.size.width, _clippingRect.size.height)));
            CCRect scissorRect = CCRectMake(origin.x, origin.y, fabs(topRight.x - origin.x), fabs(topRight.y - origin.y));
            
            ccDeviceOrientation devOrient = director->getDeviceOrientation();
            switch (devOrient)
            {
                case kCCDeviceOrientationPortraitUpsideDown:
                {
                    scissorRect.origin.x = winSize.width - scissorRect.size.width - scissorRect.origin.x;
                    scissorRect.origin.y = winSize.height - scissorRect.size.height - scissorRect.origin.y;

                    break;
                }
                case kCCDeviceOrientationLandscapeLeft:
                {
                    float temp = scissorRect.origin.x;
                    scissorRect.origin.x = scissorRect.origin.y;
                    scissorRect.origin.y = winSize.width - scissorRect.size.width - temp;
                    
                    temp = scissorRect.size.width;
                    scissorRect.size.width = scissorRect.size.height;
                    scissorRect.size.height = temp;
                    
                    break;
                }
                case kCCDeviceOrientationLandscapeRight:
                {
                    float temp = scissorRect.origin.y;
                    scissorRect.origin.y = scissorRect.origin.x;
                    scissorRect.origin.x = winSize.height - scissorRect.size.height - temp;
                    
                    temp = scissorRect.size.width;
                    scissorRect.size.width = scissorRect.size.height;
                    scissorRect.size.height = temp;
                    
                    break;
                }
                case kCCDeviceOrientationPortrait:
                default:
                    break;
            }
            
            // In case this is a retina display device, convert to correct resolution
            scissorRect = CC_RECT_POINTS_TO_PIXELS(scissorRect);
            
            // Use OpenGL to mask areas outside bounds
            glEnable(GL_SCISSOR_TEST);
            // std::cout << "CocosClippingNode::visit() glScissor: " << scissorRect.origin.x << "," << scissorRect.origin.y << "," << scissorRect.size.width << "," << scissorRect.size.height << std::endl;
            glScissor((GLint)scissorRect.origin.x, (GLint)scissorRect.origin.y, (GLint)scissorRect.size.width, (GLint)scissorRect.size.height);
        }
        
        // Clipping or no clipping, always call the node's visit, otherwise it will not be drawn
        CCNode::visit();
        
        // After drawing, disable clipping mask
        if (_shouldClip)
        {
            glDisable(GL_SCISSOR_TEST);
        }
    }
    
    
    // Set true to activate clipping
    void CocosClippingNode::shouldClip(bool clip)
    {
        _shouldClip = clip;
    }
    
    
    // Clipping bounds
    void CocosClippingNode::setClipRect(const CCRect &rect)
    {
        _clippingRect = rect;
    }
}
