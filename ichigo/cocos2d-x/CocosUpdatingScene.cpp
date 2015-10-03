#include "CocosUpdatingScene.h"
#include "Director.h"


namespace ichigo
{
    // This update function will be schedualed for the active scene to get updated each frame. We use it to send the
    // update to the Director, and from there to all objects in the game
    void CocosUpdatingScene::update(ccTime dt)
    {
        Director::getInstance()->update(dt);
        
        CCScene::update(dt);
    }
}
