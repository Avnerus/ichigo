#ifndef __ICHIGO_UTILS_H__
#define __ICHIGO_UTILS_H__

#include "Point.h"
#include <string>


#define PI 3.14159265


namespace ichigo
{
    class TouchPoint;
    class Actor;
    
    
    class Utils
    {
    public:
        
        static void         calcMultitouchTransform(Point *anchorPos, TouchPoint *touchPos, float *outScale, float *outRotation);
        static bool         areActorsColliding(Actor *actor1, Actor *actor2);
        
        static float        rad2deg(float angleInRadians);
        static float        deg2rad(float angleInDegrees);
        
        static void         seedRand();
        static float        randf(float max);
        static int          randi(int max);
        
        static std::string  intToZeroPaddedString(int num, int digits);
    };
}


#endif // __ICHIGO_UTILS_H__
