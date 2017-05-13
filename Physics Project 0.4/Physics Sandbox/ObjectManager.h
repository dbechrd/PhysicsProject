#ifndef OBJECTMANAGER_H_INCLUDED
#define OBJECTMANAGER_H_INCLUDED

#include "Object.h"

#include <vector>

using namespace std;

class ObjectManager{

    private:

        vector<Object*> objects;
        vector<Object*>::iterator objectsIter;

    public:

        ObjectManager();
        void AddObject( Object *object );
        void RemoveObject( int index );
        void SetObjCoords( int index, int mousex, int mousey );
        bool Update( bool buttonpressed );
        bool CheckCollision( int mousex, int mousey );
        void Render();
        void Render( int index );

};

#endif // OBJECTMANAGER_H_INCLUDED
