#ifndef __ICHIGO_DATAMANAGER_H__
#define __ICHIGO_DATAMANAGER_H__

#include "json/json.h"
#include "Color.h"
#include "Point.h"
#include <string>
#include <map>


#define CONST_INT(a)    (ichigo::DataManager::getInstance()->getConstInt(a))
#define CONST_FLOAT(a)  (ichigo::DataManager::getInstance()->getConstFloat(a))
#define CONST_BOOL(a)   (ichigo::DataManager::getInstance()->getConstBool(a))
#define CONST_POINT(a)  (ichigo::DataManager::getInstance()->getConstPoint(a))
#define CONST_COLOR(a)  (ichigo::DataManager::getInstance()->getConstColor(a))
#define CONST_STRING(a) (ichigo::DataManager::getInstance()->getConstString(a))


namespace ichigo {
    
    class DataManager {
    
    public:

        DataManager();
        ~DataManager();
        
        static DataManager*     getInstance();
        bool                    init();
        Json::Value             loadFromJSON(std::string fileName);
        std::string             readFile(const char *path);
        
        static std::string      getString(const Json::Value &value, const char *name, const std::string &defaultVal = "");
        static int              getInt(const Json::Value &value, const char *name, int defaultVal = 0);
        static float            getFloat(const Json::Value &value, const char *name, float defaultVal = 0);
        static bool             getBool(const Json::Value &value, const char *name, bool defaultVal = false);
        static Point            getPoint(const Json::Value &value, const char *name, const Point &defaultVal = Point(0, 0));
        static Color            getColor(const Json::Value &value, const char *name, const Color &defaultVal = Color(0, 0, 0, 255));
        
        void                    loadConstFile(std::string filename);
        int                     getConstInt(const std::string &constName);
        float                   getConstFloat(const std::string &constName);
        bool                    getConstBool(const std::string &constName);
        Point                   getConstPoint(const std::string &constName);
        Color                   getConstColor(const std::string &constName);
        std::string             getConstString(const std::string &constName);
        
    protected:
        
        static bool             isFloat(const Json::Value &value);
        
        std::map<std::string, int>          _constInts;
        std::map<std::string, float>        _constFloats;
        std::map<std::string, bool>         _constBools;
        std::map<std::string, Point>        _constPoints;
        std::map<std::string, Color>        _constColors;
        std::map<std::string, std::string>  _constStrings;
    };    
}



#endif // __ICHIGO_DATAMANAGER_H__