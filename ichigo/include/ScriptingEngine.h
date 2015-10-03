#ifndef __ICHIGO_SCRIPTINGENGINE_H__
#define __ICHIGO_SCRIPTINGENGINE_H__

namespace ichigo {
    class ScriptingEngine {
    public:
        
        virtual bool executeScriptFile(std::string fileName) = 0;
        virtual int executeFunction(std::string funcName) = 0;
        virtual void init() = 0;
        
    protected:
        
    };
}


#endif  // __ICHIGO_SCRIPTINGENGINE_H__
