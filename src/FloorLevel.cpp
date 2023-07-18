#include "FloorLevel.h"

FloorLevel::FloorLevel(sf::Vector2f pos, Level type, b2World* world, sf::Vector2f scale)
    // Initialize box2d object for physics
	: StaticObject(type, world, pos, scale)
{
}
