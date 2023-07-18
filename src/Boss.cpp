#include "Boss.h"

Boss::Boss(sf::Vector2f pos, b2World* world, sf::Vector2f scale)
    // Initialize box2d object for physics
    : MovingObject(Object::Boss, pos, scale), m_direction(1), m_life(MyLife), m_standing(0) {

    // Create square body for the boss
    createSquareBody(world, b2_dynamicBody, pos);

    // Apply mass for boss
    b2MassData mass;
    mass.center = m_body->GetLocalCenter();
    mass.mass = 120;
    mass.I = m_item.getOrigin().y;
    m_body->SetMassData(&mass);

    // Arrange boss life count
    for (size_t i = 0; i < MyLife; i++) {
        m_hearts[i].setTexture(Resources::instance().getUtility(Utility::BlackHeart));
        m_hearts[i].setPosition(70 * i + 50, 150);
    }
}

// Move function for boss.
void Boss::move(sf::Time time) {
    if (m_standing > 0) {
        m_standing -= time.asSeconds();
    }

    // Roll the boss if needs to move.
    else {
        float curr_x = m_body->GetLinearVelocity().x;
        m_body->SetLinearVelocity({ SpeedPerSecond * m_direction * 3 + curr_x, 10 });
        m_item.rotate(Scale * m_body->GetPosition().x - m_item.getPosition().x);
        m_item.setPosition(Scale * m_body->GetPosition().x, Scale * m_body->GetPosition().y);
    }
}

// Delete the boss if needed
void Boss::dispose() {
    if (m_life > 1)
        m_life--;
    else
        m_isDisposed = true;
}

// Draw boss object
void Boss::draw(sf::RenderWindow& window) const {

    window.draw(m_item);
    for (size_t i = 0; i < m_life; i++) {
        window.draw(m_hearts[i]);
    }
}