#include "Item.h"


namespace it
{
    Item::Item() 
    : ichigo::Actor()
	{
		std::cout << "An item was created" << std::endl;
    }
    
    
    Item::~Item() 
	{   
        std::cout << "An item was destroyed" << std::endl;        
    }
    
	
    bool Item::init()
	{
		return Actor::init();
    }	
}