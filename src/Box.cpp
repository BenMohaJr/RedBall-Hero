#include "Box.h"


Box::Box(sf::Vector2f pos, b2World* world, sf::Vector2f scale)
    // Initialize box2d object for physics
    : MovingObject(Object::Box, pos, scale) {

    // Create square body
    createSquareBody(world, b2_dynamicBody, pos);

    // Apply mass for body
    b2MassData mass;
    mass.center = m_body->GetLocalCenter();
    mass.mass = 80;
    mass.I = m_item.getOrigin().y;
    m_body->SetMassData(&mass);
}

