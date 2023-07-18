#pragma once


#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include <typeinfo>
#include "Ball.h"
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "FloorLevel.h"
#include "Star.h"
#include "Enemy.h"
#include "Boss.h"
#include "Box.h"
#include "Rock.h"

// Template object factory class
template <class T>
class ObjectFactory
{
public:
    // Map object definition
	using pFnc = std::unique_ptr<T>(*)(sf::Vector2f pos, b2World* world, sf::Vector2f scale);

	static std::unique_ptr<T> createM(const std::string&, sf::Vector2f, b2World*, sf::Vector2f);
	static std::unique_ptr<T> createS(const std::string&, sf::Vector2f, b2World*, sf::Vector2f);

private:
	ObjectFactory() = default;
	ObjectFactory(const ObjectFactory&) = delete;
	void operator=(const ObjectFactory&) = delete;

	static void insert(const std::string& name, pFnc);

    // Generic get object from map function
	static auto& getObjMap() {
		static std::map<std::string, pFnc> objMap;
		return objMap;
	}
};

//=======================================================================
		//STATIC OBJECTS FACTORY
//=======================================================================

// Load all moving object to map function
template<class T>
std::unique_ptr<T> ObjectFactory<T>::createM(const std::string& name, sf::Vector2f pos, b2World* world, sf::Vector2f scale)
{
	static bool initial = true;

	if (initial) {
		insert("Ball" , [](sf::Vector2f pos, b2World* world, sf::Vector2f scale) -> std::unique_ptr<T> { return std::make_unique< Ball  >(pos, world, scale); });
		insert("Enemy", [](sf::Vector2f pos, b2World* world, sf::Vector2f scale) -> std::unique_ptr<T> { return std::make_unique< Enemy >(pos, world, scale); });
		insert("Box"  , [](sf::Vector2f pos, b2World* world, sf::Vector2f scale) -> std::unique_ptr<T> { return std::make_unique< Box   >(pos, world, scale); });
		insert("Rock" , [](sf::Vector2f pos, b2World* world, sf::Vector2f scale) -> std::unique_ptr<T> { return std::make_unique< Rock  >(pos, world, scale); });
		insert("Boss" , [](sf::Vector2f pos, b2World* world, sf::Vector2f scale) -> std::unique_ptr<T> { return std::make_unique< Boss  >(pos, world, scale); });
		initial = false;
	}

    // Get objects
	auto it = ObjectFactory::getObjMap().find(name);
	if (it == ObjectFactory::getObjMap().end())
		return nullptr;
	return it->second(pos, world, scale);
}

// Load all static objects to map
template<class T>
std::unique_ptr<T> ObjectFactory<T>::createS(const std::string& name, sf::Vector2f pos, b2World* world, sf::Vector2f scale)
{
	static bool initial = true;

	if (initial) {
		insert("Star"  , [](sf::Vector2f pos, b2World* world, sf::Vector2f scale) -> std::unique_ptr<T> { return std::make_unique< Star      >(pos, world, scale); });
		insert("LVL1_1", [](sf::Vector2f pos, b2World* world, sf::Vector2f scale) -> std::unique_ptr<T> { return std::make_unique< FloorLevel>(pos, Level::Level1_1, world, scale); });
		insert("LVL1_2", [](sf::Vector2f pos, b2World* world, sf::Vector2f scale) -> std::unique_ptr<T> { return std::make_unique< FloorLevel>(pos, Level::Level1_2, world, scale); });
		insert("LVL2_1", [](sf::Vector2f pos, b2World* world, sf::Vector2f scale) -> std::unique_ptr<T> { return std::make_unique< FloorLevel>(pos, Level::Level2_1, world, scale); });
		insert("LVL2_2", [](sf::Vector2f pos, b2World* world, sf::Vector2f scale) -> std::unique_ptr<T> { return std::make_unique< FloorLevel>(pos, Level::Level2_2, world, scale); });
		insert("LVL3"  , [](sf::Vector2f pos, b2World* world, sf::Vector2f scale) -> std::unique_ptr<T> { return std::make_unique< FloorLevel>(pos, Level::Level3, world, scale); });
		initial = false;
	}

    // Get static objects
	auto it = ObjectFactory::getObjMap().find(name);
	if (it == ObjectFactory::getObjMap().end())
		return nullptr;
	return it->second(pos, world, scale);
}

// Insert objects to map
template<class T>
void ObjectFactory<T>::insert(const std::string& name, pFnc f) {
	ObjectFactory::getObjMap().emplace(name, f);
}