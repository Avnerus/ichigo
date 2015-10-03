#include "Point.h"
#include <cmath>


namespace ichigo 
{
    Point::Point(float pointX /* = 0 */, float pointY /* = 0 */)
    {
        x = pointX;
        y = pointY;
    }
    
    
    Point::Point(const Point &srcPoint)
    {
        x = srcPoint.x;
        y = srcPoint.y;
    }
    
    
    Point::~Point()
    {
    }
    
    
    // Find the distance from this point to another point
    float Point::distanceTo(const ichigo::Point &otherPoint) const
    {
        float xLength = x - otherPoint.x;
        float yLength = y - otherPoint.y;
        
        return sqrtf((xLength * xLength) + (yLength * yLength));
    }
    
    
    // Treat this point as a vector, and normalize it
    void Point::normalize()
    {
        float vectorLength = Point(0, 0).distanceTo(*this);
        x /= vectorLength;
        y /= vectorLength;
    }
}