#ifndef __KOALA_BEETLE_H__
#define __KOALA_BEETLE_H__

#include "ichigo.h"
#include "Tree.h"

#include <tr1/memory>
#include <vector>


namespace koala
{       
    class BeetleSwarm : public ichigo::Actor
    {
    public:
        
        BeetleSwarm();
        virtual ~BeetleSwarm();
        
        Tree                    *getTree();
        void                     setTree(Tree *tree);
        float                    getClimbSpeed();
        void                     setClimbSpeed(float climbSpeed);
        float                    getEatingSpeed();
        void                     setEatingSpeed(float eatingSpeed);
        void                     setLevel(int level);
        int                      getLevel();
        BranchData              *getCurrentBranch();
        void                     setCurrentBranch(BranchData *);
        void                     Eat();
        
        
                
        virtual bool    init();
        virtual void    deserialize(Json::Value &agentConfig);
        
        ichigo::SpriteActorView *getSpriteView();
        
    private:
        
    protected:    
        float _climbSpeed;
        float _eatingSpeed;
        int   _level;
        BranchData  *_currentBranch;
        
        ichigo::SpriteActorView *_swarmView;
        Tree *_tree;
    };
}


#endif // __KOALA_TREE_H__
