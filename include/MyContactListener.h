#pragma once

#include "GameObject.h"
#include <Box2d/Box2d.h>



// MyContactListener class
class MyContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);
private:

};
