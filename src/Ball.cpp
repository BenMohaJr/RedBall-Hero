#include "Ball.h"

// Constructor
Ball::Ball(sf::Vector2f pos, b2World* world, sf::Vector2f scale)
    // Initialize box2d object for physics
    : MovingObject(Object::Ball, pos, scale), m_life(3), m_inJump(true), m_score(0), m_rightBorder(scale.y) {

    m_item.setScale(0.25, 0.25);

    // Create box2d object
    createCircleBody(world, b2_dynamicBody, m_item.getTexture()->getSize().x / 2u * scale.x);

    // Place amount of hearts on the screen.
    for (size_t i = 0; i < HeartsCount; i++) {
        m_hearts[i].setTexture(Resources::instance().getUtility(Utility::Heart));
        m_hearts[i].setPosition(70 * i + 50, 50);
    }
    // Rearrange mass for the ball
    b2MassData mass;
    mass.center = m_body->GetLocalCenter();
    mass.mass = 40;
    mass.I = m_item.getOrigin().y;
    m_body->SetMassData(&mass);

    // Print the score text
    m_scoreText.setFont(Resources::instance().getFont());
    m_scoreText.setCharacterSize(30);
    //m_scoreText.setStyle(sf::Text::Bold);
    m_scoreText.setFillColor(TextColor);
    m_scoreText.setOutlineColor(sf::Color::White);
    m_scoreText.setOutlineThickness(4);

}
// Move function
void Ball::move(sf::Time deltaTime) {
    // Decide which key pressed
    sf::Vector2f direction = handleKeys();
    float curr_y = m_body->GetLinearVelocity().y;
    float curr_x = m_body->GetLinearVelocity().x;
    // Slow the ball a bit every time
    if (curr_x > 0) {
        curr_x -= 0.1f;
        if (curr_x < 0)
            curr_x = 0;
    }
    // Slow the ball a bit every time
    if (curr_x < 0) {
        curr_x += 0.1f;
        if (curr_x > 0)
            curr_x = 0;
    }
    // move in the wanted direction
    m_body->SetLinearVelocity({ SpeedPerSecond * 0.5f * direction.x + curr_x ,curr_y + 0.01f });


    if (direction.y < 0 && !m_inJump) {
        m_body->ApplyLinearImpulseToCenter(b2Vec2(0, -SpeedPerSecond), true);
        m_inJump = true;
    }


    // Rotate and move the sfml body according to the box2d body
    m_item.rotate(Scale * m_body->GetPosition().x - m_item.getPosition().x);
    m_item.setPosition(Scale * m_body->GetPosition().x, Scale * m_body->GetPosition().y);

    float Position = getPosition().x - float(WindowWidth) / 4;

    // Let the camera follow the ball
    if (Position < 0)
        Position = 0;
    if (Position > m_rightBorder - WindowWidth)
        Position = m_rightBorder - WindowWidth;

    // The hearts follow the ball
    for (size_t i = 0; i < HeartsCount; i++)
        m_hearts[i].setPosition(Position + 70 * i + 50, 50);

    // The score follow the ball
    m_scoreText.setPosition(Position + WindowWidth * 3.25 / 4, 50);
    m_scoreText.setString("SCORE : " + std::to_string(m_score));

    // If the ball fell out of the map
    if (getPosition().y > WindowHeight)
        m_isDisposed = true;
}

//Decide which key was pressed by the user
sf::Vector2f Ball::handleKeys()
{
    auto temp = sf::Vector2f(0, 0);
    // Checks which direction the user wants to go and updates the data accordingly.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        temp.x -= 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        temp.x += 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        temp.y -= 1;
    }

    return temp;
}

// Draw func
void Ball::draw(sf::RenderWindow& window) const {

    // Draw sfml body, score and hearts
    window.draw(m_scoreText);

    window.draw(m_item);

    for (size_t i = 0; i < HeartsCount; i++) {
        window.draw(m_hearts[i]);
    }
}

// If jumped, let the ball return to the floor
void Ball::jump(sf::Vector2f position) {
    int direction;
    if (position.x - m_item.getPosition().x < 0)
        direction = 1;
    else
        direction = -1;

    m_body->ApplyLinearImpulseToCenter(b2Vec2(SpeedPerSecond * direction * 2, -SpeedPerSecond), true);
    m_item.setPosition(Scale * m_body->GetPosition().x, Scale * m_body->GetPosition().y);
    // So you cant jump twice
    m_inJump = true;
}

// Decrease life
void Ball::dicLife() {
    if (m_life > 1) m_life--;
    else m_isDisposed = true;

    m_hearts[m_life].setTexture(Resources::instance().getUtility(Utility::EmptyHeart));
}