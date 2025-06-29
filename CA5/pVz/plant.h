#ifndef PLANT
#define PLANT

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "bullet.h"
#include "sun.h"




const std::string PLANT_TYPE_1_FRAMES_ROOT = "pic/frames/sunflower_frames/";
const std::string PLANT_TYPE_2_FRAMES_ROOT = "pic/frames/peashooter_frames/";
const std::string PLANT_TYPE_3_FRAMES_ROOT = "pic/frames/snow_peashooter_frames/";
const std::string PLANT_TYPE_5_FRAMES_ROOT = "pic/frames/melonPult_frames/";
const std::string PLANT_TYPE_6_FRAMES_ROOT = "pic/frames/kernelPult_frames/";
const std::string PLANT_TYPE_4_TEXTURE_PATH = "pic/frames/walnut_frames/walnut.png";
const std::string PLANT_TYPE_4_CRACKED1_TEXTURE_PATH = "pic/frames/walnut_frames/walnut_cracked1.png";
const std::string PLANT_TYPE_4_CRACKED2_TEXTURE_PATH = "pic/frames/walnut_frames/walnut_cracked2.png";

const float PLANT_FRAME_RATE = 0.1;
const int PLANT_TYPE_1_NUM_OF_FRAMES = 61;
const int PLANT_TYPE_2_NUM_OF_FRAMES = 39;
const int PLANT_TYPE_3_NUM_OF_FRAMES = 31;
const int PLANT_TYPE_5_NUM_OF_FRAMES = 24;
const int PLANT_TYPE_6_NUM_OF_FRAMES = 53;


const float SUNFLOWER_WIDTH = 80;
const float SUNFLOWER_HEIGHT = 80;
const float PEASHOOTER_WIDTH = 80;
const float PEASHOOTER_HEIGHT = 80;
const float SNOW_PEASHOOTER_WIDTH = 80;
const float SNOW_PEASHOOTER_HEIGHT = 80;
const float WALNUT_WIDTH = 80;
const float WALNUT_HEIGHT = 80;
const float MELON_PULT_WIDTH = 100;
const float MELON_PULT_HEIGHT = 105;
const float KERNEL_PULT_WIDTH = 110;
const float KERNEL_PULT_HEIGHT = 110;




class Plant
{
public:
	std::string line_id ;
	std::string square_id ;
	Plant(std::string type,std::vector<float> options);
	void Load_Frames(std::string root_path , int num_of_frames);
	void draw(sf::RenderWindow &window,float current_global_time);
	void set_Square(std::string l,std::string s,float square_x_position,float square_y_position);
	Bullet* Shoot_Bullet(float current_global_time,sf::Vector2f target_position,float target_velocity);
	Sun* Produce_Sun(float current_global_time);
	bool is_Act_Time(float current_global_time);
	float get_x_Position();
	void getting_Damage(float zombie_damage);
	bool is_Producer();
	bool is_Shooter();
	float get_Width();
	bool is_Dead();

private:
	std::string type;
	std::vector<float> plant_options;
	float width;
	float height;
	float health;
	float damage;
	float last_reaction_time;
	float action_speed;
	bool shooter;
	bool producer;
	sf::RectangleShape shape;
	std::vector<sf::Texture> frames_texture;
	int frame_index;
	float frame_rate;
	float last_time_change_frame;
};

#endif