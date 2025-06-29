#ifndef FUNCTION
#define FUNCTION
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>



const float HOUSE_X_POSITION = 180;
const float DEAD_TEXT_CHAR_SIZE = 150;
const float DEAD_TEXT_X_POSITION = 225;
const float DEAD_TEXT_Y_POSITION = 60;
const float FALLING_SUN_PRIMARY_X_POSITION = 313;
const float FALLING_SUN_PRIMARY_Y_POSITION = 0;


const char ACTION_OPTION_SEPRATOR = ',';


const std::string ATTACKS_OPTION_PATH = "option/attacks_option.csv";
const std::string FALLING_SUN_OPTION_PATH = "option/falling_sun_option.csv";

const std::string MAIN_SOUNDTRACK_PATH =  "soundeffect/grasswalk.ogg";
const std::string ZOMBIE_INTRO_SOUND_PATH = "soundeffect/awooga.ogg";

const std::string WIN_TEXT_FONT_PATH = "font/zombie_font2.ttf";
const std::string WIN_TEXT_STRING = "THE ZOMBIES\n         ARE\n       GONE !";
const std::string WIN_SOUND_PATH = "soundeffect/winmusic.ogg";

const std::string DEAD_TEXT_FONT_PATH = "font/zombie_font2.ttf";
const std::string DEAD_TEXT_STRING = "THE ZOMBIES\n    ATE YOUR\n      BRAINS !";
const std::string GAMEOVER_SOUND_PATH = "soundeffect/evillaugh.ogg";
const std::string DEAD_SOUND_PATH = "soundeffect/scream.ogg";


void Play(sf::RenderWindow &window);
void gameover(sf::RenderWindow &window);
void Win(sf::RenderWindow &window);
void Read_From_File(std::vector<float> &options,std::string file_path);
void Load_Music(sf::Music &music,std::string path);
void Load_Sound(sf::Sound &sound,sf::SoundBuffer &buffer,std::string path);


#endif