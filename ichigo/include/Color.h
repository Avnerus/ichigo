#ifndef __ICHIGO_COLOR_H__
#define __ICHIGO_COLOR_H__


typedef unsigned char byte;

#include <iostream>



namespace ichigo 
{
    class Color
    {
    public:
        Color(byte red = 0, byte green = 0, byte blue = 0, byte alpha = 255);
        Color(const Color &srcColor);
        ~Color();
        
        Color &operator=(const Color &srcColor);
        friend std::ostream  &operator<<(std::ostream &out, const Color &inColor);
        
        byte r;
        byte g;
        byte b;
        byte a;
    };
    
    inline std::ostream &operator<<( std::ostream &out, Color &inColor ) {
        out << "(" << (int)inColor.r << "," << (int)inColor.g << "," << (int)inColor.b << "," << (int)inColor.a << ")";
        return out;
    }
}

#endif  // __ICHIGO_COLOR_H__
