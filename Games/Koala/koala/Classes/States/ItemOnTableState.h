#ifndef __KOALA_ITEMONTABLESTATE_H__
#define __KOALA_ITEMONTABLESTATE_H__

#include "FSMState.h"
#include "SpriteActorView.h"


namespace koala
{
    class ItemOnTableState : public ichigo::FSMState
    {
    public:
        
        ItemOnTableState();
        virtual ~ItemOnTableState();
        
        virtual void            init();
        virtual void            onEnter();
        virtual void            onExit();
        virtual void            onUpdate(float dt);
        
        void                    onTouchStarted(ichigo::Agent *agent);
        
    protected:
        
        ichigo::SpriteActorView    *_itemView;
    };
}


#endif // __KOALA_ITEMONTABLESTATE_H__
