#include "Tree.h"
#include "TileMapView.h"

#include "ichigo.h"


namespace koala
{
    Tree::Tree() {
    }
    
    
    Tree::~Tree() {        
    }
    
    bool Tree::init() {
        _tileMap = (ichigo::TileMapView *)_actorView;
        _nature = (Nature *)ichigo::Director::getInstance()->findByName("nature");        
        _nature->setCurrentTree(this);        
        
        GenerateBranchData();
        RandomizeFoliage();      
        
        return true;
    }
    
    
    void Tree::GenerateBranchData() {
        // Go over the tilemap and get the branch data
        for (int y = 0; y < _tileMap->getTileRows(); y++) {
            std::tr1::shared_ptr<LevelData> level = std::tr1::shared_ptr<LevelData>(new LevelData());
            
            ichigo::Tile *leftTile = _tileMap->getTile(0,y);
            if (leftTile->getID() == "LB") {
                level->leftBranch = std::tr1::shared_ptr<BranchData>(new BranchData());
                level->leftBranch->foliageLevel = 0;
                level->leftBranch->tile = leftTile;
                level->leftBranch->foliage = initFoliage(leftTile);
            }
            else {
                level->leftBranch = std::tr1::shared_ptr<BranchData>();
            }            
            ichigo::Tile *rightTile = _tileMap->getTile(2,y);
            if (rightTile->getID() == "RB") {
                level->rightBranch = std::tr1::shared_ptr<BranchData>(new BranchData());
                level->rightBranch->foliageLevel = 0;
                level->rightBranch->tile = rightTile;
                level->rightBranch->foliage = initFoliage(rightTile);
            }
            else {
                level->rightBranch = std::tr1::shared_ptr<BranchData>();
                
            }            
            _branchLevelList.push_back(level);
        }        
    }
    
    void Tree::RandomizeFoliage() {
        for (BranchLevelList::iterator it = _branchLevelList.begin(); it != _branchLevelList.end(); it++) {
            std::tr1::shared_ptr<LevelData> level = (*it);
            if (level->leftBranch) {
                level->leftBranch->foliageLevel = ichigo::Utils::randi(5);
                ichigo::SpriteActorView *foliageView = (ichigo::SpriteActorView *)level->leftBranch->foliage->getView();
                foliageView->playAnimation(ichigo::Utils::intToZeroPaddedString(level->leftBranch->foliageLevel, 1));
            }
            if (level->rightBranch) {
                level->rightBranch->foliageLevel = ichigo::Utils::randi(5);
                ichigo::SpriteActorView *foliageView = (ichigo::SpriteActorView *)level->rightBranch->foliage->getView();
                foliageView->playAnimation(ichigo::Utils::intToZeroPaddedString(level->rightBranch->foliageLevel, 1));
            }
        }        
    }
    
    void Tree::SetFoliageLevel(BranchData *branch, int level) {
        if (level < 0) {
            level = 0;
        }
        std::cout << "Tree::SetFoliageLevel : setting level to " << level << std::endl;
        branch->foliageLevel = level;
        ichigo::SpriteActorView *foliageView = (ichigo::SpriteActorView *)branch->foliage->getView();
        foliageView->playAnimation(ichigo::Utils::intToZeroPaddedString(branch->foliageLevel, 1));
    }
    
    
    ichigo::Agent*  Tree::initFoliage(ichigo::Tile *tile) {
        // Tile is a lift, load doors sprite
        ichigo::Agent *foliage = ichigo::AgentFactory::createAgent("Sprite");
        Json::Value foliageJson = ichigo::DataManager::getInstance()->loadFromJSON("foliage.json");
        foliage->loadFromJSON(foliageJson);
        foliage->getView()->setPosition(tile->getPosition());
        addChild(foliage);
        return foliage;
    }
    
    // Hold json data and use it later to initialize
    void Tree::deserialize(Json::Value &agentConfig)
    {
        ichigo::Actor::deserialize(agentConfig);        
        
    }
    ichigo::TileMapView *Tree::getTileMap() {
        return _tileMap;
    }
    
    const BranchLevelList   &Tree::getBranchLevelList() {
        return _branchLevelList;
    }
}