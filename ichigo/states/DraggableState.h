#ifndef __ICHIGO_DRAGGABLESTATE_H__
#define __ICHIGO_DRAGGABLESTATE_H__


#include "FSMState.h"


namespace ichigo {
    
    class DraggableState : public FSMState  {
    public:
      DraggableState();
      virtual ~DraggableState();

      void onTouchBegan(Agent* director);
  };
}

#endif  // __ICHIGO_DRAGGABLESTATE_H__