#ifndef GAMEPLAY
#define GAMEPLAY

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "line.h"
#include "card.h"
#include "functions.h"




const std::string PLANTS_OPTION_PATH = "option/plants_option.csv";
const std::string ZOMBIES_OPTION_PATH = "option/zombies_option.csv";

const char SEPRATOR = ',';

const std::string PLAYGROUND_TEXTURE_PATH = "pic/playground.png";
const std::string THROW_SOUND_PATH = "soundeffect/throw.ogg";

const std::string PLANT_ON_CARD_ROOT = "pic/cards/on_";
const std::string PLANT_OFF_CARD_ROOT = "pic/cards/off_";


const int NUM_OF_CARDS = 5;
const float FIRST_LINE_X_POSITION = 492;
const float FIRST_LINE_Y_POSITION = 188;
const float FIRST_CARD_COORDINATE_X = 50;
const float FIRST_CARD_COORDINATE_Y = 30;

const int SCORE_COUNTING_UNIT = 25;
const float POSITION_X_SCORE_BACKGROUND= 190;
const float POSITION_Y_SCORE_BACKGROUND= 30;
const float TEXT_SCORE_CHAR_SIZE = 30;
const float SCORE_BACKGROUND_WIDTH= 170;
const float SCORE_BACKGROUND_HIGHT= 60;
const float SCORE_FOREGROUND_WIDTH= 112;
const float SCORE_FOREGROUND_HIGHT= 54;
const float SCORE_SUN_SAHPE_WIDTH= 60;
const float SCORE_SUN_SAHPE_HIGHT= 60;



class GamePlay
{
public:
	GamePlay(float width , float height);
	void Load_Background(float width , float height);
	void Read_From_File(std::vector<std::pair<std::string,std::vector<float>>> &options,std::string file_path);
	void Load_Cards();
	void draw(sf::RenderWindow &window,float current_global_time);
	void Move_Mouse(sf::RenderWindow &window);
	void Draw_Cards(sf::RenderWindow &window,float current_global_time);
	void Draw_Plants(sf::RenderWindow &window,float current_global_time);
	void Card_Selection(sf::RenderWindow &window,float current_global_time);
	bool is_Line_Range(sf::Vector2i localPosition ,Plant *p);
	bool is_Valid_Square(Plant *p);
	void Generate_Zombie();
	void Move_Zombies();
	void Draw_Zombies(sf::RenderWindow &window,float current_global_time);
	void Plants_Fire(float current_global_time);
	Line* Find_Line(std::string line_id);
	void Move_Bullets(float current_global_time);
	void Draw_Bullets(sf::RenderWindow &window);
	void Bullet_Impact(float current_global_time);
	void Kill_Plants(float current_global_time);
	void Plants_Death();
	void Zombies_Death();
	bool GameOver(float house_x_position);
	void Generate_Falling_Sun(float sun_x_position,float sun_y_position,float vertical_speed);
	void Move_Falling_Suns();
	void Draw_Falling_Suns(sf::RenderWindow &window);
	void Load_Sun_Score();
	void Draw_Sun_Score(sf::RenderWindow &window );
	void Generate_Produced_Sun(float current_global_time);
	void Sort_Zombies();
	void Sort_By_Line();
	bool is_Any_Zombie_Left();
	void Break_Ice(float current_global_time);

private:
	std::vector<std::pair<std::string,std::vector<float>>> plants_options;
	std::vector<std::pair<std::string,std::vector<float>>> zombies_options;
	
	int sun_score;
	sf::RectangleShape score_background;
	sf::Font score_font;
	sf::Text score_text;
	sf::RectangleShape score_foreground;
	sf::RectangleShape sun_score_shape;
	sf::Texture sun_score_texture;

	int selected_card_index;
	sf::RectangleShape playground;
	sf::Texture playground_texture;
	std::vector<Line *> lines;
	std::vector<Plant*> plants;
	std::vector<Zombie*> zombies;
	std::vector<Bullet*> bullets;
	std::vector <Card*> cards; 
	std::vector<Sun*> suns;
	sf::SoundBuffer buffer;
	sf::Sound throw_sound;
};

#endif