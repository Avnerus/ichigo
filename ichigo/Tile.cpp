#include "Tile.h"


namespace ichigo
{
    Tile::Tile(std::string name, std::string tileID, std::string extension)
    {
        _tileName = name;
        _tileID = tileID;
        _tileExt = extension;
    }
    
    
    Tile::~Tile()
    {
    }
    
    
    // Sets the ID of the frame. The ID is used with the tile name and extension to construct the sprite file
    void Tile::setID(std::string tileID)
    {
        _tileID = tileID;
    }
    
    
    // Returns the ID of the tile
    const std::string &Tile::getID()
    {
        return _tileID;
    }
    
    
    // Saves the position. A derived class should implement the actual sprite positioning
    void Tile::setPosition(float x, float y)
    {
        _pos.x = x;
        _pos.y = y;
    }
    
    
    // Returns the tile's position (in local tilemap coordinates)
    const Point &Tile::getPosition()
    {
        return _pos;
    }
}