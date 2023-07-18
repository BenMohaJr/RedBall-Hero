#pragma once
#include "StaticObject.h"


// Border class
class Border : public StaticObject
{
public:
	Border() = default;
	virtual ~Border() = default;
	Border(sf::Vector2f pos, b2World* world, sf::Vector2f size);
	void setTouching() { m_touching = true; }
	bool getTouching() const { return m_touching; }

private:
	bool m_touching; // if anyone is touching my border
};

