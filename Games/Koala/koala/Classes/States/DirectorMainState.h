#ifndef __KOALA_DIRECTORRUNNING_H__
#define __KOALA_DIRECTORRUNNING_H__

#include "FSMState.h"
#include "Agent.h"
#include "DreamKoala.h"


namespace koala
{    
    class DirectorMainState : public ichigo::FSMState  
    {
    public:
        
        DirectorMainState();
        virtual ~DirectorMainState();
        
        virtual void    onUpdate(float dt);
        virtual void    onEnter();   
        virtual void    onExit();
        
    protected:
        DreamKoala  *_dreamKoala;        
    };
}


#endif // __KOALA_DIRECTORRUNNING_H__
