#include "Controller.h"


// Constructor
Controller::Controller() : m_window(sf::RenderWindow(sf::VideoMode(WindowWidth, WindowHeight), "Red Ball Hero")) {
    m_window.setFramerateLimit(60);
}

// Run menu Func
void Controller::runMenu()
{
    Music::instance().PlayMenu();
        while (m_window.isOpen())
        {
            for (auto event = sf::Event{}; m_window.pollEvent(event);)
            {
                switch (event.type)
                {
                case sf::Event::Closed: { // if someone wants to quit
                    m_window.close();
                    break;
                }// if any-other key is pressed
                case sf::Event::KeyPressed: {
                    if (sf::Keyboard::Escape == event.key.code)
                        m_window.close();
                    break;
                }
                // If key has been pressed
                case sf::Event::MouseButtonReleased: {
                    handleMainMenu(event.mouseButton);
                    break;
                }
                }
            }
            // Print window
            m_window.clear();
            m_menu.printMenu(m_window);
            m_window.display();
        }
}

//Handle lick on main menu function
void Controller::handleMainMenu(sf::Event::MouseButtonEvent buttonPressed) {
    int Act = m_menu.getFirstStageClick(buttonPressed, m_window);
    // Decide on what has been pressed
    switch (Act) {

        // New game pressed
    case static_cast<int>(Text::NewGame):
        Music::instance().PlayClickButton();
        Music::instance().playGameMusic();
        m_play.runGame(m_window);
        m_menu.setMusicText(Music::instance().isMusicEnabled());
        m_menu.setSoundText(Music::instance().isSoundEnabled());
        Music::instance().PlayMenu();
        break;

        // Help been pressed
    case static_cast<int>(Text::Help):
        Music::instance().PlayClickButton();
        m_menu.handleHelp(m_window);
        break;

        // Settings been pressed
    case static_cast<int>(Text::Settings):
        Music::instance().PlayClickButton();
        settingMenu();
        break;

        // Exit been pressed
    case static_cast<int>(Text::Exit):
        Music::instance().PlayClickButton();
        m_window.close();
        break;
    }
}

// Handle settings menu
void Controller::settingMenu() {
    bool isBack = false;
    while (m_window.isOpen() && !isBack)
    {   // window color
        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed: { // if someone wants to quit
                m_window.close();
                break;
            }// if any-other key is pressed
            case sf::Event::KeyPressed: {
                if (sf::Keyboard::Escape == event.key.code)
                    return;
            }
            case sf::Event::MouseButtonReleased: {
                handleSettingsMenu(event.mouseButton, isBack);
            }
            default:
                ;
            }
        }
        // Print Window
        m_window.clear();
        m_menu.drawSettings(m_window);
        m_window.display();
    }
}

//Handle click on settings menu
void Controller::handleSettingsMenu(sf::Event::MouseButtonEvent buttonPressed, bool& isBack) {
    auto Act = m_menu.getSettingClick(buttonPressed, m_window);
    // Switch for click

    switch (Act) {

        // Music has been pressed
    case static_cast<int>(SettingsText::Music):
        Music::instance().PlayClickButton();
        Music::instance().setMusicEnabled(!Music::instance().isMusicEnabled(), static_cast<int>(Sounds::MenuMusic));
        m_menu.setMusicText(Music::instance().isMusicEnabled());
        break;

        // Sound has been pressed
    case static_cast<int>(SettingsText::Sound):
        Music::instance().PlayClickButton();
        Music::instance().setSoundEnabled(!Music::instance().isSoundEnabled());
        m_menu.setSoundText(Music::instance().isSoundEnabled());
        Music::instance().PlayClickButton();
        break;

        // Change player has been pressed
    case static_cast<int>(SettingsText::ChangePlayer):
        Music::instance().PlayClickButton();
        changePlayer();
        break;

        // Back has been pressed
    case static_cast<int>(SettingsText::Back):
        Music::instance().PlayClickButton();
        isBack = true;
        break;

    default:
            ;
    }
}

// Change player function
void Controller::changePlayer()
{
    bool isBack = false;
    while (m_window.isOpen() && !isBack)
    {   // window color
        for (auto event = sf::Event{}; m_window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed: { // if someone wants to quit
                m_window.close();
                break;
            }// if any-other key is pressed
            case sf::Event::MouseButtonReleased: {
                handleChangePlayer(event.mouseButton, isBack);
            }
            default:
                ;
            }
        }
        // Print window
        m_window.clear();
        m_menu.drawChangePlayer(m_window);
        m_window.display();
    }
}

// Handle player choose function
void Controller::handleChangePlayer(sf::Event::MouseButtonEvent buttonPressed, bool& isBack) {
    auto Act = m_menu.getPlayerClick(buttonPressed, m_window);
    switch (Act) {

        // User choose red ball
    case static_cast<int>(Balls::RedBall):
        Music::instance().PlayClickButton();
        Resources::instance().updatePlayer(Balls::RedBall);
        isBack = true;
        break;

            // User choose black ball
        case static_cast<int>(Balls::BlackBall):
        Music::instance().PlayClickButton();
        Resources::instance().updatePlayer(Balls::BlackBall);
        isBack = true;
        break;

            // User choose Yellow ball
    case static_cast<int>(Balls::YellowBall):
        Music::instance().PlayClickButton();
        Resources::instance().updatePlayer(Balls::YellowBall);
        isBack = true;
        break;

            // User choose blueberry ball
    case static_cast<int>(Balls::Blueberry):
        Music::instance().PlayClickButton();
        Resources::instance().updatePlayer(Balls::Blueberry);
        isBack = true;
        break;

            // User choose clementine ball
    case static_cast<int>(Balls::Clementine):
        Music::instance().PlayClickButton();
        Resources::instance().updatePlayer(Balls::Clementine);
        isBack = true;
        break;

            // User choose tomato ball
    case static_cast<int>(Balls::Tomato):
        Music::instance().PlayClickButton();
        Resources::instance().updatePlayer(Balls::Tomato);
        isBack = true;
        break;

            // User choose basketball ball
    case static_cast<int>(Balls::Basketball):
        Music::instance().PlayClickButton();
        Resources::instance().updatePlayer(Balls::Basketball);
        isBack = true;
        break;

            // User choose football ball
    case static_cast<int>(Balls::Football):
        Music::instance().PlayClickButton();
        Resources::instance().updatePlayer(Balls::Football);
        isBack = true;
        break;

    default:
        ;
    }
}
