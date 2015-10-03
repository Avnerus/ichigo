#ifndef __ICHIGO_EXCEPTION_H__
#define __ICHIGO_EXCEPTION_H__

#include <exception>

namespace ichigo {
        
    class Exception : public std::exception {

    protected:
        char _message[80];
        
    public:
        Exception(const char* message);        
        
        virtual const char* what() const throw();
    };    
}



#endif // __ICHIGO_EXCEPTION_H__