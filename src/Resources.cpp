#include "Resources.h"


//-------------- NEW FUNCTION --------------
// Initialize all textures
Resources::Resources(){
    loadUtilitys();
    loadBalls();
    loadObjects();
    loadButtons();
    loadLevels();
    loadSounds();
}

//-------------- NEW FUNCTION --------------
// Singleton function
Resources &Resources::instance() {
    static Resources resource;
    return resource;
}

// Load utilities function
void Resources::loadUtilitys()
{
    // Resize the vector
    m_utility.resize(Utilities);
    // Load all and if one failed throw exception
    if (!m_utility[static_cast<int>(Utility::Mainmenu)].loadFromFile("menuBackground.png") ||
        !m_utility[static_cast<int>(Utility::Settings)].loadFromFile("settingBackground.png") ||
        !m_utility[static_cast<int>(Utility::GroundLVL)].loadFromFile("Ground.png") ||
        !m_utility[static_cast<int>(Utility::SkyLVL)].loadFromFile("Sky.png") ||
        !m_utility[static_cast<int>(Utility::EmptyHeart)].loadFromFile("EmptyHeart.png") ||
        !m_utility[static_cast<int>(Utility::Heart)].loadFromFile("Heart.png") ||
        !m_utility[static_cast<int>(Utility::BlackHeart)].loadFromFile("BlackHeart.png") ||
        !m_utility[static_cast<int>(Utility::YouLose)].loadFromFile("YOULOSE.png") ||
        !m_utility[static_cast<int>(Utility::YouWin)].loadFromFile("YOUWIN.png") ||
        !m_utility[static_cast<int>(Utility::Help)].loadFromFile("Help.png") ||
        !textFont.loadFromFile("Splatch.ttf"))
        throw std::invalid_argument("Failed To Open File");
}

// Load balls function
void Resources::loadBalls()
{
    // Resize the vector
    m_balls.resize(Balls);
    // Load all and if one failed throw exception
    if (!m_balls[static_cast<int>(Balls::RedBall)].loadFromFile    ("RedBall.png")    ||
        !m_balls[static_cast<int>(Balls::BlackBall)].loadFromFile  ("blackBall.png")  ||
        !m_balls[static_cast<int>(Balls::YellowBall)].loadFromFile ("yellowBall.png") ||
        !m_balls[static_cast<int>(Balls::Blueberry)].loadFromFile  ("Blueberry.png")  ||
        !m_balls[static_cast<int>(Balls::Clementine)].loadFromFile ("clementine.png") ||
        !m_balls[static_cast<int>(Balls::Tomato)].loadFromFile     ("tomato.png")     ||
        !m_balls[static_cast<int>(Balls::Basketball)].loadFromFile ("basketball.png") ||
        !m_balls[static_cast<int>(Balls::Football)].loadFromFile   ("football.png"))
        throw std::invalid_argument("Failed To Open File");
}

void Resources::loadObjects()
{
    // Resize the vector
    m_object.resize(Objects);

    m_object[0] = m_balls[0];

    // Load all and if one failed throw exception
    if (!m_object[static_cast<int>(Object::Box  )].loadFromFile("Box.png"  ) ||
        !m_object[static_cast<int>(Object::Enemy)].loadFromFile("Enemy.png") || 
        !m_object[static_cast<int>(Object::Rock )].loadFromFile("Rock.png" ) ||
        !m_object[static_cast<int>(Object::Star )].loadFromFile("Star.png" ) ||
        !m_object[static_cast<int>(Object::Boss )].loadFromFile("Boss.png" ) )
        throw std::invalid_argument("Failed To Open File");
}

void Resources::loadButtons() 
{
    // Resize the vector
    m_button.resize(Buttons);
    // Load all and if one failed throw exception
    if (!m_button[static_cast<int>(Button::PlayButton)].loadFromFile("PlayButton.png") ||
        !m_button[static_cast<int>(Button::RestartButton)].loadFromFile("RestartButton.png") ||
        !m_button[static_cast<int>(Button::SoundButton)].loadFromFile("MusicButton.png") ||
        !m_button[static_cast<int>(Button::MusicButton)].loadFromFile("MusicButton.png") ||
        !m_button[static_cast<int>(Button::MuteMusicButton)].loadFromFile("MuteMusicButton.png") ||
        !m_button[static_cast<int>(Button::MuteSoundButton)].loadFromFile("MuteMusicButton.png") ||
        !m_button[static_cast<int>(Button::PauseButton)].loadFromFile("PauseButton.png"))
        throw std::invalid_argument("Failed To Open File");
}

void Resources::loadLevels() {

    // Resize the vector
    m_level.resize(LevelsTexture);
    // Load all and if one failed throw exception
    if (!m_level[static_cast<int>(Level::Level1_1)].loadFromFile("LVL1_1.png") ||
        !m_level[static_cast<int>(Level::Level1_2)].loadFromFile("LVL1_2.png") ||
        !m_level[static_cast<int>(Level::Level2_1)].loadFromFile("LVL2_1.png") ||
        !m_level[static_cast<int>(Level::Level2_2)].loadFromFile("LVL2_2.png") ||
        !m_level[static_cast<int>(Level::Level3)].loadFromFile("LVL3.png"))
        throw std::invalid_argument("Failed To Open File");
}

void Resources::loadSounds()
{
    // Resize the vector
    m_Sound.resize(Musics);
    // Load all and if one failed throw exception
    if (!m_Sound[static_cast<int>(Sounds::MenuMusic  )].loadFromFile("MenuMusic.wav"  ) ||
        !m_Sound[static_cast<int>(Sounds::GameMusic  )].loadFromFile("GameMusic.wav"  ) || 
        !m_Sound[static_cast<int>(Sounds::ClickButton)].loadFromFile("ClickButton.wav") ||
        !m_Sound[static_cast<int>(Sounds::Enemy      )].loadFromFile("Enemy.wav"      ) ||
        !m_Sound[static_cast<int>(Sounds::Star       )].loadFromFile("Star.wav"       ) ||
        !m_Sound[static_cast<int>(Sounds::WinEnemy   )].loadFromFile("WinEnemy.wav"   )  )
        throw std::invalid_argument("Failed To Open File");
}

//-------------- NEW FUNCTION --------------
sf::Time Resources::getGlobalClock() {
    return m_globalGameClock.getElapsedTime();
}
