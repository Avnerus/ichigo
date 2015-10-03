#include "DirectorView.h"
#include "SceneView.h"
#include "Director.h"


namespace ichigo
{
    DirectorView::DirectorView(Agent *agent)
    : View(agent)
    {
        _type = "DirectorView";
        _currentSceneView = NULL;
    }
    
    
    DirectorView::~DirectorView()
    {
    }
    
    
    // Called on initialization
    void DirectorView::init()
    {
        View::init();
    }
    
    
    // Configure view data from JSON structure
    void DirectorView::deserialize(Json::Value &configData)
    { 
        View::deserialize(configData);
    }
    
    
    // Called every frame
    void DirectorView::update(float dt)
    {
        View::update(dt);
    }
    
    Rect DirectorView::getBoundingBox() {
        int height;
        int width;
        
        getScreenSize(width, height);        
        
        return Rect(-width / 2.0f, -height / 2.0f, width / 2.0f, height /2.0f);
    }
}
