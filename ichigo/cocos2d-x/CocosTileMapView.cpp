#include "CocosTileMapView.h"
#include "CocosTile.h"


namespace ichigo
{
    CocosTileMapView::CocosTileMapView(Agent *agent)
    :TileMapView(agent)
    {
        _node = NULL;
        _tileRoot = NULL;
         //_pivot = ccp(0, 0);
        
        _childrenRoot = NULL;
        _childrenRoot = CCNode::node();
    }
    
    
    CocosTileMapView::~CocosTileMapView()
    {
    }
    
    
    // Sets the translation of the tile map
    void CocosTileMapView::setPosition(const ichigo::Point &pos)
    {
        TileMapView::setPosition(pos);
        
        if (_node)
        {
            //CCPoint glPos(pos.x + _pivot.x, pos.y + _pivot.y);
            CCPoint glPos(pos.x, pos.y);
            _node->setPosition(glPos);
        }
    }
    
    
    // Scales the tile map
    void CocosTileMapView::setScale(float scale)
    {
        TileMapView::setScale(scale);
        
        if (_node)
        {
            _node->setScale(scale);
        }
    }
    
    
    // Rotates the tile map
    void CocosTileMapView::setAngle(float angle)
    {
        TileMapView::setAngle(angle);
        
        if (_node)
        {
            _node->setRotation(angle);
        }
    }
    
    
    // Sets the z-order of the tile map under its parent node
    void CocosTileMapView::setZOrder(int zOrder)
    {
        TileMapView::setZOrder(zOrder);
        
        if (_node && _parent)
        {
            _node->getParent()->reorderChild(_node, zOrder);
        }
    }
    
    
    // Sets the pivot of the tile map. 
    void CocosTileMapView::setPivot(const ichigo::Point &pivot)
    {
        if (_node)
        {
            // For now results are satisfactory, so leave it at this. If it ever needs repairs this method has two strategies commented
            // out. One where th root is a sprite and pivot is altered like any other sprite, and one where the root is a node and is
            // moved to pivot position (while its children move the oposite direction to stay at the same location)
            
            /*_pivot.x = pivot.x;
            _pivot.y = pivot.y;
            _node->setPosition(ccp(_node->getPosition().x + pivot.x, _node->getPosition().y + pivot.y));
            _tileRoot->setPosition(ccp(-pivot.x, -pivot.y));
            _childrenRoot->setPosition(ccp(-pivot.x, -pivot.y));*/
            
            /*CCPoint normalizedPivot;
            normalizedPivot.x = (pivot.x / _node->boundingBox().size.width) / 2.0f + 0.5f;
            normalizedPivot.y = (pivot.y / _node->boundingBox().size.height) / 2.0f + 0.5f;
            _node->setAnchorPoint(normalizedPivot);*/
            
            //std::cout << "setPivot [" << pivot.x << "," << pivot.y << "] to [" << normalizedPivot.x << "," << normalizedPivot.y << "]" << std::endl;
        }
    }
    
    
    // Shows or hides the tile map
    void CocosTileMapView::setVisible(bool isVisible)
    {
        TileMapView::setVisible(isVisible);
        
        if (_node)
        {
            _node->setIsVisible(isVisible);
        }
    }
    
    
    // Returns the screen position of point in tile map's local coordinate system
    Point CocosTileMapView::convertLocalToScreen(const ichigo::Point &localPos)
    {
        Point retVal;
        
        if (_node)
        {
            CCPoint worldPos = _node->convertToWorldSpace(ccp(localPos.x, localPos.y));
            
            retVal.x = worldPos.x;
            retVal.y = worldPos.y;
        }
        
        return retVal;        
    }
    
    
    // Converts a point in screen coordinates to local coordinates of this tile map
    Point CocosTileMapView::convertScreenToLocal(const ichigo::Point &screenPos)
    {
        Point retVal;
        
        if (_node)
        {
            CCPoint localPos = _node->convertToNodeSpace(ccp(screenPos.x, screenPos.y));
            
            retVal.x = localPos.x;
            retVal.y = localPos.y;
        }
        
        return retVal;
    }
    
    
    // Adds a view as a child to this node
    void CocosTileMapView::addChild(ichigo::ActorView *child)
    {
        // Children can't be added to the tile map because it might be a CCSpriteBatchNode and force a texture, so we have a special
        // node for the children
        if (_childrenRoot)
        {
            _childrenRoot->addChild((CCNode *)child->getInternalData(), child->getZOrder());
            child->setParent(this);
        }
    }
    
    
    // Removes a child from the tile map node
    void CocosTileMapView::removeChild(ichigo::ActorView *child)
    {
        if (_node && _childrenRoot)
        {
            _childrenRoot->removeChild((CCNode *)child->getInternalData(), false);
            child->setParent(NULL);
        }
    }
    
    
    // Sets a tile texture by adding its sprite to the tile map node
    void CocosTileMapView::setTile(int x, int y, ichigo::Tile *tile)
    {
        // First time we have a tile, create the tile map node (it's done here to make sure tilemap texture has been given in order to
        // decide correctly whether to create a CCNode or a CCSpriteBatchNode)
        if (!_node || !_tileRoot)
        {
            createTileMapNode();
        }
        
        if (_node && _tileRoot)
        {
            // If this sprite hasn't been added yet, add it as a child to the node
            CCSprite *tileSprite = ((CocosTile *)tile)->getCCSprite();
            if (_tiles.find(x) == _tiles.end() || _tiles[x].find(y) == _tiles[x].end())
            {
                _tileRoot->addChild(tileSprite);
            }
        }
        
        // Parent will actually add the tile to the tile matrix and position the sprite
        TileMapView::setTile(x, y, tile);
    }
    
    
    // Loads all tile frames from a sprite atlas into cache
    void CocosTileMapView::loadFramesFromAtlas(std::string atlasFile)
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(atlasFile.c_str());
    }
    
    
    // Template method to create a new tile using cocos implementation
    Tile *CocosTileMapView::createTile(std::string tileID)
    {
        return new CocosTile(_tilesName, tileID, _tilesExt);
    }
    
    
    // Returns the Cocos data of this node
    void *CocosTileMapView::getInternalData()
    {
        return _node;
    }
    
    
    // Initializes the cocos node
    void CocosTileMapView::createTileMapNode()
    {
        // Root node for whole tile map structure.
        _node = CCNode::node();
        
        // Tile root is the root of all tiles. It will have no other children
        if (_tilesTextureFile == "")
        {
            // If no texture name was given, create a regular node
            _tileRoot = CCNode::node();
        }
        else
        {
            // A texture name was given, so we assume all tiles will be using frames from the same texture. We can thus create a much
            // more efficient node which will render all tiles in one render call
            _tileRoot = CCSpriteBatchNode::batchNodeWithFile(_tilesTextureFile.c_str());
        }
        _node->addChild(_tileRoot, 0);
        
        // Children root holds all the childen in the scne group. Notice their z-order is higher than the tile map
        _node->addChild(_childrenRoot, 1);
    }
}
