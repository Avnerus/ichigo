#ifndef __ICHIGO_RECT_H__
#define __ICHIGO_RECT_H__

#include <iostream>

namespace ichigo 
{
    class Rect
    {
    public:
        Rect(float minPointX, float minPointY, float maxPointX, float maxPointY );
        ~Rect();
        
        bool operator==(const Rect &inRect) const;
        friend std::ostream  &operator<<(std::ostream &out, const Rect &inRect);
        
        float minX;
        float minY;
        float maxX;
        float maxY;
    };
    
    inline bool Rect::operator==(const Rect &inRect) const {
        return (minX == inRect.minX && minY == inRect.minY && maxX == inRect.maxX && maxY ==inRect.maxY);
    }
    
    
    inline std::ostream &operator<<( std::ostream &out, Rect &inRect ) {
        out << "(" << (int)inRect.minX << "," << (int)inRect.minY << "," << (int)inRect.maxX << "," << (int)inRect.maxY << ")";
        return out;
    } 
    
}

#endif  // __ICHIGO_RECT_H__
