#pragma once
#include "MovingObject.h"

// Rock class
class Rock : public MovingObject
{
public:
	Rock() = default;
	virtual ~Rock() = default;
	Rock(sf::Vector2f, b2World*, sf::Vector2f);
	void move(sf::Time) override ;

private:

};


