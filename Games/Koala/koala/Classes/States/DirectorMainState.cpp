#include "DirectorMainState.h"
#include "ichigo.h"


namespace koala
{    
    DirectorMainState::DirectorMainState() 
    {
        // My event table        
        
        _name = "Main";
    }
    
    
    DirectorMainState::~DirectorMainState() 
    {
        std::cout << "DirectorMainState destroyed" << std::endl;
    }
    
    
    void DirectorMainState::onUpdate(float dt) 
    {    
        
    }
    
    
    void DirectorMainState::onEnter() 
    {
        std::cout << "DirectorMainState onEnter" << endl;
        
        _dreamKoala = (DreamKoala *)(_agent->findByName("dreamKoala"));
        _dreamKoala->loadScript();
                
        // _dreamKoala->say("Am I dreaming..?");
        

    }
    
    
    void DirectorMainState::onExit() 
    {
        std::cout << "DirectorMainState onExit" << endl;    
    }
    
    
}