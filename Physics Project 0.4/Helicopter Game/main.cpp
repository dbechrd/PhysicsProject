#include "ObjectManager.h"
#include "Object.h"
#include "Font.h"

#include "SDL/SDL.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

float score = 0.0;
int finalscore = 0;

int main( int argc, char* args[] )
{
    bool quit = false;
    bool keypressed = false;
    int oldTime = SDL_GetTicks();
    int newTime;
    int deltaTime;
    int lives = 3;

    /*
    GLubyte rasters[24] = {
    0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xff, 0x00, 0xff, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xff, 0xc0, 0xff, 0xc0};
    */
    /*
    GLubyte rasters1[24] = {
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xff, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xe1, 0xc0, 0x73, 0x80, 0x3f, 0x00};
    */

    GLubyte rasters1[13] = {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18};

    /*
    GLubyte rasters2[24] = {
    0x11, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xff, 0x00, 0xff, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xff, 0xc0, 0xff, 0xc0};

    GLubyte rasters3[24] = {
    0x12, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xff, 0x00, 0xff, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xff, 0xc0, 0xff, 0xc0};

    GLubyte rasters4[24] = {
    0x13, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xff, 0x00, 0xff, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xff, 0xc0, 0xff, 0xc0};

    GLubyte rasters5[24] = {
    0x14, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xff, 0x00, 0xff, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xff, 0xc0, 0xff, 0xc0};

    GLubyte rasters6[24] = {
    0x15, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xff, 0x00, 0xff, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xff, 0xc0, 0xff, 0xc0};
    */

    //For handling input
    SDL_Event event;

    //Initiate SDL for OpenGL rendering and set window title
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_WM_SetCaption( "Dan's Physics Demo", NULL );
    SDL_EnableKeyRepeat(1, 100);

    //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_SetVideoMode( 640, 480, 32, SDL_OPENGL );

    init();
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

    ObjectManager ObjMan;

    //Test Solid Obj
    /*Object *solidObj = new Object( 0.0, 0.0, 0.0 );

    solidObj->AddVertex( -0.8, -0.75, 0.0, 0.0, 255.0 );      //yellow
    solidObj->AddVertex( -0.8, -0.85, 0.0, 0.0, 255.0 );      //yellow
    solidObj->AddVertex(  0.8, -0.85, 0.0, 0.0, 255.0 );      //yellow
    solidObj->AddVertex(  0.8, -0.75, 0.0, 0.0, 255.0 );      //yellow
    //solidObj->AddForce( 0.001, 180, 0 );
    ObjMan.AddObject( solidObj );*/

    //Controllable Box
    Object *testObj = new Object( 0.0, 0.0, 10.0 );
    /*
    testObj->AddVertex( -0.03,  0.03, 255.0, 255.0, 255.0 );      //yellow
    testObj->AddVertex( -0.03, -0.03, 255.0, 255.0, 0.0 );      //yellow
    testObj->AddVertex(  0.03, -0.03, 255.0, 255.0, 0.0 );      //yellow
    testObj->AddVertex(  0.03,  0.03, 255.0, 255.0, 0.0 );      //yellow
    */
    testObj->AddVertex( -0.09,  0.09, 1.0, 0.78, 0.0 );      //yellow
    testObj->AddVertex( -0.09, -0.09, 1.0, 0.78, 0.0 );      //yellow
    testObj->AddVertex(  0.09, -0.09, 1.0, 0.78, 0.0 );      //yellow
    testObj->AddVertex(  0.09,  0.09, 1.0, 0.78, 0.0 );      //yellow

    /*
    testObj->AddVertex(  0.0,  0.0,   0.0,   0.0, 255.0 );      //blue
    testObj->AddVertex(  0.0,  0.2, 255.0,   0.0,   0.0 );      //red
    testObj->AddVertex(  0.2,  0.2,   0.0, 255.0,   0.0 );      //green
    testObj->AddVertex(  0.2,  0.0, 255.0, 255.0,   0.0 );      //yellow
    */

    /*
    testObj->AddVertex( -0.05,  0.05, 255.0, 255.0,   0.0 );      //yellow
    testObj->AddVertex( -0.05, -0.05, 255.0,   0.0,   0.0 );      //red
    //=testObj->AddVertex(  0.0 , -0.08,   0.0, 255.0,   0.0 );      //green
    testObj->AddVertex(  0.05, -0.05,   0.0,   0.0, 255.0 );      //blue
    testObj->AddVertex(  0.05,  0.05,   0.0, 255.0, 255.0 );      //cyan
    //=testObj->AddVertex(  0.0 ,  0.08, 255.0,   0.0, 255.0 );      //magenta
    */

    //testObj->AddForce( 1.50, 90 );
    //testObj->AddForce( 0.50, 180 );

    //Gravity
    //testObj->AddForce( 9.81, 180, 0 );
    //testObj->AddForce( 0.001, 180, 0 );

    //testObj->AddForce( 0.005, 15, 100 );
    ObjMan.AddObject( testObj );

    //Lives
    Object *lives1 = new Object( 0.0, 0.0, 0.0 );
    lives1->AddVertex( 0.80, 0.97, 1.0, 0.5, 0.0 );      //yellow
    lives1->AddVertex( 0.80, 0.93, 1.0, 0.5, 0.0 );      //yellow
    lives1->AddVertex( 0.84, 0.93, 1.0, 0.5, 0.0 );      //yellow
    lives1->AddVertex( 0.84, 0.97, 1.0, 0.5, 0.0 );      //yellow
    ObjMan.AddObject( lives1 );

    Object *lives2 = new Object( 0.0, 0.0, 0.0 );
    lives2->AddVertex( 0.87, 0.97, 1.0, 0.5, 0.0 );      //yellow
    lives2->AddVertex( 0.87, 0.93, 1.0, 0.5, 0.0 );      //yellow
    lives2->AddVertex( 0.91, 0.93, 1.0, 0.5, 0.0 );      //yellow
    lives2->AddVertex( 0.91, 0.97, 1.0, 0.5, 0.0 );      //yellow
    ObjMan.AddObject( lives2 );

    Object *lives3 = new Object( 0.0, 0.0, 0.0 );
    lives3->AddVertex( 0.94, 0.97, 1.0, 0.5, 0.0 );      //yellow
    lives3->AddVertex( 0.94, 0.93, 1.0, 0.5, 0.0 );      //yellow
    lives3->AddVertex( 0.98, 0.93, 1.0, 0.5, 0.0 );      //yellow
    lives3->AddVertex( 0.98, 0.97, 1.0, 0.5, 0.0 );      //yellow
    ObjMan.AddObject( lives3 );

    //The frame rate regulator
    //Timer fps;

    bool buttonpressed = false;
    bool mouseleft = false;

    //Handle Input
    while( quit == false )
    {
        //Start the frame timer
        //fps.start();

        int mousex, mousey;

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_KEYDOWN )
            {
                switch( event.key.keysym.sym )
                {
                    case SDLK_SPACE:

                        break;
                    case SDLK_UP:

                        break;
                    case SDLK_DOWN:

                        break;
                    case SDLK_LEFT:

                        break;
                    case SDLK_RIGHT:

                        break;
                    case SDLK_q:
                        if( keypressed == false ){
                            //testObj->AddForce( 0.002, 315, 100 );
                            testObj->AddForce( 120.0, 315, 100 );
                            keypressed = true;
                        }
                        break;

                    case SDLK_w:
                        if( keypressed == false ){
                            //testObj->AddForce( 0.002, 0, 100 );
                            testObj->AddForce( 120.0, 0, 100 );
                            keypressed = true;
                        }
                        break;

                    case SDLK_e:
                        if( keypressed == false ){
                            //testObj->AddForce( 0.002, 45, 100 );
                            testObj->AddForce( 120.0, 45, 100 );
                            keypressed = true;
                        }
                        break;
                    /*
                    case SDLK_a:
                        if( keypressed == false ){
                            //testObj->AddForce( 0.002, 270, 100 );
                            testObj->AddForce( 10.0, 270, 100 );
                            keypressed = true;
                        }
                        break;
                    case SDLK_d:
                        if( keypressed == false ){
                            //testObj->AddForce( 0.002, 90, 100 );
                            testObj->AddForce( 10.0, 90, 100 );
                            keypressed = true;
                        }
                        break;
                    case SDLK_z:
                        if( keypressed == false ){
                            //testObj->AddForce( 0.002, 225, 100 );
                            testObj->AddForce( 10.0, 225, 100 );
                            keypressed = true;
                        }
                        break;
                    case SDLK_x:
                        if( keypressed == false ){
                            //testObj->AddForce( 0.002, 180, 100 );
                            testObj->AddForce( 10.0, 180, 100 );
                            keypressed = true;
                        }
                        break;
                    case SDLK_c:
                        if( keypressed == false ){
                            //testObj->AddForce( 0.003, 135, 100 );
                            testObj->AddForce( 10.0, 135, 100 );
                            keypressed = true;
                        }
                        break;
                    case SDLK_b:
                        //bounce = !bounce;
                        break;
                    */
                    case SDLK_ESCAPE:
                        //Quit the program
                        quit = true;
                        break;
                    default:
                        break;
                }
            }
            else if( event.type == SDL_KEYUP )
            {
                switch( event.key.keysym.sym )
                {
                    case SDLK_UP:
                        //keyup
                        break;
                    case SDLK_DOWN:
                        //keyup
                        break;
                    case SDLK_LEFT:
                        //keyup
                        break;
                    case SDLK_RIGHT:
                        //keyup
                        break;
                    case SDLK_q:
                        //keypressed = false;
                        break;
                    case SDLK_w:
                        //keypressed = false;
                        break;
                    case SDLK_e:
                        //keypressed = false;
                        break;
                    case SDLK_a:
                        //keypressed = false;
                        break;
                    case SDLK_d:
                        //keypressed = false;
                        break;
                    case SDLK_z:
                        //keypressed = false;
                        break;
                    case SDLK_x:
                        //keypressed = false;
                        break;
                    case SDLK_c:
                        //keypressed = false;
                        break;
                }
            }
            /*if( event.type == SDL_MOUSEMOTION )
            {
                //Drag object around if button is pressed
                if( mouseleft == true ){
                    SDL_GetMouseState(&mousex, &mousey);
                    ObjMan.SetObjCoords( 0, mousex, mousey );
                }
			}
            if( event.type == SDL_MOUSEBUTTONDOWN )
            {
                //If the left mouse button was pressed
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    //Get the mouse offsets
                    mousex = event.button.x;
                    mousey = event.button.y;

                    //Check which object is being moved
                    //...

                    //Move object
                    ObjMan.SetObjCoords( 0, mousex, mousey );

                    mouseleft = true;
                    buttonpressed = true;
                }
            }
            if( event.type == SDL_MOUSEBUTTONUP )
            {
                //If the left mouse button was pressed
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    mouseleft = false;
                    buttonpressed = false;
                }
            }*/
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        //Update objects
        if( lives > 0 ){
            if( ObjMan.Update( buttonpressed ) == true ){
                lives--;
            }
        }

        //Clear screen
        glClear(GL_COLOR_BUFFER_BIT);

        /*
        glBegin(GL_QUADS);
            glColor3f(1.0, 1.0, 1.0);
            glVertex2f(-1.0, -1.0);
            glVertex2f( 1.0, -1.0);
            glVertex2f( 1.0,  1.0);
            glVertex2f(-1.0,  1.0);
        glEnd();
        */

        //Draw objects
        ObjMan.Render();

        if( lives > 0 ){
            finalscore = int(score);
        }

        stringstream objDataString (stringstream::in | stringstream::out);
        glColor3f(0.0, 0.5, 1.0);
        glRasterPos2f(-0.99, 0.94);
        objDataString << "SCORE: " << int(finalscore);
        printString(objDataString.str().c_str());
        objDataString.str("");

        //glViewport(0, 0, (GLsizei) 640, (GLsizei) 480);
        //glMatrixMode(GL_PROJECTION);
        //glLoadIdentity();
        //glOrtho (0, 640, 0, 480, -1.0, 1.0);
        //glMatrixMode(GL_MODELVIEW);

        //glColor3f (1.0, 1.0, 1.0);
        //glRasterPos2f (-0.99, 0.94);
        //glBitmap (8, 12, 0.0, 0.0, 11.0, 0.0, rasters1);
        /*
        glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters2);
        glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters3);
        glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters4);
        glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters5);
        glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, rasters6);
        */

        if( lives > 2 ){
            ObjMan.Render( 1 );
            ObjMan.Render( 2 );
            ObjMan.Render( 3 );
        }else if( lives == 2 ){
            ObjMan.Render( 1 );
            ObjMan.Render( 2 );
        }else if( lives == 1 ){
            ObjMan.Render( 1 );
        }else if( lives == 0 ){
            glColor3f(0.0, 0.5, 1.0);
            glRasterPos2f(-0.99, 0.86);
            //printString("THE QUICK BROWN FOX JUMPS");
            printString("GAME OVER");
            glRasterPos2f (-0.99, 0.80);
            //printString("OVER A LAZY DOG29482");
            printString("HOW UNFORTUNATE FOR YOU...");
        }

        if( newTime < 5000 && lives > 0 ){
            glColor3f(0.0, 0.5, 1.0);
            glRasterPos2f(-0.99, 0.86);
            printString("THANKS FOR CHOOSING DAN'S PHYSICS DEMO");
        }

        //Update the screen
        glFlush();
        SDL_GL_SwapBuffers();

        //Get Current Time and Change in Time
        newTime = SDL_GetTicks();
        deltaTime = newTime - oldTime;

        //Limit frame rate
        if( deltaTime < 1000 / 80 ){
            SDL_Delay( ( 1000 / 80 ) - deltaTime );
            //SDL_Delay(2);
        }

        //SDL_Delay( 50 );

        //Update old time variable for next frame
        oldTime = newTime;

        //Reset key states
        keypressed = false;

        /*
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
        */
    }

    //Clean up
    SDL_Quit();

    return 0;
}
