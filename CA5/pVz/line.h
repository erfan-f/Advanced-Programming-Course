#ifndef LINE
#define LINE

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include "square.h"
#include "zombie.h"

const int NUM_OF_LINE = 5;
const std::string EATING_SOUND_PATH = "soundeffect/chomp.ogg";

class Line
{
public:
	std::string id;
	Line(float x , float y , std::string n);
	bool is_Square_Range(sf::Vector2i globalPosition,Plant *p);
	bool is_Square_Free(Plant *p);
	Zombie * Generate_Zombie(std::pair <std::string,std::vector<float>> zombie_option);
	bool is_Deadline(Plant* plant);
	bool is_Collided(Bullet *bullet,float current_global_time);
	void Eat_Plant(Zombie* zombie,float current_global_time);
	void Clean_Square(Plant* plant);
	void Add_Plant(Plant *plant);
	void Delete_Zombie(Zombie *zombie);
	void Sort_Zombies_By_X_Position();
	float get_First_Zombie_Velocity();
	sf::Vector2f get_First_Zombie_Position();
	bool is_Zombie_Coming();

private:
	std::vector<Square *> squares;
	std::vector<Zombie*> zombies;
	std::vector<Plant*> plants;
	bool deadline;
	sf::SoundBuffer buffer;
	sf::Sound eating_sound;

};

#endif