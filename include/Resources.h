#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include "consts.h"
#include <exception>
#include <fstream>
#include <system_error>


// Resources class
class Resources{
public:
    ~Resources() = default;
    static Resources& instance();
    sf::Time getGlobalClock();

    void updatePlayer(enum class Balls num) { m_object[(int)Object::Ball] = m_balls[(int)num]; }
    sf::Texture& getBall(unsigned int Ball) { return m_balls[Ball]; }
    sf::Texture& getLevel(unsigned int level) { return m_level[level]; }
    sf::Texture& getUtility(Utility object) { return m_utility[static_cast<int>(object)]; }
    sf::Texture& getObject(Object object) { return m_object[static_cast<int>(object)]; }
    sf::Texture& getButtons(Button object) { return m_button[static_cast<int>(object)]; }
    sf::SoundBuffer& getSounds(Sounds object) { return m_Sound[static_cast<int>(object)]; }
    sf::Font& getFont() { return textFont; }

private:
    Resources();
    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;

    sf::Clock m_globalGameClock;    
    
    sf::Font textFont;
    
    std::vector<sf::Texture> m_balls;
    std::vector<sf::Texture> m_level;
    std::vector<sf::Texture> m_utility;
    std::vector<sf::Texture> m_object;
    std::vector<sf::Texture> m_button;

    std::vector<sf::SoundBuffer> m_Sound;

    // All load functions
    void loadUtilitys();
    void loadBalls();
    void loadObjects();
    void loadButtons();
    void loadLevels();
    void loadSounds();

};