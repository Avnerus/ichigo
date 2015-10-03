#ifndef __ICHIGO_COCOSTILE_H__
#define __ICHIGO_COCOSTILE_H__

#include "Tile.h"

#include "cocos2d.h"
using namespace cocos2d;


namespace ichigo
{
    class CocosTile : public Tile
    {
    public:
        
        CocosTile(std::string name, std::string tileID, std::string extension);
        virtual ~CocosTile();
        
        virtual void            setID(std::string tileID);
        virtual Point           getSize();
        virtual void            setPosition(float x, float y);
        
        virtual CCSprite       *getCCSprite();
        
    protected:
        
        CCSpriteFrame          *loadSpriteFrame(std::string filename);
        
        CCSprite               *_sprite;
    };
}


#endif // __ICHIGO_COCOSTILE_H__
