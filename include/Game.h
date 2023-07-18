#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <thread>
#include "World.h"

const int MyButtons = 4;

// Game class
class Game
{
public:
	Game();
	void runGame(sf::RenderWindow&);

private:
	World m_world;
	sf::Sprite m_pauseButton;
	sf::Sprite m_buttons[MyButtons];
	int m_currentLevel = 1;
	sf::Clock m_gameClock;

	sf::Text m_levels[Levels];
	sf::Sprite m_background;

	void handleButton(sf::Event::MouseButtonEvent, sf::RenderWindow&, bool&);
	void settingMenu(sf::RenderWindow&);
	void draw(sf::RenderWindow&);
	void move(sf::RenderWindow&);
	void updateButton();
	int ChooseLevel(sf::RenderWindow& window);
	int checkLevelPressed(sf::Event::MouseButtonEvent buttonPressed, sf::RenderWindow& window);
	void PrintLevels(sf::RenderWindow& window);
	GameState winOrLose();

	void HandleWinOrLose(GameState, sf::RenderWindow&);
};