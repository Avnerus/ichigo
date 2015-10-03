#ifndef __ICHIGO_COCOSUPDATINGSCENE_H__
#define __ICHIGO_COCOSUPDATINGSCENE_H__

#include "cocos2d.h"
using namespace cocos2d;


namespace ichigo
{
    class CocosUpdatingScene : public CCScene
    {
    public:
        
        virtual void update(ccTime dt);
        
        SCENE_NODE_FUNC(CocosUpdatingScene);
    };
}


#endif  // __ICHIGO_COCOSUPDATINGSCENE_H__
