#include "Exception.h"
#include <stdio.h>
#include <string.h>

namespace ichigo 
{
    Exception::Exception(const char* message) {
        strcpy (_message,message);
    }    
    
    const char* Exception::what() const throw() {
        return _message;
    }
}
