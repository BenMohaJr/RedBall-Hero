#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

// Static object class
class StaticObject : public GameObject{
public:
    StaticObject() = default;
    virtual ~StaticObject() = default;
    StaticObject(Level , b2World*, sf::Vector2f, sf::Vector2f);
    StaticObject(b2World*, sf::Vector2f, sf::Vector2f, Object);

protected:

};