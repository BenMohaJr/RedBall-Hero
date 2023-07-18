#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "consts.h"

// Music function
class Music{
public:
    static Music& instance();

    void playGameMusic();
    void PlayMenu();
    void playStar();
    void playEnemy();
    void PlayClickButton();
    void playWinEnemy();

    bool isMusicEnabled() const { return m_musicEnabled; }
    bool isSoundEnabled() const { return m_soundEnabled; }
    void setMusicEnabled(bool enabled, int music) { if (enabled) m_sound[music].play(); else m_sound[music].stop(); m_musicEnabled = enabled; }
    void setSoundEnabled(bool enabled) { m_soundEnabled = enabled; }

private:
    Music();
    Music(const Music&) = delete;
    Music& operator=(const Music&) = delete;

    sf::Sound m_sound[Musics];
    bool m_musicEnabled;
    bool m_soundEnabled;
};