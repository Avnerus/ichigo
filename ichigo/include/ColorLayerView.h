#ifndef __ICHIGO_COLORLAYERVIEW_H__
#define __ICHIGO_COLORLAYERVIEW_H__

#include "LayerView.h"
#include "Point.h"


namespace ichigo
{
    
    class ColorLayerView : public LayerView
    {
    public:
        
        ColorLayerView(Agent *agent);
        virtual ~ColorLayerView();
        
        virtual void            deserialize(Json::Value &configData);
        virtual Rect            getBoundingBox();

        virtual float           getHeight();
        virtual float           getWidth();
        virtual void            setHeight(float height);
        virtual void            setWidth(float width);        
        
        virtual void            setBGColor(const Color &bgColor);
        virtual const Color     &getBGColor();

        
        
    protected:        
        float           _weight;
        float           _width;
        float           _height;
        Color           _bgColor;
    };
}


#endif  // __ICHIGO_COLORLAYERVIEW_H__
