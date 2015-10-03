#ifndef __IT_ITEM_H__
#define __IT_ITEM_H__

#include "ichigo.h"


namespace it 
{
    class Item : public ichigo::Actor
	{    
    public:
		
        Item();
        virtual ~Item();
		
        virtual bool init();
    };    
}



#endif // __IT_ITEM_H__