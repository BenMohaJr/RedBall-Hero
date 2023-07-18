#include "Rock.h"


Rock::Rock(sf::Vector2f pos, b2World* world, sf::Vector2f scale)
    // Initialize box2d object for physics
    : MovingObject(Object::Rock, pos, scale) {

    createCircleBody(world, b2_dynamicBody, m_item.getTexture()->getSize().x / 2u);

    // Apply body mass
    b2MassData mass;
    mass.center = m_body->GetLocalCenter();
    mass.mass = 100;
    mass.I = m_item.getOrigin().y;
    m_body->SetMassData(&mass);
}

// Move object if pushed
void Rock::move(sf::Time) {
    m_item.rotate(Scale * m_body->GetPosition().x - m_item.getPosition().x);
    m_body->SetLinearVelocity({ 0 , MAX_SPEED });
    m_item.setPosition(Scale * m_body->GetPosition().x, Scale * m_body->GetPosition().y);
}