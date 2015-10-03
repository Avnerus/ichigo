#ifndef __KOALA_NATUREDEFAULTSTATE_H__
#define __KOALA_NATUREDEFAULTSTATE_H__

#include "FSMState.h"
#include "Agent.h"
#include "Nature.h"


namespace koala
{    
    class NatureDefaultState : public ichigo::StretchingState  
    {
    public:
        
        NatureDefaultState();
        virtual ~NatureDefaultState();
        
        virtual void    onUpdate(float dt);
        virtual void    onEnter();
        virtual void    onExit();
        virtual void    init();
        
    protected:
        Nature  *_nature;        
    };
}


#endif // __KOALA_NATUREDEFAULTSTATE_H__
