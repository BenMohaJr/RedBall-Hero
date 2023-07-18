#include "GameObject.h"

GameObject::GameObject(sf::Vector2f pos, sf::Vector2f scale) : m_isDisposed(false) {
    // Set position from the text file
	m_item.setOrigin(m_item.getGlobalBounds().width / 2, m_item.getGlobalBounds().height / 2);
	m_item.setPosition(pos);
	m_item.setScale(scale);
}

// Destructor to delete b2body
GameObject::~GameObject()
{
    m_body->GetWorld()->DestroyBody(m_body);
}

// Create square body function
void GameObject::createSquareBody(b2World* world, b2BodyType bodyType, sf::Vector2f pos)
{
    //BodyDef
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(pos.x / Scale, pos.y / Scale);
    bodyDef.linearDamping = 0.0f;
    bodyDef.angularDamping = 0.4f;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_body = world->CreateBody(&bodyDef);

    // BoxShape
    b2PolygonShape boxShape;
    boxShape.SetAsBox(getWidth() / 2.f / Scale, getHeight() / 2.f / Scale);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;

    // Create dynamic body if needed
    if (bodyType == b2_dynamicBody)
    {
        // Apply density and friction
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.2f;
    }
    m_body->CreateFixture(&fixtureDef);
}

// Update obj location if needed
void GameObject::updateObj()
{
    // If im a dynaimc body, slow me down a bit every once I reach top speed
    if (m_body->GetType() == b2_dynamicBody)
    {
        m_body->SetAwake(true);
        if (m_body->GetLinearVelocity().x < -MAX_SPEED) {
            m_body->SetLinearVelocity(b2Vec2(-MAX_SPEED, m_body->GetLinearVelocity().y));
        }
        else if (m_body->GetLinearVelocity().x > MAX_SPEED) {
            m_body->SetLinearVelocity(b2Vec2(MAX_SPEED, m_body->GetLinearVelocity().y));
        }
        if (m_body->GetLinearVelocity().y < -MAX_SPEED) {
            m_body->SetLinearVelocity(b2Vec2(m_body->GetLinearVelocity().x, -MAX_SPEED));
        }
        else if (m_body->GetLinearVelocity().y > MAX_SPEED) {
            m_body->SetLinearVelocity(b2Vec2(m_body->GetLinearVelocity().x, MAX_SPEED));
        }
    }
}

// Create Circle body type
void GameObject::createCircleBody(b2World* world, b2BodyType bodyType, float radius)
{
    //BodyDef
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(getPosition().x / Scale, getPosition().y / Scale);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_body = world->CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_p.Set(0, 0);
    circle.m_radius = radius / Scale ;

    // FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;

    // Create dynamic body
    if (bodyType == b2_dynamicBody)
    {
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
    }
    m_body->CreateFixture(&fixtureDef);
}

// Create sensor to apply box2d collisions
void GameObject::createSensor(b2World* world, float width, float height, b2Vec2 center, int data)
{

    b2PolygonShape shape;
    shape.SetAsBox(width, height, center, 0);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = 1.0f;
    fixture.friction = 0.1f;
    fixture.isSensor = true;
    m_body->CreateFixture(&fixture);
}

// Get body width
float GameObject::getWidth() const
{
    return m_item.getGlobalBounds().width;
}

// Get body height
float GameObject::getHeight() const
{
    return m_item.getGlobalBounds().height;
}

// Get body position
sf::Vector2f GameObject::getPosition() const
{
    return m_item.getPosition();
}


