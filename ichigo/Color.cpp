#include "Color.h"


namespace ichigo
{
    Color::Color(byte red /* = 0 */, byte green /* = 0 */, byte blue /* = 0 */, byte alpha /* = 255 */)
    {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }
    
    
    Color::Color(const Color &srcColor)
    {
        r = srcColor.r;
        g = srcColor.g;
        b = srcColor.b;
        a = srcColor.a;
    }
    
    
    Color::~Color()
    {
    }
    
    
    // Assignment operator
    Color &Color::operator=(const ichigo::Color &srcColor)
    {
        r = srcColor.r;
        g = srcColor.g;
        b = srcColor.b;
        a = srcColor.a;
        
        return *this;
    }
}
