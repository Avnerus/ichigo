#include "Rect.h"


namespace ichigo 
{
    Rect::Rect(float minPointX, float minPointY, float maxPointX, float maxPointY ) {
        minX = minPointX;
        minY = minPointY;
        maxX = maxPointX;
        maxY = maxPointY;
    }
    
    Rect::~Rect() {
    }

}