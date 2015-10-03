#ifndef __KOALA_TREE_H__
#define __KOALA_TREE_H__

#include "ichigo.h"
#include "TileMapView.h"
#include "Nature.h"

#include <tr1/memory>
#include <vector>


namespace koala
{
    class RealKoala;    
    class Nature;
    
    
    class BranchData {
    public:
        int foliageLevel;    
        ichigo::Tile *tile;    
        ichigo::Agent *foliage;
    };
    
    
    class LevelData {
    public:
        std::tr1::shared_ptr<BranchData> leftBranch;
        std::tr1::shared_ptr<BranchData> rightBranch;                
    };
    
    
    typedef std::vector< std::tr1::shared_ptr<LevelData> > BranchLevelList;
    
    
    
    class Tree : public ichigo::Actor
    {
    public:
        
        Tree();
        virtual ~Tree();
        
        
        void                    GenerateBranchData();
        void                    RandomizeFoliage();
        ichigo::TileMapView     *getTileMap();
        const BranchLevelList   &getBranchLevelList();
        void                    SetFoliageLevel(BranchData *branch, int level);
        
        virtual bool    init();
        virtual void    deserialize(Json::Value &agentConfig);      
        
    private:
        ichigo::Agent*  initFoliage(ichigo::Tile *tile);
        
    protected:    
        ichigo::TileMapView*    _tileMap;
        BranchLevelList         _branchLevelList;
        Nature*                 _nature;
    };
}


#endif // __KOALA_TREE_H__
