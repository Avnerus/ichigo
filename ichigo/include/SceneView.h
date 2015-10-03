#ifndef __ICHIGO_SCENEVIEW_H__
#define __ICHIGO_SCENEVIEW_H__

#include "View.h"
#include "Point.h"
#include "Color.h"
#include "DirectorView.h"


namespace ichigo
{
    class LayerView;
    
    
    class SceneView : public View
    {
    public:
        
        SceneView(Agent *agent);
        virtual ~SceneView();
        
        virtual void            init();
        virtual void            deserialize(Json::Value &configData);
        virtual void            update(float dt);
        
        virtual void            setBGColor(const Color &bgColor);
        virtual const Color    &getBGColor();
        
        virtual void            addLayer(LayerView *layerView) = 0;
        virtual void            removeLayer(LayerView *layerView) = 0;
        virtual void            setParent(DirectorView *directorView);
        
        virtual void            setAsCurrent(bool isCurrent) = 0;
        virtual Rect            getBoundingBox();
        
    protected:
        
        DirectorView   *_parent;
        
        Color           _bgColor;
    };
}


#endif  // __ICHIGO_SCENEVIEW_H__
