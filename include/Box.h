#pragma once
#include "MovingObject.h"

// Box class
class Box : public MovingObject
{
public:
	Box() = default;
	virtual ~Box() = default;
	Box(sf::Vector2f, b2World*, sf::Vector2f);

private:
};