#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "Music.h"
#include "Game.h"
#include "consts.h"

//Controller class
class Controller{
public:
    Controller();
    void runMenu();

private:
    sf::RenderWindow m_window;
    Menu m_menu;
    Game m_play;

    void handleMainMenu(sf::Event::MouseButtonEvent);
    void settingMenu();
    void changePlayer();
    void handleChangePlayer(sf::Event::MouseButtonEvent buttonPressed, bool& isBack);
    void handleSettingsMenu(sf::Event::MouseButtonEvent, bool&);
};