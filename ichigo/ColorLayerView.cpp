#include "ColorLayerView.h"
#include "DataManager.h"


namespace ichigo
{
    ColorLayerView::ColorLayerView(Agent *agent)
    : LayerView(agent), _bgColor(0, 0, 0, 255), _width(0.0f), _height(0.0f)
    {
        _type = "ColorLayerView";
        _parent = NULL;
    }
    
    
    ColorLayerView::~ColorLayerView() {
    }
    
    
    // Configs the view's data from a JSON structure
    void ColorLayerView::deserialize(Json::Value &configData) {
        
        LayerView::deserialize(configData);
     
        setBGColor              (DataManager::getColor(configData, "bgColor", Color(0,0,0,255)));
        setWidth                (DataManager::getFloat(configData, "width", 0.0f));
        setHeight               (DataManager::getFloat(configData, "height", 0.0f));
    }
    
    
    // Sets the background color of the layer
    void ColorLayerView::setBGColor(const ichigo::Color &bgColor) {
        _bgColor = bgColor;
    }
    
    
    // Returns the background color of the layer
    const Color &ColorLayerView::getBGColor() {
        return _bgColor;
    }
    
    float ColorLayerView::getWidth() {
        return _width;
    }    
    
    float ColorLayerView::getHeight() {
        return _height;
    }
    
    void ColorLayerView::setWidth(float width) {
        _width = width;
    }
    void ColorLayerView::setHeight(float height) {
        _height = height;
    } 
    
    Rect ColorLayerView::getBoundingBox() {
        return Rect(-_width / 2.0f, -_height / 2.0f, _width / 2.0f, _height / 2.0f);
    }    
}
