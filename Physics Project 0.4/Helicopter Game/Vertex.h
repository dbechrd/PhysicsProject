#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

class Vertex{

    private:

        //Coordinates
        float x;
        float y;

        //Color
        float r;
        float g;
        float b;

    public:

        //Constructor
        Vertex( float nx, float ny, float nr, float ng, float nb );
        ~Vertex();

        //Overloaded Coordinate Assignment / Retrieval
        float X();
        void X( float nx );
        float Y();
        void Y( float ny );
        float R();
        void R( float nr );
        float G();
        void G( float ng );
        float B();
        void B( float nb );

};

#endif // POINT_H_INCLUDED
