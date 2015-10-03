#include "CocosDirectorView.h"
#include "CocosSceneView.h"


namespace ichigo
{
    CocosDirectorView::CocosDirectorView(Agent *agent)
    : DirectorView(agent)
    {
        _ccDirector = cocos2d::CCDirector::sharedDirector();
    }
    
    
    CocosDirectorView::~CocosDirectorView()
    {
    }
    
    
    // Returns a pointer to the CCDirector
    void *CocosDirectorView::getInternalData()
    {
        return _ccDirector;
    }
    
    
    // Sets the pivit. Has no meaning in the director
    void CocosDirectorView::setPivot(const ichigo::Point &pivot)
    {
        
    }
    
    
    // Adds a scene to the director. Nothing to do here, since in Cocos the director doesn't actually hold scenes.
    void CocosDirectorView::addScene(SceneView *sceneView)
    {
    }
    
    
    // Removes a scene from the director. Nothing to do here, since Cocos's director doesn't actually hold all the scenes
    void CocosDirectorView::removeScene(SceneView *sceneView)
    {
    }
    
    
    // Sets a scene as the currently active scene
    void CocosDirectorView::setCurrentScene(SceneView *sceneView)
    {
        
        // Is this the first time we are setting a scene?
        if (!_currentSceneView)
        {
            _ccDirector->runWithScene((CCScene *)sceneView->getInternalData());
        }
        else
        {
            _ccDirector->replaceScene((CCScene *)sceneView->getInternalData());
        }

        _currentSceneView = sceneView;
    }
    
    
    // Returns the scene currently running
    SceneView *CocosDirectorView::getCurrentScene()
    {
        return _currentSceneView;
    }
    
    
    // Returns the screen position of point in director's local coordinate system
    Point CocosDirectorView::convertLocalToScreen(const ichigo::Point &localPos)
    {
        return localPos;        
    }
    
    
    // Converts a point in screen coordinates to local coordinates of the director
    Point CocosDirectorView::convertScreenToLocal(const ichigo::Point &screenPos)
    {
        return screenPos;
    }
    
    
    // Returns the screen dimensions (in pixels)
    void CocosDirectorView::getScreenSize(int &width, int &height)
    {
        cocos2d::CCSize size = _ccDirector->getWinSize();
        width = size.width;
        height = size.height;
    }
}