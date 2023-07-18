#include "StaticObject.h"



StaticObject::StaticObject(Level type, b2World* world, sf::Vector2f pos, sf::Vector2f scale){

    // Set texture for sfml bodies
	m_item.setTexture(Resources::instance().getLevel(static_cast<int>(type)));
	m_item.setOrigin(getWidth() / 2, getHeight() / 2);
	m_item.setPosition({ pos });
    // Create square body
	createSquareBody(world, b2_staticBody, pos);
}


StaticObject::StaticObject(b2World* world, sf::Vector2f pos, sf::Vector2f scale, Object type) {
    // Set sfml texture
	m_item.setTexture(Resources::instance().getObject(type));
	m_item.setOrigin(getWidth() / 2, getHeight() / 2);
	m_item.setPosition({ pos });
    // Create square body
	createSquareBody(world, b2_staticBody, pos);
}