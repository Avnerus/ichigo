#ifndef __ICHIGO_COCOSLABELVIEW_H__
#define __ICHIGO_COCOSLABELVIEW_H__

#include "LabelView.h"
#include "cocos2d.h"
using namespace cocos2d;

namespace ichigo {
    
    class CocosLabelView : public LabelView {
    public:
        
        CocosLabelView(Agent *agent);
        virtual ~CocosLabelView();
        
        virtual void        init();
        virtual void        update(float dt);        
        virtual void        *getInternalData();
        virtual void        addChild(ActorView *child);
        virtual void        removeChild(ActorView *child);
        virtual Point       convertLocalToScreen(const Point &localPos);  
        virtual Point       convertScreenToLocal(const Point &screenPos);
        
        virtual void        setPivot(const Point &pivot);
        virtual void        setVisible(bool isVisible);
        virtual void        setPosition(const Point &pos);
        virtual void        setScale(float scale);
        virtual void        setAngle(float angle);
        virtual void        setZOrder(int zOrder);
        
        virtual void        setText(std::string text);
        virtual void        setFont(std::string font);
      
    protected:
        CCLabelBMFont * _ccLabel;
    };
}


#endif  // __ICHIGO_COCOSLABELVIEW_H__
