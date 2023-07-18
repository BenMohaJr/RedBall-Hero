#pragma once
#include "MovingObject.h"

const int MyLife = 6;

// Boss class
class Boss : public MovingObject {
public:
	Boss() = default;
	virtual ~Boss() = default;
	Boss(sf::Vector2f, b2World*, sf::Vector2f);
	void move(sf::Time) override;
	void dispose() override;
	void setStanding(int time) { m_item.setRotation(0.f); m_standing = time; }
	bool isStanding() const {return m_standing > 0;}
	void draw(sf::RenderWindow& window) const override;
	void changeDirection() { m_direction = m_direction * -1; }

private:
	float m_standing; // if object is standing or in motion
	int m_direction;
	uint16 m_life;
	sf::Sprite m_hearts[MyLife];
};
