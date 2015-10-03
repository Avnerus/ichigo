#ifndef __ICHIGO_STRETCHABLESTATE_H__
#define __ICHIGO_STRETCHABLESTATE_H__

#include "FSMState.h"


namespace ichigo
{
    class StretchableState : public FSMState
    {
    public:
        StretchableState();
        virtual ~StretchableState();
        
        void         onTouchBegan(Agent *director);
        
    protected:
        std::string     _stretchingStateName;
    };
}


#endif // __ICHIGO_STRETCHABLESTATE_H__
