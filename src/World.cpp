#include "World.h"

// World
World::World() {
    // create box2d world
	m_box2dWorld = std::make_unique<b2World>(gravity);
    // Set collision handler
	m_box2dWorld->SetContactListener(&m_contactListener);
}

// Load level function
void World::loadLevel(const int levelNum)
{
	std::string levelName = "Level" + std::to_string(levelNum) + ".txt";
	std::ifstream levelFile;
	std::string line, objType;
	float locX, locY;
	float scaleX, scaleY;
	std::stringstream ssline;
	m_win = m_lose = m_boss = false;

    // Set exceptions for file handling
	levelFile.exceptions(std::ifstream::badbit);
	ssline.exceptions(ssline.failbit | ssline.badbit);


    // Clear vectors
	m_objects.clear();
	m_players.clear();
	m_borders.clear();

	levelFile.open(levelName); 

	if (!levelFile.is_open())
		throw std::runtime_error("Coudlnt open " + levelName + "Returning to lvl 1");

	levelFile.seekg(0);

    // Set texture for background
	m_sky.setTexture(Resources::instance().getUtility(Utility::SkyLVL));
	m_ground.setTexture(Resources::instance().getUtility(Utility::GroundLVL));

    // Set game borders
	getline(levelFile, line);
	m_rightBorder = std::stoi(line);
	setBorders();

	getline(levelFile, line); //Read line of labels in file

	//reading contents of level
	while (getline(levelFile, line))
	{
		ssline.clear();
		ssline.str(line);
        // Take all info from file and process it
		ssline >> objType >> locX >> locY >> scaleX >> scaleY;
		if (isPlayer(objType))
		{
            // Create moving object
			auto o = ObjectFactory<MovingObject>::createM(objType, sf::Vector2f(locX, locY), m_box2dWorld.get(), sf::Vector2f(scaleX, scaleY));
			if (o){

                // Insert for vector
				m_players.emplace_back(move(o));

				if (objType == "Boss")
					m_boss = true;
			}
			else //wasnt able to create object
				throw std::invalid_argument("Tried To Create Wrong Object");
		}
		else 
		{
            // Create static object
			auto o = ObjectFactory<StaticObject>::createS(objType, sf::Vector2f(locX, locY), m_box2dWorld.get(), sf::Vector2f(scaleX, scaleY));
			if (o){
                // Insert for vector
				m_objects.emplace_back(move(o));
			}
			else //wasnt able to create object
				throw std::invalid_argument("Tried To Create Wrong Object");
		}
	}
    // Close file for memory.
	levelFile.close();
}

// Move item in the world
void World::moveItem(sf::Time deltaTime) {
	for (auto& object : m_players) {
		object->move(deltaTime);
		object->updateObj();
	}

    // box2d move function
	m_box2dWorld->Step(timeStep, velocityIterations, positionIterations);

    // If Static needs to be deleted, delete
	for (int i = 0; i < m_objects.size(); i++)
		if (m_objects[i]->isDisposed())
			m_objects.erase(m_objects.begin() + i);

    // If Moving needs to be deleted, delete
	for (int i = 0; i < m_players.size(); i++)
		if (m_players[i]->isDisposed()) {

			if (typeid(*m_players[i]) == typeid(Ball))
				m_lose = true;
			if (typeid(*m_players[i]) == typeid(Boss))
				m_boss = false;

			m_players.erase(m_players.begin() + i);
		}
    // If i touch the end border
	if (m_borders[2]->getTouching())
		m_win = true;
}

// Draw world function
void World::draw(sf::RenderWindow& Window) {
	// Set view.
	moveScreen(Window);

    // print game background
	Window.draw(m_sky);
	Window.draw(m_ground);

    // draw moving objects
	for (auto& object : m_players) {
		object->draw(Window);
	}

    // draw static objects
	for (auto& object : m_objects) {
		object->draw(Window);
	}

}

// Move screen function
void World::moveScreen(sf::RenderWindow& Window) {

    // Find out where the ball is
	float Position = {0};
	for (auto& object : m_players) {
		if (typeid(*object) == typeid(Ball)) {
			Position = object->getPosition().x + float(WindowWidth) / 4;
		}
	}
    // Find out where ball on screen and adjust view by that
	if (Position < WindowWidth / 2)
		Position = WindowWidth / 2;
	if (Position > m_rightBorder - (WindowWidth / 2))
		Position = m_rightBorder - (WindowWidth / 2);
	
	m_sky.setPosition(Position - WindowWidth / 2, 0);

    // Set view
	sf::View view(sf::Vector2f(Position, WindowHeight / 2), sf::Vector2f(WindowWidth, WindowHeight));
	Window.setView(view);
}

// Set borders in vector.
void World::setBorders() {
	m_borders.emplace_back(std::make_unique<Border>(sf::Vector2f(0, WindowHeight / 2), &(*m_box2dWorld), sf::Vector2f(1, WindowHeight)));
	m_borders.emplace_back(std::make_unique<Border>(sf::Vector2f(WindowWidth * 1.5, 0), &(*m_box2dWorld), sf::Vector2f(m_rightBorder, 1)));
	m_borders.emplace_back(std::make_unique<Border>(sf::Vector2f(m_rightBorder, WindowHeight /2), &(*m_box2dWorld), sf::Vector2f(1, WindowHeight)));
}

// If the object is moving, return true
bool World::isPlayer(std::string objType) const
{
	if ( objType == "Ball" || objType == "Enemy" ||
		 objType == "Box"  || objType == "Rock"  ||
		 objType == "Boss")
		return true;
	return false;
}