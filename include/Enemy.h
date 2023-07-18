#pragma once
#include "MovingObject.h"


// Enemy class
class Enemy : public MovingObject{
public:
	Enemy() = default;
	virtual ~Enemy() = default;
	Enemy(sf::Vector2f, b2World*, sf::Vector2f);
	void move(sf::Time) override;
	void changeDirection() { m_direction = m_direction * -1; }
	void setDirection(int direction) { m_direction = direction; }

private:
	int m_direction;
};
