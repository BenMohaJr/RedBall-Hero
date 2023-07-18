#include "Menu.h"
#include "Resources.h"


//Create all the menu Texture vectors
Menu::Menu(){
    // All create functions
    createMainMenuText();
    createSettingsMenu();
    createPlayerMenu();
}

// Create text for main menu
void Menu::createMainMenuText() {

    m_mainMenuBackground.setTexture(Resources::instance().getUtility(Utility::Mainmenu));

    // Set strings
    m_text[(int)Text::NewGame].setString("NEW GAME");
    m_text[(int)Text::Settings].setString("SETTINGS");
    m_text[(int)Text::Help].setString("HELP");
    m_text[(int)Text::Exit].setString("EXIT");



    // Set all of the texts in place
    for (int i = 0; i < Text; i++) {
        m_text[i].setFont(Resources::instance().getFont());
        m_text[i].setCharacterSize(60);
        m_text[i].setPosition(800, 1000/2 + i * 100);
        m_text[i].setStyle(sf::Text::Bold);
        m_text[i].setFillColor(TextColor);
        m_text[i].setOutlineColor(sf::Color::White);
        m_text[i].setOutlineThickness(4);
    }

    m_text[(int)Text::NewGame].setPosition(675, 1000 / 2);
    m_text[(int)Text::Settings].setPosition(675, 1000 / 2 + 100);
}

// Create choose ball menu
void Menu::createPlayerMenu()
{
    // place all balls in 2 rows and 4 columns
    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < Balls / 2; j++) {
            m_balls[i * Balls / 2 + j].setTexture(Resources::instance().getBall(i * Balls / 2 + j));
            m_balls[i * Balls / 2 + j].setScale(0.50, 0.50);
            m_balls[i * Balls / 2 + j].setPosition(j * 300 + 350, i * 300 + 200);
        }
    // set fill color to cursor when hovering above a ball
    m_cursor.setFillColor(sf::Color::Transparent);
    m_cursor.setOutlineColor(sf::Color::White);
    m_cursor.setOutlineThickness(5);
    m_cursor.setRadius(m_balls[(int)Object::Ball].getGlobalBounds().height / 2u * 1.2);
}

//Create all setting menu
void Menu::createSettingsMenu() {

    m_settingsBackground.setTexture(Resources::instance().getUtility(Utility::Settings));

    // Set all strings and location
    m_settings[static_cast<int>(SettingsText::Music)].setString("MUSIC : ON");
    m_settings[static_cast<int>(SettingsText::Music)].setPosition(650, 350);
    m_settings[static_cast<int>(SettingsText::Sound)].setString("SOUND : ON");
    m_settings[static_cast<int>(SettingsText::Sound)].setPosition(650, 450);
    m_settings[static_cast<int>(SettingsText::ChangePlayer)].setString("CHANGE PLAYER");
    m_settings[static_cast<int>(SettingsText::ChangePlayer)].setPosition(550, 550);
    m_settings[static_cast<int>(SettingsText::Back)].setString("BACK");
    m_settings[static_cast<int>(SettingsText::Back)].setPosition(800, 650);

    // Set size and style for setting menu
    for (auto& object : m_settings) {
        object.setFont(Resources::instance().getFont());
        object.setCharacterSize(60);
        object.setStyle(sf::Text::Bold);
        object.setFillColor(TextColor);
        object.setOutlineColor(sf::Color::White);
        object.setOutlineThickness(4);
    }
}

// Discover where first stage clicked
int Menu::getFirstStageClick(sf::Event::MouseButtonEvent buttonPressed, sf::RenderWindow& window) const {
    for (int i = 0; i < Text; i++)
        if (m_text[i].getGlobalBounds().contains
        (window.mapPixelToCoords({ buttonPressed.x, buttonPressed.y }))) {
            return i;
        }
}

// Get where user has clicked
int Menu::getPlayerClick(sf::Event::MouseButtonEvent buttonPressed, sf::RenderWindow& window) const {
    for (int i = 0; i < Balls; i++)
        if (m_balls[i].getGlobalBounds().contains
        (window.mapPixelToCoords({ buttonPressed.x, buttonPressed.y }))) {
            return i;
        }
}

//Help menu function
void Menu::handleHelp(sf::RenderWindow& Window) {
    Window.clear();
    sf::Sprite Photo;
    Photo.setTexture(Resources::instance().getUtility(Utility::Help));
    Window.draw(Photo);
    Window.display();

    // Decide where button is pressed and return to menu if pressed esc
    while (Window.isOpen()) {


        for (auto event = sf::Event{}; Window.pollEvent(event);) {

            switch (event.type) {

            case sf::Event::Closed:             { Window.close(); }
            case sf::Event::KeyPressed:         { if (sf::Keyboard::Escape == event.key.code)   return; }
            }
        }
    }
}

// Draw all the settings menu
void Menu::drawSettings(sf::RenderWindow& window) {
    window.draw(m_settingsBackground);

    // draw settings
    for (auto& object : m_settings)
        object.setScale(1, 1);

    sf::Vector2f location = (sf::Vector2f)sf::Mouse::getPosition(window);
    // if pressed on something enlarge it
    for (auto& object : m_settings)
        if (object.getGlobalBounds().contains(location))
            object.setScale(1.05, 1.05);

    // draw objects
    for (auto& object : m_settings)
        window.draw(object);
}

// draw all the balls for the change balls menu
void Menu::drawChangePlayer(sf::RenderWindow& window) {
    window.draw(m_settingsBackground);

    // set all balls scale for half
    for (auto& object : m_balls)
        object.setScale(0.50, 0.50);

    sf::Vector2f location = (sf::Vector2f)sf::Mouse::getPosition(window);
    float scale = (m_cursor.getGlobalBounds().height - m_balls[0].getGlobalBounds().height) / 4;
// draw the cursor
    for (auto& object : m_balls)
        if (object.getGlobalBounds().contains(location)) {
            object.setScale(0.55, 0.55);
            m_cursor.setPosition(object.getPosition().x - scale, object.getPosition().y - scale);
            window.draw(m_cursor);
        }

    // draw all the balls
    for (auto& object : m_balls)
        window.draw(object);
}
// Print the menu itself function
void Menu::printMenu(sf::RenderWindow& window) {
    window.draw(m_mainMenuBackground);

    // set scale for text
    for (auto& object : m_text)
        object.setScale(1, 1);

    sf::Vector2f location = (sf::Vector2f)sf::Mouse::getPosition(window);
    for (auto& object : m_text)
        if (object.getGlobalBounds().contains(location))
            object.setScale(1.05, 1.05);

    // draw object
    for (auto& object : m_text) {
        window.draw(object);
    }
}

// Find out which settings text has been pressed
int Menu::getSettingClick(sf::Event::MouseButtonEvent buttonPressed, sf::RenderWindow& window) const  {
    // Go all over the texts and return which text has been pressed
    for (int i = 0; i < SettingsText; i++)
        if (m_settings[i].getGlobalBounds().contains
        (window.mapPixelToCoords({ buttonPressed.x , buttonPressed.y }))) {
            return i;
        }
}