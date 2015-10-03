#include "Item.h"

#include "SpriteActorView.h"
#include "DataManager.h"


namespace koala
{
    Item::Item()
    {
        _description = "An item";
    };
    
    
    Item::~Item()
    {
        
    }
    
    
    // Load parameters from Json file
    void Item::deserialize(Json::Value &agentConfig)
    {
        Agent::deserialize(agentConfig);
        
        setDescription(ichigo::DataManager::getString(agentConfig, "desc", getDescription()));
    }
    
    
    // Sets a textual description of the item
    void Item::setDescription(const std::string &desc)
    {
        _description = desc;
    }
    
    
    // Returns the description of this item
    std::string Item::getDescription()
    {
        return _description;
    }
}