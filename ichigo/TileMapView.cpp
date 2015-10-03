#include "TileMapView.h"
#include "DataManager.h"


namespace ichigo
{
    TileMapView::TileMapView(Agent *agent)
    : ActorView(agent)
    {
        _type = "TileMapView";
        
        _tileRows = 0;
        _tileCols = 0;
        _tileWidth = 0;
        _tileHeight = 0;
    }
    
    
    TileMapView::~TileMapView()
    {
    }
    
    
    // Config the tilemap from a Json data structure
    void TileMapView::deserialize(Json::Value &configData)
    {        
        if (configData.isMember("loadAtlas"))
        {
            loadFramesFromAtlas(DataManager::getString(configData, "loadAtlas"));
        }
        
        setTilesTexture (DataManager::getString(configData, "tilesTexture", getTilesTexture()));
        setTilesName    (DataManager::getString(configData, "tilesName",    getTilesName()));
        setTilesExt     (DataManager::getString(configData, "tilesExt",     getTilesExt()));
        
        // Go over each tile in the map, create the appropriate Tile and add to the TileMap at the correct position
        bool firstTileCreated = false;
        int tileRows = 0;
        int tileCols = 0;
        Json::Value &tilemap = configData["tilesMap"];
        if (!tilemap.isNull() && tilemap.isArray() && tilemap.size() > 0)
        {
            tileRows = tilemap.size();
            for (int i = 0; i < tileRows; i++)
            {
                Json::Value &tilerow = tilemap[i];
                if (!tilerow.isNull() && tilerow.isArray() && tilerow.size() > 0)
                {
                    tileCols = tilerow.size();
                    for (int j = 0; j < tileCols; j++)
                    {
                        Tile *tile = createTile(tilerow[j].asString());
                        
                        // There are some things the tilemap should learn about itself, and it gets the information from the first tile
                        // it creates (like the spacing between tiles)
                        if (!firstTileCreated)
                        {
                            setTileMapSize(tileCols, tileRows);
                            setTileSize(tile->getSize().x, tile->getSize().y);
                            firstTileCreated = true;
                        }
                        
                        // Add tile to the map
                        setTile(j, (tileRows - 1) - i, tile);
                    }
                }
            }
        }

        ActorView::deserialize(configData);
    }
    
    
    // Adds a Tile to the requested position in the map. Notice Y=0 is the bottom of the map
    void TileMapView::setTile(int x, int y, ichigo::Tile *tile)
    {
        _tiles[x][y] = std::tr1::shared_ptr<Tile>(tile);
        tile->setPosition(x * (_tileWidth - 1), y * (_tileHeight - 1));
    }
    
    
    // Returns the Tile at map position x,y
    Tile *TileMapView::getTile(int x, int y)
    {
        Tile *retVal = NULL;
        
        if (x >= 0 &&x < _tileCols && y >= 0 && y < _tileRows)
        {
            retVal = _tiles[x][y].get();
        }
        
        return retVal;
    }
    
    
    // Returns the Tile occupying the area where position x,y (local coordiantes) is.
    // If offsetInTile is provided, on return it will hold the offset in tile coordinates of x,y
    Tile *TileMapView::getTileAtPosition(float x, float y, ichigo::Point *offsetInTile)
    {
        int mapX = getTileCol(x);
        int mapY = getTileRow(y);
        
        // Get offset?
        if (offsetInTile)
        {
            offsetInTile->x = x - (mapX * _tileWidth);
            offsetInTile->y = y - (mapY * _tileHeight);
        }
        
        return getTile(mapX, mapY);
    }
    
    
    // Returns the column of the tile a x position
    int TileMapView::getTileCol(float x)
    {
        return x / _tileWidth + 0.5f;
    }
    
    
    // Returns the row of the tile a y position
    int TileMapView::getTileRow(float y)
    {
        return y / _tileHeight + 0.5f;
    }
    
    
    // Sets the widht and height (in tiles) of the tile map
    void TileMapView::setTileMapSize(int cols, int rows)
    {
        _tileCols = cols;
        _tileRows = rows;
    }
    
    
    // Returns the number of tiles in each row in the tile map
    int TileMapView::getTileRows()
    {
        return _tileRows;
    }
    
    
    // Returns the number of tiles in each column of the tile map
    int TileMapView::getTileColumns()
    {
        return _tileCols;
    }
    
    
    // Sets the size of one tile
    void TileMapView::setTileSize(float width, float height)
    {
        _tileWidth = width;
        _tileHeight = height;
    }
    
    
    // Returns the width of one tile
    float TileMapView::getTileWidth()
    {
        return _tileWidth;
    }
    
    
    // Returns the height of one tile
    float TileMapView::getTileHeight()
    {
        return _tileHeight;
    }
    
    
    // Sets the texture file from which all tile frames are loaded. If this is set, it can be used for efficient rendering of all
    // tiles with one render call (though this depends on the implementation)
    void TileMapView::setTilesTexture(std::string filename)
    {
        _tilesTextureFile = filename;
    }
    
    
    // Returns the filename of the texture used for all tile frames
    const std::string &TileMapView::getTilesTexture()
    {
        return _tilesTextureFile;
    }
    
    
    // Sets the name of the tile frame. Together with the tileID and tile extension, we can get the texture of the tile
    void TileMapView::setTilesName(std::string name)
    {
        _tilesName = name;
    }
    
    
    // Returns the name-part of the tiles' texture
    const std::string &TileMapView::getTilesName()
    {
        return _tilesName;
    }
    
    
    // Sets the extension used when loading a tile's frame texture
    void TileMapView::setTilesExt(std::string ext)
    {
        _tilesExt = ext;
    }
    
    
    // Returns the file extension used when loading a tile's frame texture
    const std::string &TileMapView::getTilesExt()
    {
        return _tilesExt;
    }
    
    
    // Returns true if a point on the screen lies within the bounds of the tile map. For what we need, it is enough to return 
    // true always
    bool TileMapView::isScreenPointInside(const ichigo::Point &screenPos)
    {
        return true;
    }
    
        
    Rect TileMapView::getBoundingBox() {
        Rect box =  Rect(
            -_tileWidth / 2.0f, 
            -_tileHeight / 2.0f, 
            (_tileWidth - 1.0f) * ((float)_tileCols - 0.5f),
            _tileHeight * ((float)_tileRows - 0.5f)
        );
        std::cout << "TileMapView::getBoundingBox() returning " << box << std::endl;    
        return box;
    }
}
