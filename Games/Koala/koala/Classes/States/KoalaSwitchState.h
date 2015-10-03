#ifndef __KOALA_KOALASWITCHSTATE_H_
#define __KOALA_KOALASWITCHSTATE_H_

#include "ichigo.h"


namespace koala
{
    class KoalaSwitchState : public ichigo::FSMState
    {
    public:
        
        KoalaSwitchState();
        
        virtual void    onUpdate(float dt);
        
        void            onTouchStarted(ichigo::Agent *agent);
        void            onTouchMoved(ichigo::Agent *agent);
        void            onTouchEnded(ichigo::Agent *agent);
        
    protected:
        
        void            animateTouchEnding(float dt);
        
        ichigo::SceneView  *_sceneView;
        ichigo::LayerView  *_realityLayer;
        ichigo::LayerView  *_dreamLayer;
        ichigo::ActorView  *_hudBG;
        int                 _screenHeight;
        bool                _isViewingReality;
        int                 _touchID;
        float               _touchY;
        bool                _touchEnding;
    };
}


#endif // __KOALA_KOALASWITCHSTATE_H_
