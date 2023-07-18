#pragma once

#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>


#include "Ball.h"
#include "Star.h"
#include "Border.h"
#include "Boss.h"
#include "FloorLevel.h"
#include "ObjectFactory.h"
#include "consts.h"
#include "StaticObject.h"
#include "MovingObject.h"
#include "MyContactListener.h"



// Consts for box2d world
const float timeStep = 1.0f / 60.0f;
const int32 velocityIterations = 6, positionIterations = 2;
const b2Vec2 gravity = b2Vec2(0.0f, 11.f);

// World class
class World
{
public:
	World();
	~World() = default;

	void loadLevel(const int levelNum);

	void draw(sf::RenderWindow& Window);
	void moveItem(sf::Time deltaTime);

	bool win() { return m_win && !m_boss; }
	bool lose() { return m_lose; }

private:
	std::unique_ptr<b2World> m_box2dWorld;

	std::vector<std::unique_ptr<MovingObject>> m_players;
	std::vector<std::unique_ptr<StaticObject>> m_objects;
	std::vector<std::unique_ptr<Border>> m_borders;

	sf::Sprite m_sky;
	sf::Sprite m_ground;

	MyContactListener m_contactListener;

	bool m_win, m_lose, m_boss;
	bool isPlayer(std::string) const;
	int  m_rightBorder;
	void moveScreen(sf::RenderWindow& Window);
	void setBorders();
};

