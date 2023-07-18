#pragma once
#include "StaticObject.h"

// Star class
class Star : public StaticObject {
public:
	Star() = default;
	virtual ~Star() = default;
	Star(sf::Vector2f pos, b2World* world, sf::Vector2f scale);

private:
};
