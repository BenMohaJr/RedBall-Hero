#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Resources.h"
#include "consts.h"
#include <Box2D/Box2D.h>


// Game object class
class GameObject {
public:
	GameObject() = default;
	GameObject(sf::Vector2f pos, sf::Vector2f scale);
	~GameObject();

	void updateObj();
	float getWidth() const;
	float getHeight() const;
	sf::Vector2f getPosition() const;
	virtual void dispose() { m_isDisposed = true; }
	bool isDisposed() { return m_isDisposed; }
	void virtual draw(sf::RenderWindow& window) const { window.draw(m_item); }

protected:
	bool m_isDisposed = { false }; // If an object needs to be deleted
	b2Body* m_body = nullptr;
	sf::Sprite m_item;

	void createSquareBody(b2World* world, b2BodyType bodyType, sf::Vector2f rect);
	void createCircleBody(b2World* world, b2BodyType bodyType, float radius);
	void createSensor(b2World* world, float width, float height, b2Vec2 center, int data);
};