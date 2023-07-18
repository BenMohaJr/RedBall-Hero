#pragma once

#include <SFML/Graphics.hpp>

const sf::Color TextColor(252, 88, 88);

const int WindowWidth = 1886;
const int WindowHeight = 1001;


const float Scale = 30.f;

const float MAX_SPEED = 15.0f;

const auto SpeedPerSecond = 500.f;

const int SettingsText = 4;

const int Text = 4;

const int Musics = 6;

const int Levels = 3;

const int LevelsTexture = 5;

const int Utilities = 10;

const int Objects = 6;

const int Buttons = 7;

const int Balls = 8;

const int HeartsCount = 3;

enum class Utility
{
    Mainmenu, 
    Settings,
    GroundLVL,
    SkyLVL,
    EmptyHeart,
    Heart,
    BlackHeart,
    YouLose,
    YouWin,
    Help
};

enum class Balls
{
    RedBall,
    BlackBall,
    YellowBall,
    Blueberry,
    Clementine,
    Tomato,
    Basketball,
    Football
};

enum class Object
{
    Ball,
    Box,
    Enemy,
    Rock,
    Star,
    Boss
};

enum class Button
{
    PlayButton,
    RestartButton,
    SoundButton,
    MusicButton,
    MuteMusicButton,
    MuteSoundButton,
    PauseButton
};

enum class Sounds 
{
    MenuMusic,
    GameMusic,
    ClickButton,
    Enemy,
    Star,
    WinEnemy
};

enum class Direction 
{    
    Left, 
    Right, 
    Jump,
    Stay
};

enum class Text 
{   
    NewGame, 
    Settings, 
    Help, 
    Exit 
};

enum class TextLevel {
    First,
    Second,
    Third
};



enum class SettingsText
{ 
    Music, 
    Sound, 
    ChangePlayer, 
    Back 
};

enum class Level
{
    Level1_1,
    Level1_2,
    Level2_1,
    Level2_2,
    Level3
};


enum class GameState
{
    Win,
    Lose,
    Advance
};
