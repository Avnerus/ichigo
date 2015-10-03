#ifndef __ICHIGO_COCOSSCENEVIEW_H__
#define __ICHIGO_COCOSSCENEVIEW_H__

#include "SceneView.h"
#include "CocosUpdatingScene.h"
#include "CocosTouchLayer.h"

#include "cocos2d.h"
using namespace cocos2d;

#define BGCOLOR_LAYER_ZORDER    (-1000)
#define BGCOLOR_LAYER_WIDTH     8000
#define BGCOLOR_LAYER_HEIGHT    8000

namespace ichigo
{
    class CocosSceneView : public SceneView
    {
    public:
        
        CocosSceneView(Agent *agent);
        virtual ~CocosSceneView();
        
        virtual void                init();
        virtual void                update(float dt);
        
        virtual void                setPosition(const Point &pos);
        virtual void                setScale(float scale);
        virtual void                setAngle(float angle);
        virtual void                setBGColor(const Color &bgColor);
        virtual void                setPivot(const Point &pivot);
       
        virtual Point               convertLocalToScreen(const Point &localPos);  
        virtual Point               convertScreenToLocal(const Point &screenPos);  
        
        virtual void                addLayer(LayerView *layerView);
        virtual void                removeLayer(LayerView *layerView);
        
        virtual void                setAsCurrent(bool isCurrent);
        
        virtual void               *getInternalData();
        
    protected:
    
        CocosUpdatingScene         *_ccScene;
        CocosTouchLayer            *_touchLayer;
        CCLayerColor               *_bgColorLayer;
    };
}


#endif  // __ICHIGO_COCOSSCENEVIEW_H__
