#ifndef __ICHIGO_AGENTFACTORY_H__
#define __ICHIGO_AGENTFACTORY_H__

#include "Agent.h"
#include <string>


namespace ichigo
{
    // Since this class has a static method, and it is impossible to inherit these, Ichigo contains only the interface.
    // Each game using Ichigo needs to implement AgentFactory, not by inheritence, just by implementing its CPP file.
    class AgentFactory
    {
    public:
        
        static Agent *createAgent(std::string type);
    };
}


#endif // __ICHIGO_AGENTFACTORY_H__
