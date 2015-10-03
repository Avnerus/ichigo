#ifndef __ICHIGO_POINT_H__
#define __ICHIGO_POINT_H__

#include <iostream>

namespace ichigo 
{
    class Point
    {
    public:
        Point(float pointX = 0, float pointY = 0);
        Point(const Point &srcPoint);
        ~Point();
        
        float           distanceTo(const Point &otherPoint) const;
        void            normalize();
        
        Point          &operator=(const Point &inPoint);
        Point          &operator+=(const Point &inPoint);
        Point          &operator-=(const Point &inPoint);
        Point          &operator*=(float factor);
        Point          &operator/=(float factor);
        const Point     operator+(const Point &inPoint) const;
        const Point     operator-(const Point &inPoint) const;
        const Point     operator*(const float factor) const;
        const Point     operator/(const float factor) const;
        bool            operator==(const Point &inPoint) const;
        bool            operator!=(const Point &inPoint) const;
        friend std::ostream  &operator<<(std::ostream &out, const Point &inPoint);
        
        float x;
        float y;
    };
    
    
    inline Point &Point::operator=(const ichigo::Point &inPoint)
    {
        if (this != &inPoint)
        {
            x = inPoint.x;
            y = inPoint.y;
        }
        
        return *this;
    }
    
    
    inline Point &Point::operator+=(const Point &inPoint)
    {
        x += inPoint.x;
        y += inPoint.y;
        
        return *this;
    }
    
    
    inline Point &Point::operator-=(const Point &inPoint)
    {
        x -= inPoint.x;
        y -= inPoint.y;
        
        return *this;
    }
    
    
    inline Point &Point::operator*=(float factor)
    {
        x *= factor;
        y *= factor;
        
        return *this;
    }
    
    
    inline Point &Point::operator/=(float factor)
    {
        x /= factor;
        y /= factor;
        
        return *this;
    }
    
    
    inline const Point Point::operator+(const Point &inPoint) const
    {
        Point retVal(*this);
        retVal += inPoint;
        
        return retVal;
    }
    
    
    inline const Point Point::operator-(const Point &inPoint) const
    {
        Point retVal(*this);
        retVal -= inPoint;
        
        return retVal;
    }
    
    
    inline const Point Point::operator*(const float factor) const
    {
        Point retVal(*this);
        retVal *= factor;
        
        return retVal;
    }
    
    
    inline const Point Point::operator/(const float factor) const
    {
        Point retVal(*this);
        retVal /= factor;
        
        return retVal;
    }
    
    
    inline bool Point::operator==(const Point &inPoint) const
    {
        return (x == inPoint.x && y == inPoint.y);
    }
    
    
    inline bool Point::operator!=(const Point &inPoint) const
    {
        return !(*this == inPoint);
    }
    
    inline std::ostream &operator<<( std::ostream &out, const Point &inPoint ) {
        out << "(" << inPoint.x << "," << inPoint.y << ")";
        return out;
    }
}

#endif  // __ICHIGO_POINT_H__
