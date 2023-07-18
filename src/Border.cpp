#include "Border.h"

// Arrange screen borders to know where the lvl ends
Border::Border(sf::Vector2f pos, b2World* world, sf::Vector2f size) : m_touching(false) {

    // Creating b2body
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(pos.x / Scale, pos.y / Scale);
    bodyDef.linearDamping = 0.0f;
    bodyDef.angularDamping = 0.4f;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_body = world->CreateBody(&bodyDef);


    b2PolygonShape boxShape;
    boxShape.SetAsBox(size.x / 2.f / Scale, size.y / 2.f / Scale);
    b2FixtureDef fixtureDef;

    fixtureDef.shape = &boxShape;

    m_body->CreateFixture(&fixtureDef);
}