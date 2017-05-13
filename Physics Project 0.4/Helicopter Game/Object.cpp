#include "Object.h"
#include "Vertex.h"
#include "Force.h"
#include "Font.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL/SDL.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <sstream>
#include <string>

using namespace std;

//Constructor
Object::Object( float nx, float ny, float nmass )
{

    //Defaults
    x = nx;
    y = ny;

    xVel = 0.0;
    yVel = 0.0;

    accelx = 0.0;
    accely = 0.0;

    mass = nmass;
    elast = 0.0;

    //air = 0.005;
    air = 0.998;
    //air = 1.0;
    fS = 0.0;
    fK = 0.0;

    oldTime = float(SDL_GetTicks()) / 1000;

    vertices.clear();
    fApp.clear();


    /*FT_GlyphSlot  slot = face->glyph;  // a small shortcut
    FT_UInt       glyph_index;
    int           pen_x, pen_y, n;


    int error = FT_Init_FreeType( &library );
    if ( error )
    {
        cout << "Text Engine Error!" << endl << endl;
    }

    error = FT_New_Face( library,
                       "/resources/verdana.ttf",
                       0,
                       &face );
    if ( error == FT_Err_Unknown_File_Format )
    {
        cout << "the font file could be opened and read, but it appears that its font format is unsupported\n";
    }
    else if ( error )
    {
        cout << "another error code means that the font file could not be opened or read, or simply that it is broken\n";
    }
    //... set character size ...

    pen_x = 300;
    pen_y = 200;

    char text[8] = "testing";
    int num_chars = 7;

    for ( n = 0; n < num_chars; n++ )
    {
        // load glyph image into the slot (erase previous one)
        error = FT_Load_Char( face, text[n], FT_LOAD_RENDER );
        if ( error )
          continue;  // ignore errors

        // now, draw to our target surface
        //my_draw_bitmap( &slot->bitmap, pen_x + slot->bitmap_left, pen_y - slot->bitmap_top );

        // increment pen position
        pen_x += slot->advance.x >> 6;
    }*/
}

Object::~Object()
{
    vertices.clear();
    fApp.clear();
}

//Adds New Vertex
void Object::AddVertex( float nx, float ny, float nr, float ng, float nb )
{
    //cout << tempobj->X() << endl;
    //cout << tempobj->Y() << endl;
    //cout << tempobj->R() << endl;
    //cout << tempobj->G() << endl;
    //cout << tempobj->B() << endl;
    vertices.push_back( new Vertex( nx, ny, nr, ng, nb ) );
}

//Adds New Acting Force
void Object::AddForce( float nmagnitude, float nangle, int nduration )
{
    fApp.push_back( new Force( nmagnitude, nangle, nduration ) );
}

//Moves object
void Object::SetCoords( int mousex, int mousey )
{
    if( mousex < 320 && mousex >= 0 ){
        x = -1 * (1 - (float(mousex) / 320));
        //debug out cout << "BLARX: " << x << endl;
    }else if( mousex > 320 && mousex <= 640  ){
        x =  1 * (float(mousex - 320) / 320);
    //}else{
        //x = 0.0;
    }

    if( mousey < 240 && mousey >= 0  ){
        y =  1 * (1 - (float(mousey) / 240));
        //debug out cout << "BLARY: " << y << endl << endl;
    }else if( mousey > 240 && mousey <= 480  ){
        y = -1 * (float(mousey - 240) / 240);
    //}else{
        //y = 0.0;
    }
}

//Check collision between object and a given point
bool Object::CheckCollision( int xcheck, int ycheck )
{
    /*
    int N = vertices.size();
    int counter = 0;
    int i;
    double xinters;
    Vertex p1,p2;

    p1 = vertices[0];
    for( i = 1; i <= N; i++ )
    {
        p2 = vertices[i % N];
        if (p.Y() > MIN(p1.Y(),p2.Y()))
        {
            if (p.Y() <= MAX(p1.Y(),p2.Y()))
            {
                if (p.X() <= MAX(p1.X(),p2.X()))
                {
                    if (p1.Y() != p2.Y())
                    {
                        xinters = (ycheck-p1.Y())*(p2.X()-p1.X())/(p2.Y()-p1.Y()y)+p1.X();
                        if (p1.X() == p2.X() || xcheck <= xinters)
                        {
                            counter++;
                        }
                    }
                }
            }
            p1 = p2;
        }
    }

    if (counter % 2 == 0){
        return false;
    }else{
        return true;
    }
    */
}

//Iterates through all forces and calculates resultant x and y velocities,
//then updates the objects position accordingly
bool Object::Update( bool buttonpressed )
{
    bool retval = false;

    //If mass == 0 the object is anchored and does not need to be updated
    if( mass > 0 ){

        //Sum of acting forces
        float totalForcex = 0.0;
        //float totalForcey = 0.0;
        float totalForcey = 0.0;

        //Calculate time (in seconds) since last update
        float newTime = float(SDL_GetTicks()) / 1000;
        float deltaTime = newTime - oldTime;
        //debug out cout << "newTime: " << newTime << ", deltaTime: " << deltaTime << endl;

        //Dunno what these are for..
        //float oldxVel = xVel;
        //float oldyVel = yVel;

        //Store coords in case of collision
        float tempx = x;
        float tempy = y;

        //Create/Set Collision variables
        bool xcol = false;
        bool ycol = false;

        //Iterate through forces if there are any
        if( fApp.size() > 0 )
        {
            float magnitude = 0.0;
            float angle = 0.0;
            float radians = 0.0;
            int initTime = 0;
            int duration = 0;

            for( fAppIter = fApp.begin(); fAppIter != fApp.end(); fAppIter++ )
            {
                magnitude = (*fAppIter)->Magnitude();// * mass;
                angle = (*fAppIter)->Angle();
                radians = (angle * 3.14159265)/180;
                initTime = (*fAppIter)->InitTime();
                duration = (*fAppIter)->Duration();

                if( angle == 0 || angle == 360 ){
                    totalForcey += magnitude;
                }else if( angle == 90 ){
                    totalForcex += magnitude;
                }else if( angle == 180 ){
                    totalForcey -= magnitude;
                }else if( angle == 270 ){
                    totalForcex -= magnitude;
                }else if( angle > 0 && angle < 90 ){
                    totalForcex += ( sin(radians) * magnitude );
                    totalForcey += ( cos(radians) * magnitude );
                }else if( angle > 90 && angle < 180 ){
                    totalForcex += ( sin(radians) * magnitude );
                    totalForcey += ( cos(radians) * magnitude );
                }else if( angle > 180 && angle < 270 ){
                    totalForcex += ( sin(radians) * magnitude );
                    totalForcey += ( cos(radians) * magnitude );
                }else if( angle > 270 && angle < 360 ){
                    totalForcex += ( sin(radians) * magnitude );
                    totalForcey += ( cos(radians) * magnitude );
                }

                if( duration > 0 )
                {
                    if( (SDL_GetTicks() - initTime > duration) )
                    {
                        deadForces.push_back( fAppIter );
                    }
                }
            }
        }

        if( deadForces.size() > 0 )
        {
            for( deadForcesIter = deadForces.begin(); deadForcesIter != deadForces.end(); deadForcesIter++ )
            {
                fApp.erase( (*deadForcesIter) );
            }

            deadForces.clear();
        }

        if( !collision && (totalForcey != 0 || totalForcex != 0 || accelx != 0 || accely != 0) ){
            totalForcey += mass * -9.81;
        }else{
            if( collision ){
                retval = true;
            }
            x = 0;
            y = 0;
            xVel = 0;
            yVel = 0;
        }

        //Calculate frictional force
        //totalForcex += ( -1 * xVel / mass );
        //totalForcey += ( -1 * yVel / mass );
        //cout << "tFx" << totalForcex << " += ( -1 * " << xVel << " / mass );" << endl;
        //cout << "tFy" << totalForcey << " += ( -1 * " << yVel << " / mass );" << endl << endl;

        //Calculate horizontal acceleration after air resistance
        //if( xVel - air > 0 ){
        //    accelx = totalForcex / mass - air;
        //}else if( xVel + air < 0 ){
        //    accelx = totalForcex / mass + air;
        //}else{
            //xVel = 0;

        //float airResistancex = 0.96 * xVel;// * xVel;
        //float airResistancey = 0.96 * yVel;// * yVel;

            accelx = totalForcex / mass;// * deltaTime;
            //accelx += -1 * xVel / mass;
            //debug out cout << "accelx: " << accelx << " = " << deltaTime << " * " << totalForcex << " / " << mass << endl;

            //accelx = deltaTime * totalForcex / mass;
        //}

        //Calculate vertical acceleration after air resistance
        //if( yVel - air > 0 ){
        //    accely = totalForcey / mass - air;
        //}else if( yVel + air < 0 ){
        //    accely = totalForcey / mass + air;
        //}else{
            //yVel = 0;

            accely = totalForcey / mass;// * deltaTime;
            //accely += -1 * yVel / mass;
            //debug out cout << "accely: " << accely << " = " << deltaTime << " * " << totalForcey << " / " << mass << endl << endl;

            //accely = deltaTime * totalForcey / mass;
        //}

        //cout << "Accelx: " << accelx << endl;
        //cout << "Accely: " << accely << endl;

        //Update Velocities
        //xVel += accelx;
        xVel += accelx * deltaTime;
        //xVel += (accelx - airResistancex) * deltaTime;
        //yVel += accely;
        yVel += accely * deltaTime;
        //yVel += (accely - airResistancey) * deltaTime;

        //xVel = xVel * air;
        //yVel = yVel * air;

        /*if( xVel - air > 0 ){
            xVel = xVel - air;
        }else if( xVel + air < 0 ){
            xVel = xVel + air;
        }else{
            xVel = 0;
        }

        if( yVel - air > 0 ){
            yVel = yVel - air;
        }else if( yVel + air < 0 ){
            yVel = yVel + air;
        }else{
            yVel = 0;
        }*/

        //debug out cout << "xVel: " << xVel << " = xVel + " << accelx << endl;
        //debug out cout << "yVel: " << yVel << " = yVel + " << accely << endl << endl;

        /*

         // DETERMINE THE NEW VELOCITY FOR THE PARTICLE
        target->v.x = source->v.x + (DeltaTime * source->f.x * source->oneOverM);
        target->v.y = source->v.y + (DeltaTime * source->f.y * source->oneOverM);
        target->v.z = source->v.z + (DeltaTime * source->f.z * source->oneOverM);

        // SET THE NEW POSITION
        target->pos.x = source->pos.x + (DeltaTime * source->v.x);
        target->pos.y = source->pos.y + (DeltaTime * source->v.y);
        target->pos.z = source->pos.z + (DeltaTime * source->v.z);

        */

        if( buttonpressed == false ){
        //Zero the velocity if too small to matter
        //otherwise update the position
        //if( xVel < -0.01 || xVel < 0.01 ){
            //Divide by meters / pixels
            //x += xVel / 5;
            //x += xVel / 500;

            //x += xVel;

            x += (xVel * deltaTime) / 3;

            //s0 + v0*t + 0.5*a*t^2
            //x += (xVel * deltaTime) + (0.5 * accelx * (deltaTime * deltaTime));
            //debug out cout << "x: " << x << " = x + (" << xVel << " * " << deltaTime << ") / 5" << endl;
        //}else{
        //    xVel = 0;
        //}

        //Zero the velocity if too small to matter
        //otherwise update the position
        //if( yVel < -0.01 || yVel < 0.01 ){
            //Divide by meters / pixels
            //y += yVel / 5;
            //y += yVel / 500;

            //y += yVel;

            y += (yVel * deltaTime) / 3;

            //s0 + v0*t + 0.5*a*t^2
            //y += (yVel * deltaTime) + (0.5 * accely * (deltaTime * deltaTime));
            //debug out cout << "y: " << y << " = y + (" << yVel << " * " << deltaTime << ") / 5" << endl << endl;
        //}else{
        //    yVel = 0;
        //}
        }else{
            xVel = 0;
            yVel = 0;
        }

        //cout << "x: " << x << endl << endl;
        //cout << "y: " << y << endl;

        //Reset Collision Variable (For colored drawing)
        collision = false;

        //Set the vertices
        for( verticesIter = vertices.begin(); verticesIter != vertices.end(); verticesIter++ )
        {
            bool tmpxcol = false;
            bool tmpycol = false;
            bool equal = false;

            //Check edge of screen collision x
            if( xcol == false ){
                if( x + (*verticesIter)->X() < -1.0 ){
                    tmpxcol = true;
                    //x -= (x + (*verticesIter)->X()) - (-1.0);
                    x = (-1.0) - (*verticesIter)->X();
                    //y = tempy;
                }else if( x + (*verticesIter)->X() > 1.0 ){
                    tmpxcol = true;
                    //x -= (x + (*verticesIter)->X()) - (1.0);
                    x = ( 1.0) - (*verticesIter)->X();
                    //y = tempy;
                }
            }

            //Check edge of screen collision y
            if( ycol == false ){
                if( y + (*verticesIter)->Y() < -1.0 ){
                    tmpycol = true;
                    //y -= (y + (*verticesIter)->Y()) - (-1.0);
                    y = (-1.0) - (*verticesIter)->Y();
                    //x = tempx;
                }else if( y + (*verticesIter)->Y() > 1.0 ){
                    tmpycol = true;
                    //y -= (y + (*verticesIter)->Y()) - (1.0);
                    y = ( 1.0) - (*verticesIter)->Y();
                    //x = tempx;
                }
            }

            //If collision reverse velocities and absorb some force
            if( (tmpxcol || tmpycol) && (!xcol || !ycol) ){
                if( tmpxcol && !xcol ){
                    //If velocity less than 1 m/s stop bouncing
                    if( xVel < -1.0 || xVel > 1.0 ){
                        if( mass > 2 ){
                            xVel = -1 * xVel * ((1 / mass) * 2);//0.65;
                            //debug out cout << "air friction x: " << -1 * xVel * ((1 / mass) * 2) << endl;
                        }else{
                            xVel = -1 * xVel * (0.75);
                            //debug out cout << "air friction x: " << -1 * xVel * (0.75) << endl << endl;
                        }
                        //xVel = -xVel;
                    }else{
                        xVel = 0;
                    }
                    if( !equal ){
                        x = tempx;
                    }
                    xcol = true;
                    collision = true;
                }
                if( tmpycol && !ycol ){
                    //If velocity less than 1 m/s stop bouncing
                    if( yVel < -1.0 || yVel > 1.0 ){
                        if( mass > 2 ){
                            yVel = -1 * yVel * ((1 / mass) * 2);//0.65;
                            //debug out cout << "air friction y: " << -1 * yVel * ((1 / mass) * 2) << endl;
                        }else{
                            yVel = -1 * yVel * (0.75);
                            //debug out cout << "air friction y: " << -1 * yVel * (0.75) << endl << endl;
                        }
                        //yVel = -yVel;
                    }else{
                        yVel = 0;
                    }
                    if( !equal ){
                        y = tempy;
                    }
                    ycol = true;
                    collision = true;
                }
            //}else{
            //    if( !xcol && !ycol ){
            //        collision = false;
            //    }
            }
        }

        oldTime = newTime;
    }

    return retval;
}

void Object::Render()
{
    if( vertices.size() <= 0 )
    {
        return;
    }

    //Decide what type of object we're rendering
    //================================================================
    if( vertices.size() == 1 ){

        //Draw Point
        glBegin( GL_POINTS );

    }else if( vertices.size() == 2 ){

        //Draw Line
        glBegin( GL_LINES );

    }else if( vertices.size() == 3 ){

        //Draw Triangle
        glBegin( GL_TRIANGLES );

    }else if( vertices.size() == 4 ){

        //Draw Quad
        glBegin( GL_QUADS );

    }else if( vertices.size() >= 5 ){

        //Draw Polygon
        glBegin( GL_POLYGON );

    }
    //================================================================

    //Render the verices' color and position
    for( verticesIter = vertices.begin(); verticesIter != vertices.end(); verticesIter++ )
	{
	    //Set Color
	    if( collision == true ){
	        glColor3f( 255.0, 0.0, 0.0 );
	    }else{
            glColor3f( (*verticesIter)->R(), (*verticesIter)->G(), (*verticesIter)->B() );
	    }

		//Set Vertex
		glVertex2f( x + (*verticesIter)->X(), y + (*verticesIter)->Y() );
	}

    //End of object data
    glEnd();

    //================================================================
    //Calculate Score based on velocites

    float tempxVel = xVel;
    float tempyVel = yVel;
    float multiplier = 0.05;

    if( tempxVel < 0 ){
        tempxVel = -tempxVel;
    }else if( tempxVel == 0 ){
        //Uh-Oh you're not moving along the x-axis! Less Points! *evil grin*
        multiplier = 0.01;
    }

    if( tempyVel < 0 ){
        tempyVel = -tempyVel;
    }else if( tempyVel == 0 ){
        //Uh-Oh you're not moving along the y-axis! Less Points! *evil grin*
        multiplier = 0.01;
    }

    score += (tempxVel + tempyVel) * multiplier;

	//================================================================
}
