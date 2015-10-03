#ifndef __ICHIGO_CHARACTERSTATE_H
#define __ICHIGO_CHARACTERSTATE_H


#include "FSMState.h"
#include "Character.h"

#include <string>


namespace ichigo 
{
    class CharacterState : public FSMState  
    {      
    public:
        
        CharacterState();
        virtual ~CharacterState();


        virtual void    init();
        
        void            onTouchStarted(Agent *director);
        
        
    protected:
        int             _touchID;
        Character*      _character;
        SpriteActorView* _characterView;
    };
}

#endif // __ICHIGO_CHARACTERSTATE_H