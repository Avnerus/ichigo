#ifndef __ICHIGO_TILEMAPVIEW_H__
#define __ICHIGO_TILEMAPVIEW_H__

#include "ActorView.h"
#include "Tile.h"
#include <string>
#include <map>
#include <tr1/memory>


namespace ichigo
{
    typedef std::map< int, std::map< int, std::tr1::shared_ptr<Tile> > > TileMatrix;
    
    
    class TileMapView : public ActorView
    {
    public:
        
        TileMapView(Agent *agent);
        virtual ~TileMapView();
        
        virtual void                deserialize(Json::Value &configData);
        
        virtual void                setTile(int x, int y, Tile *tile);
        virtual Tile               *getTile(int x, int y);
        virtual Tile               *getTileAtPosition(float x, float y, Point *offsetInTile);
        virtual int                 getTileCol(float x);
        virtual int                 getTileRow(float y);
        
        virtual void                setTileMapSize(int cols, int rows);
        virtual int                 getTileRows();
        virtual int                 getTileColumns();
        virtual void                setTileSize(float width, float height);
        virtual float               getTileWidth();
        virtual float               getTileHeight();
        virtual void                setTilesTexture(std::string filename);
        virtual const std::string  &getTilesTexture();
        virtual void                setTilesName(std::string name);
        virtual const std::string  &getTilesName();
        virtual void                setTilesExt(std::string ext);
        virtual const std::string  &getTilesExt();
        virtual bool                isScreenPointInside(const Point &screenPos);
        
        virtual void                loadFramesFromAtlas(std::string atlasFile) = 0;
        virtual Tile               *createTile(std::string tileID) = 0;
        virtual Rect                getBoundingBox();
        
    protected:
        
        int                 _tileRows;
        int                 _tileCols;
        float               _tileWidth;
        float               _tileHeight;
        std::string         _tilesTextureFile;
        std::string         _tilesName;
        std::string         _tilesExt;
        
        TileMatrix          _tiles;
    };
}


#endif // __ICHIGO_TILEMAPVIEW_H__
