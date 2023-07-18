#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos, b2World* world, sf::Vector2f scale)
    // Initialize box2d object for physics
    : MovingObject(Object::Enemy, pos, scale), m_direction(1){

    // Create square body
    createSquareBody(world, b2_dynamicBody, pos);

    // Apply mass for body
    b2MassData mass;
    mass.center = m_body->GetLocalCenter();
    mass.mass = 120;
    mass.I = m_item.getOrigin().y;
    m_body->SetMassData(&mass);
}

// Move enemy if needed
void Enemy::move(sf::Time) {
   // rotate and move
    m_body->SetLinearVelocity({ SpeedPerSecond * m_direction, 10 });
    m_item.rotate(Scale * m_body->GetPosition().x - m_item.getPosition().x);
    m_item.setPosition(Scale * m_body->GetPosition().x, Scale * m_body->GetPosition().y);
}