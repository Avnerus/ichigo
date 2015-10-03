#ifndef __KOALA_NATURE_H__
#define __KOALA_NATURE_H__

#include "Actor.h"
#include "Point.h"
#include "DataManager.h"
#include "Tree.h"

#include <map>

namespace koala
{
    class Tree;

    class Nature : public ichigo::Actor
    {
    public:
        
        Nature();
        virtual ~Nature();
        
        void setCurrentTree(Tree *tree);
        void setMaxBeetleSwarmLevel(int level);
        void spawnBeetleSwarm();
        
        virtual bool    init();
        virtual void    deserialize(Json::Value &agentConfig);      
        
    protected:    
        Tree *_currentTree;
        int _maxBeetleSwarmLevel;
    };
}


#endif // __KOALA_NATURE_H__
