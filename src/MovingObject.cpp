#include "MovingObject.h"


MovingObject::MovingObject(Object type, sf::Vector2f pos, sf::Vector2f scale)
	: GameObject(pos, scale)
{
    // initialize SFML body texture and scale and position
	m_item.setTexture(Resources::instance().getObject(type));
	m_item.setScale({ scale });
	m_item.setPosition({ pos });
	m_item.setOrigin(sf::Vector2f(m_item.getTexture()->getSize() / 2u));
}

// move all moving object.
void MovingObject::move(sf::Time) {
	m_body->SetLinearVelocity({ 0 , MAX_SPEED });
	m_item.setPosition(Scale * m_body->GetPosition().x, Scale * m_body->GetPosition().y);
}