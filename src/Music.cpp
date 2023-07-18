#include "Music.h"
#include "Resources.h"

//contructor
Music::Music() : m_musicEnabled(true), m_soundEnabled(true)
{
    // load all music
    for (size_t i = 0; i < Musics; i++)
        m_sound[i].setBuffer(Resources::instance().getSounds(Sounds(i)));

    // set loops for game music and menu for it to not end
    m_sound[static_cast<int>(Sounds::GameMusic)].setLoop(true);
    m_sound[static_cast<int>(Sounds::MenuMusic)].setLoop(true);
}

// singleton func
Music& Music::instance() {
    static Music music;
    return music;
}

//play game music Function
void Music::playGameMusic(){
    // Check if music is already playing
    if (m_musicEnabled) {
        m_sound[static_cast<int>(Sounds::MenuMusic)].stop();
        m_sound[static_cast<int>(Sounds::GameMusic)].play();
    }
}

//Func for play menu music
void Music::PlayMenu(){
    // Check if music is already playing
    if (m_musicEnabled) {
        m_sound[static_cast<int>(Sounds::GameMusic)].stop();
        m_sound[static_cast<int>(Sounds::MenuMusic)].play();
    }
}

//-------------- NEW FUNCTION --------------
void Music::playStar(){
    // Play music for star
    if(m_soundEnabled)
        m_sound[(int)Sounds::Star].play();
}

//-------------- NEW FUNCTION --------------
void Music::playEnemy(){
    // Play music for enemy
    if (m_soundEnabled)
        m_sound[(int)Sounds::Enemy].play();
}

//-------------- NEW FUNCTION --------------
void Music::playWinEnemy() {
    // Play music for killingEnemy
    if (m_soundEnabled)
        m_sound[(int)Sounds::WinEnemy].play();
}

//-------------- NEW FUNCTION --------------
void Music::PlayClickButton(){
    // Play music for any click
    if (m_soundEnabled)
        m_sound[(int)Sounds::ClickButton].play();
}