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
Object::Object( float nx, float ny, float nmass, float nfS, float nfK )
{

    //Defaults
    x = nx;
    y = ny;

    xVel = 0.0;
    yVel = 0.0;

    xAccel = 0.0;
    yAccel = 0.0;

    mass = nmass;
    elast = 0.0;

    //air = 0.005;
    //air = 0.995;
    //air = 1.0;
    fS = nfS;
    fK = nfK;

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
        //debug out  << "BLARX: " << x << endl;
    }else if( mousex > 320 && mousex <= 640  ){
        x =  1 * (float(mousex - 320) / 320);
    //}else{
        //x = 0.0;
    }

    if( mousey < 240 && mousey >= 0  ){
        y =  1 * (1 - (float(mousey) / 240));
        //debug out  << "BLARY: " << y << endl << endl;
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
        //debug out  << "newTime: " << newTime << ", deltaTime: " << deltaTime << endl;

        //Dunno what these are for..
        //float oldxVel = xVel;
        //float oldyVel = yVel;

        //Store coords in case of collision
        float tempx = x;
        float tempy = y;

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

        totalForcey += mass * -9.81;

        //GAH!  Stop resetting variables.. this is FOR FUN!
        /*if( !collision && (totalForcey != 0 || totalForcex != 0 || xAccel != 0 || yAccel != 0) ){
            totalForcey += mass * -9.81;
        }else{
            if( collision ){
                retval = true;
            }
            x = 0;
            y = 0;
            xVel = 0;
            yVel = 0;
        }*/

        //Calculate frictional force
        //totalForcex += ( -1 * xVel / mass );
        //totalForcey += ( -1 * yVel / mass );
        //cout << "tFx" << totalForcex << " += ( -1 * " << xVel << " / mass );" << endl;
        //cout << "tFy" << totalForcey << " += ( -1 * " << yVel << " / mass );" << endl << endl;

        //Calculate horizontal acceleration after air resistance
        //if( xVel - air > 0 ){
        //    xAccel = totalForcex / mass - air;
        //}else if( xVel + air < 0 ){
        //    xAccel = totalForcex / mass + air;
        //}else{
            //xVel = 0;

        //float airResistancex = 0.96 * xVel;// * xVel;
        //float airResistancey = 0.96 * yVel;// * yVel;

            //xAccel = totalForcex - ((1 - air) * xVel) / mass;// * deltaTime;
            //Accel = (forces - (1/2 * airdensity * Vel^2 * Area * DragCoefficient)) / mass
            //float xDrag = (0.5 * 1.2 * (xVel*xVel) * 20 * 1.05);
            float xDrag = 0.0;
            float xKinFrict = 0.0;
            float xStatFrict = 0.0;

            if( ycol ){

                //Working copy of force variable
                float tempTotalForcey = totalForcey;

                //Get absolute value of force
                if( tempTotalForcey < 0 ){
                    tempTotalForcey = -tempTotalForcey;
                }

                if( xVel == 0 ){
                    if( totalForcex != 0 ){
                        //Calculate Static Friction
                        xStatFrict = (fS * tempTotalForcey);

                        //If force positive, friction should be negative
                        if( totalForcex > 0 ){
                            xStatFrict = -xStatFrict;
                        }

                        //Friction can never be greater than an applied force, only less than or equal
                        if( xStatFrict > 0 && xStatFrict + totalForcex > 0 ){
                            xStatFrict = -totalForcex;
                        }else if( xStatFrict < 0 && xStatFrict + totalForcex < 0 ){
                            xStatFrict = -totalForcex;
                        }
                        //debug out  << "omg stat frict: " << xStatFrict << " N\n";
                    }
                }else{
                    //Calculate kinetic friction
                    xKinFrict = (fK * tempTotalForcey);

                    //If velocity positive, friction should be negative
                    if( xVel > 0 ){
                        xDrag = -xDrag;
                        xKinFrict = -xKinFrict;
                    }
                }
            }

            if( xVel != 0 ){
                //Calculate drag
                xDrag = (0.5 * 1.2 * (xVel*xVel) * 20 * 1.05);

                //If velocity positive, drag should be negative
                if( xVel > 0 ){
                    xDrag = -xDrag;
                }

                //Calculate acceleration
                xAccel = (totalForcex + xDrag + xKinFrict) / mass;
            }else{
                xAccel = (totalForcex + xStatFrict) / mass;
                //debug out  << "omg totalForcex: " << totalForcex << " N\n";
                //debug out  << "omg xAccel: " << xAccel << " m/s\n";
            }

            //xAccel = xAccel - (xAccel * 0.01);
            //xAccel += -1 * xVel / mass;
            //debug out  << "xAccel: " << xAccel << " = " << deltaTime << " * " << totalForcex << " / " << mass << endl;

            //xAccel = deltaTime * totalForcex / mass;
        //}

        //Calculate vertical acceleration after air resistance
        //if( yVel - air > 0 ){
        //    yAccel = totalForcey / mass - air;
        //}else if( yVel + air < 0 ){
        //    yAccel = totalForcey / mass + air;
        //}else{
            //yVel = 0;

            //yAccel = totalForcey - ((1 - air) * yVel) / mass;// * deltaTime;
            /*
            float yDrag = (0.5 * 1.2 * (yVel*yVel) * 20 * 1.05);

            if( yVel < 0 ){
                yAccel = (totalForcey + yDrag) / mass;
            }else{
                yAccel = (totalForcey - yDrag) / mass;
            }
            */

            /*
            float yDrag = (0.5 * 1.2 * (yVel*yVel) * 20 * 1.05);
            //float yDrag = 0;
            float yKinFrict = 0.0;
            float yStatFrict = 0.0;

            if( xcol ){
                if( yVel == 0 ){
                    yStatFrict = (fS * totalForcey);
                }else{
                    yKinFrict = (fK * totalForcey);
                }
            }

            if( yVel < 0 ){
                yAccel = (totalForcey + yDrag + yKinFrict) / mass;
            }else{
                if( yVel == 0 ){
                    yAccel = (totalForcey - yDrag - yStatFrict) / mass;
                }else{
                    yAccel = (totalForcey - yDrag - yKinFrict) / mass;
                }
            }
            */

            float yDrag = 0.0;
            float yKinFrict = 0.0;
            float yStatFrict = 0.0;

            if( xcol ){

                //Working copy of force variable
                float tempTotalForcey = totalForcey;

                //Get absolute value of force
                if( tempTotalForcey < 0 ){
                    tempTotalForcey = -tempTotalForcey;
                }

                if( yVel == 0 ){
                    if( totalForcey != 0 ){
                        //Calculate Static Friction
                        yStatFrict = (fS * tempTotalForcey);

                        //If force positive, friction should be negative
                        if( totalForcey > 0 ){
                            yStatFrict = -yStatFrict;
                        }

                        //Friction can never be greater than an applied force, only less than or equal
                        if( yStatFrict > 0 && yStatFrict + totalForcey > 0 ){
                            yStatFrict = -totalForcey;
                        }else if( yStatFrict < 0 && yStatFrict + totalForcey < 0 ){
                            yStatFrict = -totalForcey;
                        }
                        //debug out  << "omg stat frict: " << yStatFrict << " N\n";
                    }
                }else{
                    //Calculate kinetic friction
                    yKinFrict = (fK * tempTotalForcey);

                    //If velocity positive, friction should be negative
                    if( yVel > 0 ){
                        yDrag = -yDrag;
                        yKinFrict = -yKinFrict;
                    }
                }
            }

            if( yVel != 0 ){
                //Calculate drag
                yDrag = (0.5 * 1.2 * (yVel*yVel) * 20 * 1.05);

                //If velocity positive, drag should be negative
                if( yVel > 0 ){
                    yDrag = -yDrag;
                }

                //Calculate acceleration
                yAccel = (totalForcey + yDrag + yKinFrict) / mass;
            }else{
                yAccel = (totalForcey + yStatFrict) / mass;
                //debug out  << "omg totalForcey: " << totalForcex << " N\n";
                //debug out  << "omg yAccel: " << xAccel << " m/s\n";
            }

            //yAccel = yAccel - (yAccel * 0.01);
            //yAccel += -1 * yVel / mass;
            //debug out  << "yAccel: " << yAccel << " = " << deltaTime << " * " << totalForcey << " / " << mass << endl << endl;

            //yAccel = deltaTime * totalForcey / mass;
        //}

        stringstream objDataString (stringstream::in | stringstream::out);

        glRasterPos2f(-0.99, 0.58);
        objDataString << "XFORCE:" << totalForcex << " N";
        printString(objDataString.str().c_str());
        objDataString.str("");

        glRasterPos2f(-0.99, 0.52);
        objDataString << "YFORCE:" << totalForcey << " N";
        printString(objDataString.str().c_str());
        objDataString.str("");

        glRasterPos2f(-0.99, 0.46);
        objDataString << "XDRAG:" << xDrag << " N";
        printString(objDataString.str().c_str());
        objDataString.str("");

        glRasterPos2f(-0.99, 0.40);
        objDataString << "YDRAG:" << yDrag << " N";
        printString(objDataString.str().c_str());
        objDataString.str("");

        glRasterPos2f(-0.99, 0.34);
        objDataString << "XKINFRICT:" << xKinFrict << " N";
        printString(objDataString.str().c_str());
        objDataString.str("");

        glRasterPos2f(-0.99, 0.28);
        objDataString << "YKINFRICT:" << yKinFrict << " N";
        printString(objDataString.str().c_str());
        objDataString.str("");

        glRasterPos2f(-0.99, 0.22);
        objDataString << "XSTATFRICT:" << xStatFrict << " N";
        printString(objDataString.str().c_str());
        objDataString.str("");

        glRasterPos2f(-0.99, 0.16);
        objDataString << "YSTATFRICT:" << yStatFrict << " N";
        printString(objDataString.str().c_str());
        objDataString.str("");

        glColor3f(1.0, 0.05, 0.05);
        glRasterPos2f(-0.99, 0.10);
        if( xcol ){
            objDataString << "XCOL";
        }
        printString(objDataString.str().c_str());
        objDataString.str("");

        glRasterPos2f(-0.99, 0.04);
        if( ycol ){
            objDataString << "YCOL";
        }
        printString(objDataString.str().c_str());
        objDataString.str("");

        //cout << "xAccel: " << xAccel << endl;
        //cout << "yAccel: " << yAccel << endl;

        //Update Velocities
        //xVel += xAccel;
        xVel += xAccel * deltaTime;
        if( xVel > -0.01 && xVel < 0.01 && xVel != 0 ){
            xVel = 0;
        }
        //Multiply by an abritrary "drag" coefficient
        //--xVel *= air;

        //xVel += (xAccel - airResistancex) * deltaTime;
        //yVel += yAccel;
        yVel += yAccel * deltaTime;
        if( yVel > -0.10 && yVel < 0.10 && yVel != 0 ){
            //yVel = 0;
        }
        //Multiply by an abritrary "drag" coefficient
        //--yVel *= air;

        //yVel += (yAccel - airResistancey) * deltaTime;

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

        //debug out  << "xVel: " << xVel << " = xVel + " << xAccel << endl;
        //debug out  << "yVel: " << yVel << " = yVel + " << yAccel << endl << endl;

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

            //Add velocity to position per unit time and divide by pixels per meter
            x += (xVel * deltaTime);// / 3;

            //s0 + v0*t + 0.5*a*t^2
            //x += (xVel * deltaTime) + (0.5 * xAccel * (deltaTime * deltaTime));
            //debug out  << "x: " << x << " = x + (" << xVel << " * " << deltaTime << ") / 5" << endl;
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

            //Add velocity to position per unit time and divide by pixels per meter
            y += (yVel * deltaTime);// / 3;

            //s0 + v0*t + 0.5*a*t^2
            //y += (yVel * deltaTime) + (0.5 * yAccel * (deltaTime * deltaTime));
            //debug out  << "y: " << y << " = y + (" << yVel << " * " << deltaTime << ") / 5" << endl << endl;
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
        //collision = false;

        //Create/Set Collision variables
        xcol = false;
        ycol = false;

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
                    if( xVel < -0.05 || xVel > 0.05 ){
                        //We need better fake air resistance for sandbox mode
                        xVel = -xVel;// * 0.9;
                        /*if( mass > 2 ){
                            xVel = -1 * xVel * ((1 / mass) * 2);//0.65;
                            cout << "air friction x: " << -1 * xVel * ((1 / mass) * 2) << endl;
                        }else{
                            xVel = -1 * xVel * (0.75);
                            cout << "air friction x: " << -1 * xVel * (0.75) << endl << endl;
                        }*/
                        //xVel = -xVel;
                    }else{
                        xVel = 0.0;
                    }
                    if( !equal ){
                        //x = tempx;
                    }
                    xcol = true;
                    //collision = true;
                }
                if( tmpycol && !ycol ){
                    //If velocity less than 1 m/s stop bouncing
                    if( yVel < -0.50 || yVel > 0.50 ){
                        //We need better fake air resistance for sandbox mode
                        yVel = -yVel;// * 0.9;
                        /*if( mass > 2 ){
                            yVel = -1 * yVel * ((1 / mass) * 2);//0.65;
                            cout << "air friction y: " << -1 * yVel * ((1 / mass) * 2) << endl;
                        }else{
                            yVel = -1 * yVel * (0.75);
                            cout << "air friction y: " << -1 * yVel * (0.75) << endl << endl;
                        }*/
                        //yVel = -yVel;
                    }else{
                        yVel = 0.0;
                    }
                    if( !equal ){
                        //y = tempy;
                    }
                    ycol = true;
                    //collision = true;
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
	    if( ycol == true || xcol == true ){
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
    //Font


    stringstream objDataString (stringstream::in | stringstream::out);

    glColor3f(0.0, 0.5, 1.0);

    glRasterPos2f(-0.99, 0.94);
    objDataString << "X:" << x;
    printString(objDataString.str().c_str());
    objDataString.str("");

    glRasterPos2f(-0.99, 0.88);
    objDataString << "Y:" << y;
    printString(objDataString.str().c_str());
    objDataString.str("");

    glRasterPos2f(-0.99, 0.82);
    objDataString << "XVEL:" << xVel << " M/S";
    printString(objDataString.str().c_str());
    objDataString.str("");

    glRasterPos2f(-0.99, 0.76);
    objDataString << "YVEL:" << yVel << " M/S";
    printString(objDataString.str().c_str());
    objDataString.str("");

    glRasterPos2f(-0.99, 0.70);
    objDataString << "XACC:" << xAccel << " M/S^S";
    printString(objDataString.str().c_str());
    objDataString.str("");

    glRasterPos2f(-0.99, 0.64);
    objDataString << "YACC:" << yAccel << " M/S^2";
    printString(objDataString.str().c_str());
    objDataString.str("");


	//================================================================
}
