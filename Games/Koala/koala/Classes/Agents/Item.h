#ifndef __KOALA_ITEM_H__
#define __KOALA_ITEM_H__

#include "Agent.h"


namespace koala
{
    class Item : public ichigo::Agent
    {
    public:
        
        Item();
        virtual ~Item();
        
        virtual void            deserialize(Json::Value &agentConfig);
        
        virtual void            setDescription(const std::string &desc);
        virtual std::string     getDescription();
        
    protected:
        
        std::string     _description;
    };
}


#endif // __KOALA_ITEM_H__
