#pragma once
#include "StaticObject.h"


// Floorlevel class
class FloorLevel : public StaticObject
{
public:
	FloorLevel() = default;
	virtual ~FloorLevel() = default;
	FloorLevel(sf::Vector2f pos, Level type, b2World* world, sf::Vector2f scale);

private:
};