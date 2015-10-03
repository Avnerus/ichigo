#include "Utils.h"
#include "TouchPoint.h"
#include "Actor.h"
#include "ActorView.h"

#include <cmath>
#include <time.h>
#include <iomanip>
#include <sstream>

namespace ichigo
{
    // Utility function to calculate the scale and rotation two touch points. The first one is static and the second one moving
    // If one of the out parameters is NULL, it will be disregarded
    void Utils::calcMultitouchTransform(ichigo::Point *anchorPos, ichigo::TouchPoint *touchPos, float *outScale, float *outRotation)
    {
        Point preMoveTP = touchPos->getPrevPos();
        Point postMoveTP = touchPos->getPos();
        
        // Calculate how much the distance has changed for the scale
        if (outScale)
        {
            float distanceBefore = anchorPos->distanceTo(preMoveTP);
            float distanceAfter = anchorPos->distanceTo(postMoveTP);
            
            if (distanceBefore != 0)
            {
                *outScale = distanceAfter / distanceBefore;
            }
            else
            {
                *outScale = 0;
            }
        }
        
        // Calculate how much the angle between both points has changed to get the rotation
        if (outRotation)
        {
            Point angleBefore = preMoveTP - *anchorPos;
            Point angleAfter = postMoveTP - *anchorPos;
            angleBefore.normalize();
            angleAfter.normalize();
            
            float angleInRadians = atan2f(angleAfter.y, angleAfter.x) - atan2f(angleBefore.y, angleBefore.x);
            *outRotation = -rad2deg(angleInRadians);
        }
    }
    
    
    // Returns true if the bounding spheres of both actor views are colliding
    bool Utils::areActorsColliding(ichigo::Actor *actor1, ichigo::Actor *actor2)
    {
        bool retVal = false;
        
        if (actor1 && actor2)
        {
            ActorView *view1 = (ActorView *)actor1->getView();
            ActorView *view2 = (ActorView *)actor2->getView();
            
            if (view1 && view2)
            {
                float distance = view1->getPositionOnScreen().distanceTo(view2->getPositionOnScreen());
                if (distance <= view1->getRadius() * view1->getWorldScale() + view2->getRadius() * view2->getWorldScale())
                {
                    retVal = true;
                }
            }
        }
        
        return retVal;
    }
    
    
    // Converts an angle in radians to degrees
    float Utils::rad2deg(float angleInRadians)
    {
        return angleInRadians * 180.0f / PI;
    }
    
    
    // Converts an angle in degrees to radians
    float Utils::deg2rad(float angleInDegrees)
    {
        return angleInDegrees * PI / 180.0f;
    }
    
    
    // Seed the random generator
    void Utils::seedRand()
    {
        srand(time(NULL));
    }
    
    
    // Returns a random float between 0 and max
    float Utils::randf(float max)
    {
        return ((float)rand() / (float)RAND_MAX) * max;
    }
    
    // Returns a random int between 0 and max
    int Utils::randi(int max)
    {
        return (rand() % max);
    }
    
    
    // Converts NUM into a string. If num has less digits than DIGITS, it will be zero padded
    std::string Utils::intToZeroPaddedString(int num, int digits)
    {
        std::ostringstream retVal;
        retVal << std::setw(digits) << std::setfill('0') << num;
        return retVal.str();
    }
}
