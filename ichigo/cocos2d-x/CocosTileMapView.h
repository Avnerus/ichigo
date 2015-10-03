#ifndef __ICHIGO_COCOSTILEMAPVIEW_H__
#define __ICHIGO_COCOSTILEMAPVIEW_H__

#include "TileMapView.h"

#include "cocos2d.h"
using namespace cocos2d;


namespace ichigo
{
    class CocosTileMapView : public TileMapView
    {
    public:
        
        CocosTileMapView(Agent *agent);
        virtual ~CocosTileMapView();
        
        virtual void            setPosition(const Point &pos);
        virtual void            setScale(float scale);
        virtual void            setAngle(float angle);
        virtual void            setZOrder(int zOrder);
        virtual void            setPivot(const Point &pivot);
        virtual void            setVisible(bool isVisible);
        
        virtual Point           convertLocalToScreen(const Point &localPos);
        virtual Point           convertScreenToLocal(const Point &screenPos);
        
        virtual void            addChild(ActorView *child);
        virtual void            removeChild(ActorView *child);
        
        virtual void            setTile(int x, int y, Tile *tile);
        virtual void            loadFramesFromAtlas(std::string atlasFile);
        virtual Tile           *createTile(std::string tileID);
        
        virtual void           *getInternalData();
        
    protected:
        
        void                    createTileMapNode();
        
        CCNode                 *_node;
        CCNode                 *_tileRoot;
        CCNode                 *_childrenRoot;
        //CCPoint                 _pivot;
    };
}


#endif // __ICHIGO_COCOSTILEMAPVIEW_H__
