#include "Star.h"


Star::Star(sf::Vector2f pos, b2World* world, sf::Vector2f scale)
    // Initialize box2d object for physics
	: StaticObject(world, pos, scale, Object::Star)
{
}

