#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "consts.h"

// Menu class
class Menu {
public:
    Menu();
    int getPlayerClick(sf::Event::MouseButtonEvent, sf::RenderWindow&) const;
    int getFirstStageClick(sf::Event::MouseButtonEvent, sf::RenderWindow&) const;
    int getSettingClick(sf::Event::MouseButtonEvent, sf::RenderWindow&) const;
    void handleHelp(sf::RenderWindow&) ;
    void drawSettings(sf::RenderWindow&) ;
    void drawChangePlayer(sf::RenderWindow&) ;
    void printMenu(sf::RenderWindow&) ;
    void setMusicText(bool enabled) { if (enabled) m_settings[0].setString("MUSIC : ON"); else m_settings[0].setString("MUSIC : OFF"); }
    void setSoundText(bool enabled) { if (enabled) m_settings[1].setString("SOUND : ON"); else m_settings[1].setString("SOUND : OFF"); }

private:
    sf::Sprite m_mainMenuBackground ;
    sf::Sprite m_settingsBackground;
    sf::CircleShape m_cursor;
    
    sf::Text m_text[Text];
    sf::Text m_settings[SettingsText];
    sf::Sprite m_balls[Balls];

    void createPlayerMenu();
    void createSettingsMenu();
    void createMainMenuText();
};