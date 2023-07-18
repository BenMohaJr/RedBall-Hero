#pragma once
#include "MovingObject.h"


// Ball class
class Ball : public MovingObject
{
public:
	Ball() = default;
	virtual ~Ball() = default;
	Ball(sf::Vector2f, b2World*, sf::Vector2f);
	void move(sf::Time) override;
	void draw(sf::RenderWindow& window) const override;
	void setInJump() { m_inJump = false; }
	void jump(sf::Vector2f);
	void dicLife();
	void setScore(int num) { m_score += num; }

private:
	uint16 m_life; // ball life count
	uint32 m_score;
	int m_rightBorder; // What's the border i cant pass on the screen where i win if touched
	bool m_inJump; // if im in jump i cant jump again
	sf::Sprite m_hearts[HeartsCount];
	sf::Text m_scoreText;

	sf::Vector2f handleKeys();
};