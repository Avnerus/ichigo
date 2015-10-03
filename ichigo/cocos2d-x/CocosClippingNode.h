#ifndef __ICHIGO_COCOSCLIPPINGNODE_H__
#define __ICHIGO_COCOSCLIPPINGNODE_H__

#include "cocos2d.h"
using namespace cocos2d;


namespace ichigo 
{
    class CocosClippingNode : public CCNode
    {
    public:
        
        CocosClippingNode();
        virtual ~CocosClippingNode();
        
        static          CocosClippingNode *clippingNode();
        virtual void    visit();
        
        void            shouldClip(bool clip);
        void            setClipRect(const CCRect &rect);
        
    protected:
        
        bool        _shouldClip;
        CCRect      _clippingRect;
    };
}

#endif // __ICHIGO_COCOSCLIPPINGNODE_H__
