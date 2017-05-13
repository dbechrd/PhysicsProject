#include "Force.h"
#include "SDL/SDL.h"

//Constructor sets data
Force::Force( float nmagnitude, float nangle, int nduration )
{
    magnitude = nmagnitude;
    angle = nangle;

    initTime = SDL_GetTicks();
    duration = nduration;
}

//Retrieve Magnitude
float Force::Magnitude()
{
    return magnitude;
}

//Retrieve Angle
float Force::Angle()
{
    return angle;
}

//Retrieve Init Time
int Force::InitTime()
{
    return initTime;
}

//Retrieve Duration
int Force::Duration()
{
    return duration;
}
