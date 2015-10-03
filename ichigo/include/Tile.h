#ifndef __ICHIGO_TILE_H__
#define __ICHIGO_TILE_H__

#include "Point.h"
#include <string>


namespace ichigo
{
    class Tile 
    {
    public:

        Tile(std::string name, std::string tileID, std::string extension);
        virtual ~Tile();
        
        virtual void                setID(std::string tileID);
        virtual const std::string  &getID();
        
        virtual Point               getSize() = 0;
        virtual void                setPosition(float x, float y);
        virtual const Point        &getPosition();
        
    protected:
        
        Point               _pos;
        std::string         _tileName;
        std::string         _tileID;
        std::string         _tileExt;
    };
}


#endif // __ICHIGO_TILE_H__
