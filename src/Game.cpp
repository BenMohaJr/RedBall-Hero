#include "game.h"
#include "Music.h"

// Constructor.
Game::Game() {
    // Load level
    m_world.loadLevel(m_currentLevel);

    m_background.setTexture(Resources::instance().getUtility(Utility::Settings));

    // Set texture for menu buttons
    m_pauseButton.setTexture(Resources::instance().getButtons(Button::PauseButton));
    m_pauseButton.setScale({ 1, 1 });
    m_pauseButton.setPosition({ WindowWidth/2 , 50 });
    m_pauseButton.setOrigin(sf::Vector2f(m_pauseButton.getTexture()->getSize() / 2u));

    // Set buttons position
    for (size_t i = 0; i < MyButtons; i++) {
        m_buttons[i].setTexture(Resources::instance().getButtons(Button(i)));
        m_buttons[i].setScale({ 1, 1 });
        m_buttons[i].setPosition( WindowWidth / 4 + (WindowWidth * 0.5 / MyButtons) * i, WindowHeight / 2 );
        m_buttons[i].setOrigin(sf::Vector2f(m_buttons[i].getTexture()->getSize() / 2u));
    }

    // Set strings
    m_levels[(int)TextLevel::First].setString("LEVEL 1");
    m_levels[(int)TextLevel::Second].setString("LEVEL 2");
    m_levels[(int)TextLevel::Third].setString("LEVEL 3");


    // Set all of the texts in place
    for (int i = 0; i < Levels; i++) {
        m_levels[i].setFont(Resources::instance().getFont());
        m_levels[i].setCharacterSize(60);
        m_levels[i].setPosition(800, 500 / 2 + i * 150);
        m_levels[i].setStyle(sf::Text::Bold);
        m_levels[i].setFillColor(TextColor);
        m_levels[i].setOutlineColor(sf::Color::White);
        m_levels[i].setOutlineThickness(4);
    }
}


// Run game function
void Game::runGame(sf::RenderWindow& window)
{
    updateButton();
    // Restart game clock

    m_currentLevel = ChooseLevel(window);
    m_world.loadLevel(m_currentLevel);
    m_gameClock.restart();
    try {
        while (window.isOpen())
        {
            // Decide If we won or lost
            GameState state = winOrLose();
            if (state == GameState::Lose || state == GameState::Win)
                // print screens if won or lost
                HandleWinOrLose(state, window);


            // Handle window
            for (auto event = sf::Event(); window.pollEvent(event);)
            {
                switch (event.type)
                {
                    // Close window
                case sf::Event::Closed: {
                    // if someone wants to quit
                    window.close();
                    break;
                }// if any-other key is pressed
                case sf::Event::KeyPressed: {
                    if (sf::Keyboard::Escape == event.key.code)
                    {
                        // Set  view
                        sf::View view(sf::Vector2f(WindowWidth / 2, WindowHeight / 2), sf::Vector2f(WindowWidth, WindowHeight));
                        window.setView(view);
                        return;
                    }
                    break;
                case sf::Event::MouseButtonReleased: {
                    if (m_pauseButton.getGlobalBounds().contains
                    (window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
                        settingMenu(window);
                    break;
                }
                }
                default:
                    ;
                }
            }
            // Move window
            move(window);
        }
    }
    // Catch exceptions if needs to be thrown
    catch (const std::runtime_error& e) { std::cerr << "Exception caught: " << e.what() << std::endl;  m_currentLevel = 1; }
}



// Func to choose which evel to run
int Game::ChooseLevel(sf::RenderWindow& Window) {

    while (Window.isOpen()) {

        // Choose level
        for (auto event = sf::Event{}; Window.pollEvent(event);) {

            switch (event.type) {

            case sf::Event::Closed: { Window.close(); }
            case sf::Event::KeyPressed: { if (sf::Keyboard::Escape == event.key.code)   return 1; }
            case sf::Event::MouseButtonPressed: { return checkLevelPressed(event.mouseButton, Window); }
            }
        }

        // Print window
        Window.clear();
        PrintLevels(Window);
        Window.display();
    }
    return 1;// return default if not choosen
}

// Func to see which level the player pressed on
int Game::checkLevelPressed(sf::Event::MouseButtonEvent buttonPressed, sf::RenderWindow& window) {
    for (int i = 0; i < Levels; i++)
        if (m_levels[i].getGlobalBounds().contains // check which level pressed on
        (window.mapPixelToCoords({ buttonPressed.x, buttonPressed.y }))) {
            return i + 1;
        }
}

// Print levels menu
void Game::PrintLevels(sf::RenderWindow& window) {
    window.draw(m_background);

    // draw object
    for (auto& object : m_levels) {
        window.draw(object);
    }
}


// If win or lose funciton
GameState Game::winOrLose() {
    if (m_world.win()) {
        // if no lives
        if (m_currentLevel < Levels) {
            m_currentLevel += 1;
            m_world.loadLevel(m_currentLevel);

            return GameState::Advance;
        }
        // Here you won
        else {
            m_currentLevel = 1;
            m_world.loadLevel(m_currentLevel);

            return GameState::Win;
        }
    }
    // If you lost, load first level.
    if (m_world.lose()) {
        m_currentLevel = 1;
        m_world.loadLevel(m_currentLevel);
        return GameState::Lose;
    }
    // Keep playing
    return GameState::Advance;
}

// Load Photo of win or lose
void Game::HandleWinOrLose(GameState state, sf::RenderWindow& window){
    sf::Sprite photo;
    // Win photo
    if (state == GameState::Win)
        photo.setTexture(Resources::instance().getUtility(Utility::YouWin));
    else // Lose Photo
        photo.setTexture(Resources::instance().getUtility(Utility::YouLose));

    window.clear();
    window.draw(photo);
    window.display();
    std::this_thread::sleep_for(std::chrono::seconds(10));
}

// Move function handler
void Game::move(sf::RenderWindow& window) {
    const auto deltaTime = m_gameClock.restart();

    window.clear();

    // Move items by delta time
    m_world.moveItem(deltaTime);

    sf::View view = window.getView();
    m_pauseButton.setPosition(view.getCenter().x, 50);
    // Set buttons
    for (size_t i = 0; i < MyButtons; i++)
        m_buttons[i].setPosition((view.getCenter().x - WindowWidth / 4) + (WindowWidth * 0.5 / MyButtons * i) + 50 , WindowHeight / 2);

    //Draw
    m_world.draw(window);
    window.draw(m_pauseButton);
    window.display();
}

// Settings menu Function
void Game::settingMenu(sf::RenderWindow& window) {
    bool isBack = false;
    // Handle Setting menu
    while (window.isOpen() && !isBack)
    {   // window color
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed: { // if someone wants to quit
                window.close();
                break;
            }// if any-other key is pressed
            case sf::Event::KeyPressed: { // Escape button handle
                if (sf::Keyboard::Escape == event.key.code)
                    return;
            }
            // Mouse button on setting menu
            case sf::Event::MouseButtonReleased: {
                handleButton(event.mouseButton, window, isBack);
            }
            default:
                ;
            }
        }
        draw(window);
    }
}

// Handle button menu
void Game::handleButton(sf::Event::MouseButtonEvent buttonPressed, sf::RenderWindow& window, bool& isBace) {
    int Act = 10;
    // Setting text handler
    for (int i = 0; i < SettingsText; i++)
        if (m_buttons[i].getGlobalBounds().contains
        (window.mapPixelToCoords({ buttonPressed.x , buttonPressed.y })))
            Act = i;

    // Switch for which button has been pressed
    switch (Act) {

        // If play button was pressed
    case static_cast<int>(Button::PlayButton):
        Music::instance().PlayClickButton();
        isBace = true;
        return;

        // If restart button is pressed
    case static_cast<int>(Button::RestartButton):
        Music::instance().PlayClickButton();
        m_world.loadLevel(m_currentLevel);
        isBace = true;
        break;

        // If music button is pressed
    case static_cast<int>(Button::MusicButton):
        Music::instance().PlayClickButton();
        Music::instance().setMusicEnabled(!Music::instance().isMusicEnabled(), static_cast<int>(Sounds::GameMusic));
        updateButton();

        break;

        // If sound button is pressed
    case static_cast<int>(Button::SoundButton):
        Music::instance().PlayClickButton();
        Music::instance().setSoundEnabled(!Music::instance().isSoundEnabled());
        Music::instance().PlayClickButton();
        updateButton();
        break;
    default:
        isBace = true;
    }
}

// Update music button Functions
void Game::updateButton() {
    // If the music is already active and music button has been pressed
    if (Music::instance().isMusicEnabled())
        m_buttons[(int)Button::MusicButton].setTexture(Resources::instance().getButtons(Button::MusicButton));
    else
        m_buttons[(int)Button::MusicButton].setTexture(Resources::instance().getButtons(Button::MuteMusicButton));

    // If the sound is already active and music button has been pressed
    if (Music::instance().isSoundEnabled())
        m_buttons[(int)Button::SoundButton].setTexture(Resources::instance().getButtons(Button::SoundButton));
    else
        m_buttons[(int)Button::SoundButton].setTexture(Resources::instance().getButtons(Button::MuteSoundButton));
}

// Draw all the music buttons
void Game::draw(sf::RenderWindow& window) {
    window.clear();
    m_world.draw(window);
    for (auto& object : m_buttons)
        window.draw(object);
    window.display();
}
