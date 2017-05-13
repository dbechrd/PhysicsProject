#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "Vertex.h"
#include "Force.h"

#include <vector>

using namespace std;

class Object{

    private:

        //Location
        float x;
        float y;

        //Store Points
        vector<Vertex*> vertices;
        vector<Vertex*>::iterator verticesIter;

        //Velocity
        float xVel;
        float yVel;

        //Acceleration
        float xAccel;
        float yAccel;

        //Physical Properties
        float mass;
        float elast;

        //Friction
        float air;                                  //air resistance
        float fS;                                   //static
        float fK;                                   //kinetic

        //Forces
        vector<Force*> fApp;                   //applied
        vector<Force*>::iterator fAppIter;     //applied iterator

        //Temporary storage of forces to delete
        vector< vector<Force*>::iterator > deadForces;
        vector< vector<Force*>::iterator >::iterator deadForcesIter;

        //Time
        float oldTime;

        //Temp collision test
        //bool collision;
        bool xcol;
        bool ycol;

    public:

        Object( float nx, float ny, float nmass, float nfS, float nfK );
        ~Object();
        void AddVertex( float nx, float ny, float nr, float ng, float nb );
        void AddForce( float nmagnitude, float nangle, int nduration );
        void SetCoords( int mousex, int mousey );
        bool CheckCollision( int xcheck, int ycheck );
        bool Update( bool buttonpressed );
        void Render();

};

#endif // OBJECT_H_INCLUDED
