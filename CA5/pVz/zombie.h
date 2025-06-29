#ifndef ZOMBIE
#define ZOMBIE

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>

const std::string ZOMBIE_TYPE_1 = "regular";
const std::string ZOMBIE_TYPE_2 = "gargantuar";


const std::string ZOMBIE_TYPE_1_WALKING_FRAMES_ROOT = "pic/frames/zombie_type1_walking_frames/"; 
const std::string ZOMBIE_TYPE_1_EATING_FRAMES_ROOT = "pic/frames/zombie_type1_eating_frames/"; 
const std::string ZOMBIE_TYPE_2_WALKING_FRAMES_ROOT = "pic/frames/zombie_type2_walking_frames/"; 
const std::string ZOMBIE_TYPE_2_EATING_FRAMES_ROOT = "pic/frames/zombie_type2_eating_frames/"; 

const int NUM_OF_FRAME_TYPE_1_WALKING = 74;
const int NUM_OF_FRAME_TYPE_1_EATING = 14;
const float ZOMBIE_TYPE_1_WIDTH = 150;
const float  ZOMBIE_TYPE_1_HEIGHT= 300;


const int NUM_OF_FRAME_TYPE_2_WALKING = 58;
const int NUM_OF_FRAME_TYPE_2_EATING = 26;
const float ZOMBIE_TYPE_2_WIDTH = 180;
const float  ZOMBIE_TYPE_2_HEIGHT= 230;
const float ZOMBIE_TYPE_2_CHANGE_Y_POSITION = -180;

const float ZOMBIE_FRAME_RATE = 0.1;

class Zombie
{
private:
	std::string type;
	std::vector<float > options;
	sf::RectangleShape shape;
	sf::Texture texture;
	std::string id;
	float health;
	float damage;
	float velocity;
	float walk_again_velocity;
	float width;
	float height;
	float last_reaction_time;
	float eating_speed;
	std::vector<sf::Texture> walking_frames_texture;
	std::vector<sf::Texture> eating_frames_texture;
	int walking_frame_index;
	int eating_frame_index;
	float frame_rate;
	float last_time_change_frame;
	bool eat_status;
	bool freeze_status;
	float freeze_time;
	float last_time_freezed;

public:
	std::string line_id;
	Zombie(std::string z_type,std::vector<float> opt,std::string i , std::string l_i ,float primary_x ,float  primary_y);
	void Load_Frames(std::string walking_frames_root,std::string eating_frames_root,int num_of_walking_frames,int num_of_eating_frames);
	void Move();
	void draw(sf::RenderWindow &window ,float current_global_time);
	bool is_get_Shot(sf::Vector2f bullet_position,std::string bullet_type,float bullet_damage,float current_global_time);
	float get_x_Position();
	float get_y_Position();
	void Stop();
	void go_Forward();
	void Bite(float current_global_time);
	bool is_Bite_Time(float current_global_time);
	bool Are_You_Okay();
	bool is_House_Reached(float house_x_position);
	float get_Damage();
	float get_Velocity();
	void Check_Ice_Break(float current_global_time);
};

#endif