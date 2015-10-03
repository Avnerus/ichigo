#ifndef __ICHIGO_CLIPPEDACTORVIEW_H__
#define __ICHIGO_CLIPPEDACTORVIEW_H__

#include "SpriteActorView.h"
#include <string>
#include <map>
#include <tr1/memory>


namespace ichigo
{    
    
    class ClippedActorView : public ActorView
    {
    public:
        
        ClippedActorView(Agent *agent);
        virtual ~ClippedActorView();
        
        virtual void            deserialize(Json::Value &agentConfig);
        virtual void            clipToBounds(bool clip);
        virtual bool            isClippingToBounds();
        virtual void            setClippingBounds(float x, float y, float w, float h);      
        virtual Point           getClippingSize();
        virtual void            setClippingSize(Point size);
      
        
    protected:
         bool        _clipToBounds;
         Point       _clippingOrigin;
         Point       _clippingSize;
    };
}


#endif  // __ICHIGO_CLIPPEDACTORVIEW_H__
