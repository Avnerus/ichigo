#include "LabelView.h"
#include "DataManager.h"

namespace ichigo {
    
    LabelView::LabelView(Agent *agent)
    : ActorView(agent) {
        _text = "";
    }
    
    
    LabelView::~LabelView() {
    }
            
    
    void LabelView::setFont(std::string font) {
        _BMFont = font;
    }
    
    void LabelView::setText(std::string text) {
        _text = text;
    }
    
    void LabelView::deserialize(Json::Value &configData) {
        ActorView::deserialize(configData);
        setFont(DataManager::getString(configData, "font"));
    }
    Rect LabelView::getBoundingBox() {
        return Rect(0.0f, 0.0f, 0.0f, 0.0f);
    }    
}
