#include "Vertex.h"

//Constructor Sets Coords and Color
Vertex::Vertex( float nx, float ny, float nr, float ng, float nb )
{
    x = nx;
    y = ny;
    r = nr;
    g = ng;
    b = nb;
}

Vertex::~Vertex()
{

}

//Retrieve X
float Vertex::X()
{
    return x;
}

//Assign X
void Vertex::X( float nx )
{
    x = nx;
}

//Retrieve Y
float Vertex::Y()
{
    return y;
}

//Assign Y
void Vertex::Y( float ny )
{
    y = ny;
}

//Retrieve R
float Vertex::R()
{
    return r;
}

//Assign R
void Vertex::R( float nr )
{
    r = nr;
}

//Retrieve G
float Vertex::G()
{
    return g;
}

//Assign G
void Vertex::G( float ng )
{
    g = ng;
}

//Retrieve B
float Vertex::B()
{
    return b;
}

//Assign B
void Vertex::B( float nb )
{
    b = nb;
}
