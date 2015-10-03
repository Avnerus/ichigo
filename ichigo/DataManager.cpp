#include "DataManager.h"
#include "stdio.h"
#include "cocos2d.h"

#include <iostream>

namespace ichigo {
        
    static ichigo::DataManager s_dataManager;
    static bool s_bFirstRun = true;
    
    
    DataManager::DataManager() {
    }
    
    
    DataManager::~DataManager() {
    }
    
    
    // Returns the singleton instance, creates it if needed
    DataManager* DataManager::getInstance()
    {
    	if (s_bFirstRun)
    	{
    		s_dataManager.init();
            s_bFirstRun = false;
    	}

    	return &s_dataManager;
    }
    
    
    // DataManager initializer
    bool DataManager::init() {
        std::cout << "DataManagerr Initializing" << std::endl;        
		
		return true;
    }
    
    
    // Loads a JSON file and returns it in Value form
    Json::Value DataManager::loadFromJSON(std::string fileName) {
        Json::Value root;
        Json::Reader reader;
        std::string data = readFile(fileName.c_str());
        bool parsingSuccessful = reader.parse(data, root );
        
        if ( !parsingSuccessful ) {
            // report to the user the failure and their locations in the document.
            std::cout  << "Failed to parse file\n" << fileName
                       << reader.getFormattedErrorMessages();
            return NULL;
        }
        return root;            
    }
    
    
    // Reads a text file. 
    // TODO: Remove the call to cocos utility function
    std::string DataManager::readFile(const char *path) {
        
        // Open file for input
        FILE *file = fopen( cocos2d::CCFileUtils::fullPathFromRelativePath(path), "rb" );
        if ( !file ) {
            return std::string("");
        }
        
        // Find file size
        fseek( file, 0, SEEK_END );
        long size = ftell( file );
        fseek( file, 0, SEEK_SET );
        
        // Create buffer and fill it with file contents
        std::string text;
        char *buffer = new char[size+1];
        buffer[size] = 0;
        if ( fread( buffer, 1, size, file ) == (unsigned long)size ) {
            text = buffer;
        }
        
        // Cleanup
        fclose( file );
        delete[] buffer;
        return text;
    }

    
    // Static method to return the string value from a JSON::Value. If the value doesn't exist or is of the wrong type,
    // defaultVal is returned
    std::string DataManager::getString(const Json::Value &value, const char *name, const std::string &defaultVal /* = "" */)
    {
        if (!value || !value.isMember(name) || !value[name].isString())
        {
            return defaultVal;
        }
        
        return value[name].asString();
    }
    
    
    // Static method to return an int value from a JSON::Value. If the value doesn't exist or is of the wrong type,
    // defaultVal is returned
    int DataManager::getInt(const Json::Value &value, const char *name, int defaultVal /* = 0 */)
    {
        if (!value || !value.isMember(name) || !value[name].isInt())
        {
            return defaultVal;
        }
        
        return value[name].asInt();
    }
    
    
    // Static method to return a float value from a JSON::Value. If the value doesn't exist or is of the wrong type,
    // defaultVal is returned
    float DataManager::getFloat(const Json::Value &value, const char *name, float defaultVal /* = 0 */)
    {
        if (!value || !value.isMember(name) || !isFloat(value[name]))
        {
            return defaultVal;
        }
        
        return value[name].asFloat();
    }
    
    
    // Static method to return a boolean value from a JSON::Value. If the value doesn't exist or is of the wrong type,
    // defaultVal is returned
    bool DataManager::getBool(const Json::Value &value, const char *name, bool defaultVal /* = false */)
    {
        if (!value || !value.isMember(name) || !value[name].isBool())
        {
            return defaultVal;
        }
        
        return value[name].asBool();
    }
    
    
    // Static method to return a point value from a JSON::Value. If the value doesn't exist or is of the wrong type,
    // defaultVal is returned
    Point DataManager::getPoint(const Json::Value &value, const char *name, const Point &defaultVal /* = (0, 0) */)
    {
        if (!value || !value.isMember(name) || !value[name].isArray() || 
            value[name].size() != 2 || !isFloat(value[name][0]) || !isFloat(value[name][1]))
        {
            return defaultVal;
        }
        
        return Point(value[name][0].asFloat(), value[name][1].asFloat());
    }
    
    
    // Static method to return a color value from a JSON::Value. If the value doesn't exist or is of the wrong type,
    // defaultVal is returned
    Color DataManager::getColor(const Json::Value &value, const char *name, const Color &defaultVal /* = (0, 0, 0, 255) */)
    {
        // Allow color to have 3 or 4 parameters. If 3, alpha is 255
        if (!value || !value.isMember(name) || !value[name].isArray() || value[name].size() < 3 || value[name].size() > 4 ||
            !value[name][0].isInt() || !value[name][1].isInt() || !value[name][2].isInt() || 
            (value[name].size() == 4 && !value[name][3].isInt()))
        {
            return defaultVal;
        }
        
        Color retVal(value[name][0].asInt(), value[name][1].asInt(), value[name][2].asInt());
        if (value[name].size() == 4)
        {
            retVal.a = value[name][3].asInt();
        }
        return retVal;
    }
    
    
    // Checks if a Json value is a float
    bool DataManager::isFloat(const Json::Value &value)
    {
        return value.isDouble() || value.isInt();
    }
    
    
    // Loads a JSON file with const values into maps for quick rerieval
    void DataManager::loadConstFile(std::string filename)
    {
        Json::Value constFile = loadFromJSON(filename);
        if (!constFile.isNull() && constFile.isMember("config"))
        {
            // Go over each child and add the const to the correct map
            for (int i = 0; i < constFile["config"].size(); i++)
            {
                Json::Value &currConst = constFile["config"][i];
                std::string constType = getString(currConst, "type");
                
                if (constType == "int")
                {
                    _constInts[getString(currConst, "name")] = getInt(currConst, "value");
                }
                else if (constType == "float")
                {
                    _constFloats[getString(currConst, "name")] = getFloat(currConst, "value");
                }
                else if (constType == "bool")
                {
                    _constBools[getString(currConst, "name")] = getBool(currConst, "value");
                }
                else if (constType == "point")
                {
                    _constPoints[getString(currConst, "name")] = getPoint(currConst, "value");
                }
                else if (constType == "color")
                {
                    _constColors[getString(currConst, "name")] = getColor(currConst, "value");
                }
                else if (constType == "string")
                {
                    _constStrings[getString(currConst, "name")] = getString(currConst, "value");
                }
            }
        }
    }
    
    
    // Returns a constant from the int map. No verifying code because we want this method to be as fast as possible
    int DataManager::getConstInt(const std::string &constName)
    {
        return _constInts[constName];
    }
    
    
    // Returns a constant from the float map. No verifying code because we want this method to be as fast as possible
    float DataManager::getConstFloat(const std::string &constName)
    {
        return _constFloats[constName];
    }
    
    
    // Returns a constant from the bool map. No verifying code because we want this method to be as fast as possible
    bool DataManager::getConstBool(const std::string &constName)
    {
        return _constBools[constName];
    }
    
    
    // Returns a constant from the point map. No verifying code because we want this method to be as fast as possible
    Point DataManager::getConstPoint(const std::string &constName)
    {
        return _constPoints[constName];
    }
    
    
    // Returns a constant from the color map. No verifying code because we want this method to be as fast as possible
    Color DataManager::getConstColor(const std::string &constName)
    {
        return _constColors[constName];
    }
    
    
    // Returns a constant from the string map. No verifying code because we want this method to be as fast as possible
    std::string DataManager::getConstString(const std::string &constName)
    {
        return _constStrings[constName];
    }
}