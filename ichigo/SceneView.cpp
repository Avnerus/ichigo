#include "SceneView.h"
#include "DataManager.h"


namespace ichigo
{
    SceneView::SceneView(Agent *agent)
    : View(agent), _bgColor(0, 0, 0, 255)
    {
        _type = "SceneView";
        _parent = NULL;
    }
    
    
    SceneView::~SceneView()
    {
    }
    
    
    // Gets called during initialization
    void SceneView::init()
    {
        View::init();
    }
    
    
    // Configs the view's data from a JSON structure
    void SceneView::deserialize(Json::Value &configData)
    {
        View::deserialize(configData);
        
        setBGColor      (DataManager::getColor(configData, "bgColor",       getBGColor()));
    }
    
    
    // Gets called every frame
    void SceneView::update(float dt)
    {
        View::update(dt);
    }
    
    
    // Sets the parent view (the director of this scene)
    void SceneView::setParent(ichigo::DirectorView *directorView)
    {
        _parent = directorView;
    }
    
    
    // Sets the background color of the scene
    void SceneView::setBGColor(const ichigo::Color &bgColor)
    {
        _bgColor = bgColor;
    }
    
    
    // Returns the background color of the scene
    const Color &SceneView::getBGColor()
    {
        return _bgColor;
    }
    
    Rect SceneView::getBoundingBox() {
        return _parent->getBoundingBox();
    }
}
