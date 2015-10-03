#ifndef __ICHIGO_BUTTONSTATE_H__
#define __ICHIGO_BUTTONSTATE_H__


#include "FSMState.h"

#include <string>


namespace ichigo 
{
    class ButtonState : public FSMState  
    {      
    public:
        
        ButtonState();
        virtual ~ButtonState();
        
        virtual bool    isPressed();
        virtual void    setUpAnimation(const std::string &animationName);
        virtual void    setDownAnimation(const std::string &animationName);

        void            onTouchBegan(Agent *director);
        void            onTouchMoved(Agent *director);
        void            onTouchEnded(Agent *director);
        
    protected:
        
        void            setPressed(bool pressed);
        
        bool            _isPressed;
        int             _touchID;
        std::string     _upAnimation;
        std::string     _downAnimation;
    };
}

#endif // __ICHIGO_BUTTONSTATE_H__