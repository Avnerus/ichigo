#ifndef __KOALA_ITEMDRAGSTATE_H__
#define __KOALA_ITEMDRAGSTATE_H__

#include "FSMState.h"
#include "SpriteActorView.h"


namespace koala
{
    class ItemDragState : public ichigo::FSMState
    {
    public:
        
        ItemDragState();
        virtual ~ItemDragState();
        
        virtual void            init();
        virtual void            onEnter();
        virtual void            onExit();
        virtual void            onUpdate(float dt);
        
        void                    onTouchMoved(ichigo::Agent *agent);
        void                    onTouchEnded(ichigo::Agent *agent);
        
        void                    setTouchID(int touchID);
        
    protected:
        
        void                        endDrag();
        
        ichigo::SpriteActorView    *_itemView;
        ichigo::Point               _initialPos;
        int                         _touchID;
    };
}


#endif // __KOALA_ITEMDRAGSTATE_H__
