#ifndef __ICHIGO_LABEL_H__
#define __ICHIGO_LABEL_H__

#include "ActorView.h"

namespace ichigo {
    
    class LabelView : public ActorView {
    public:
        
        LabelView(Agent *agent);
        virtual ~LabelView();
        
        virtual void    setText(std::string text);
        virtual void    setFont(std::string font);
        virtual void    deserialize(Json::Value &configData);
        virtual Rect    getBoundingBox();
      
    protected:
        std::string _text;
        std::string _BMFont;

    };
}


#endif  // __ICHIGO_LABEL_H__
