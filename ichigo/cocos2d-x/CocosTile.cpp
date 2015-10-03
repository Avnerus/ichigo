#include "CocosTile.h"
#include "Point.h"


namespace ichigo
{
    CocosTile::CocosTile(std::string name, std::string tileID, std::string extension)
    :Tile(name, tileID, extension)
    {
        _sprite = NULL;
        _tileName = name;
        _tileExt = extension;
        
        setID(tileID);
    }
    
    
    CocosTile::~CocosTile()
    {
    }
    
    
    // Sets the tile's texture according to the given ID. If this is the first time the tile is set, also create the cocos sprite
    void CocosTile::setID(std::string tileID)
    {
        Tile::setID(tileID);
        
        // Load texture according to given ID
        CCSpriteFrame *frame = loadSpriteFrame(_tileName + "_" + tileID + "." + _tileExt);
        if (frame)
        {
            // Set texture to sprite
            if (_sprite)
            {
                _sprite->setTexture(frame->getTexture());
                _sprite->setTextureRect(frame->getRect());
            }
            else
            {
                // Sprite not created yet, create it using this texture
                _sprite = CCSprite::spriteWithSpriteFrame(frame);
            }
        }
    }
    
    
    // Returns the size of the tile's texture
    Point CocosTile::getSize()
    {
        Point retVal;
        
        if (_sprite)
        {
            retVal.x = _sprite->getContentSize().width;
            retVal.y = _sprite->getContentSize().height;
        }
        
        return retVal;
    }
    
    
    // Sets the position of the tile's sprite
    void CocosTile::setPosition(float x, float y)
    {
        Tile::setPosition(x, y);
        
        if (_sprite)
        {
            _sprite->setPosition(ccp(x, y));
        }
    }
    
    
    // Exposes the cocos sprite
    CCSprite *CocosTile::getCCSprite()
    {
        return _sprite;
    }
    
    
    // Loads a texture frame from a file
    CCSpriteFrame *CocosTile::loadSpriteFrame(std::string filename)
    {
        // First attempt to get it from the frame cache, in case it was already loaded from an atlas
        CCSpriteFrame *retVal = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename.c_str());
        
        // If not found, create the frame by loading texture
        if (!retVal)
        {
            CCTexture2D *frameTexture = CCTextureCache::sharedTextureCache()->addImage(filename.c_str());
            if (frameTexture)
            {
                retVal = CCSpriteFrame::frameWithTexture(frameTexture, 
                                                         CCRect(0, 0, frameTexture->getContentSize().width, frameTexture->getContentSize().height));
                
                // Add to frame cache
                CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(retVal, filename.c_str());
            }
        }
        
        return retVal;        
    }
}
