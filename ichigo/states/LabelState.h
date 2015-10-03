#ifndef __ICHIGO_LABELSTATE_H__
#define __ICHIGO_LABELSTATE_H__


#include "FSMState.h"
#include "LabelView.h"


namespace ichigo 
{
    class LabelState : public FSMState  
    {      
    public:
        
        LabelState();
        virtual ~LabelState();
        
        virtual void    showFor(float seconds);
        virtual void    onEnter();
        virtual void    init();
        void            onTimerEnded(Agent *waitingAgent);
        
    protected:
        LabelView *_labelView;
    };
}

#endif // __ICHIGO_LABELSTATE_H__