#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

// MovingObject class
class MovingObject : public GameObject{
public:
    MovingObject(Object, sf::Vector2f, sf::Vector2f);
    virtual ~MovingObject() = default;
    virtual void move(sf::Time);
protected:
};

