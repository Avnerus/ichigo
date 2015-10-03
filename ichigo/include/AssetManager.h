#ifndef __ICHIGO_ASSETMANAGER_H__
#define __ICHIGO_ASSETMANAGER_H__

#include <tr1/memory>
#include <tr1/unordered_map>

#include "cocos2d.h"

namespace ichigo {
    
    class AssetManager {
    
    protected:
        // std::tr1::unordered_map<std::string, std::tr1::shared_ptr<cocos2d::CCTexture2D> > _textures;
        
    public:
        static AssetManager* getInstance();
        bool init();
        cocos2d::CCTexture2D* getTexture(std::string name);
        void addTexture(std::string name);
        
        AssetManager();
        ~AssetManager();
    };    
}



#endif // __ICHIGO_ASSETMANAGER_H__