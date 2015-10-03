#ifndef __IT_KOALASWITCHSTATE_H_
#define __IT_KOALASWITCHSTATE_H_

#include "ichigo.h"


namespace it
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
        int                 _screenHeight;
        bool                _isViewingReality;
        int                 _touchID;
        float               _touchY;
        bool                _touchEnding;
    };
}


#endif // __IT_KOALASWITCHSTATE_H_
