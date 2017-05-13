#include "ObjectManager.h"

//Empty Constructor
ObjectManager::ObjectManager()
{

}

//Add object to collection
void ObjectManager::AddObject( Object *object )
{
    objects.push_back( object );
}

//Delete object from collection
void ObjectManager::RemoveObject( int index )
{

}

//Move object
void ObjectManager::SetObjCoords( int index, int mousex, int mousey )
{
    if( index < objects.size() )
    {
        objects[index]->SetCoords( mousex, mousey );
    }
}

bool ObjectManager::Update( bool buttonpressed )
{
    /*
	for ( objectsIter = objects.begin(); objectsIter != objects.end(); objectsIter++ )
	{
		(*objectsIter)->Update( buttonpressed );
	}
	*/
	return objects[0]->Update( buttonpressed );
}

bool ObjectManager::CheckCollision( int mousex, int mousey )
{
    for ( objectsIter = objects.begin(); objectsIter != objects.end(); objectsIter++ )
	{
		//(*objectsIter)->Update();
	}
}

void ObjectManager::Render()
{
    //if( CheckCollision() == false ){
        /*
        for ( objectsIter = objects.begin(); objectsIter != objects.end(); objectsIter++ )
        {
            (*objectsIter)->Render();
        }
        */
        objects[0]->Render();
    //}else{
    //    Update();
    //}
}


void ObjectManager::Render( int index )
{
    if( index >= 0 && index < objects.size() )
    {
        objects[index]->Render();
    }
}
