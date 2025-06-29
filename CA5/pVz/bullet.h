#ifndef BULLET
#define BULLET
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


const std::string PLANT_TYPE_1 = "sunflower";
const std::string PLANT_TYPE_2 = "peashooter";
const std::string PLANT_TYPE_3 = "snow_peashooter";
const std::string PLANT_TYPE_4 = "walnut";
const std::string PLANT_TYPE_5 = "melonPult";
const std::string PLANT_TYPE_6 = "kernelPult";


const std::string BULLET_TYPE_1 = "Pea Bullet";
const std::string BULLET_TYPE_2 = "Ice Bullet";
const std::string BULLET_TYPE_3 = "Melon Bullet";
const std::string BULLET_TYPE_4 = "Kernel Bullet";

const float BULLET_TYPE_1_SIZE = 10;
const float BULLET_TYPE_2_SIZE = 10;
const float BULLET_TYPE_3_SIZE = 18;
const float BULLET_TYPE_4_SIZE = 25;


const std::string BULLET_TYPE_1_TEXTURE_PATH = "pic/bullets/pea.png";
const std::string BULLET_TYPE_2_TEXTURE_PATH = "pic/bullets/snow_pea.png";
const std::string BULLET_TYPE_3_TEXTURE_PATH = "pic/bullets/melon.png";
const std::string BULLET_TYPE_4_TEXTURE_PATH = "pic/bullets/kernel.png";



class Bullet
{
private:
	float shoot_time;
	float horizontal_velocity;
	float vertical_velocity;
	float target_velocity;
	sf::Vector2f plant_position;
	sf::Vector2f target_position;
	float velocity;
	float damage;
	sf::CircleShape shape;
	sf::Texture bullet_texture;
	std::string type;
public:
	std::string line_id;
	Bullet(std::string plant_name,std::string l_i,float v,float d,float current_global_time,sf::Vector2f p_p,sf::Vector2f t_p,float t_v,float x_plant,float y_plant,float plant_width ,float plant_height);
	void Move(float current_global_time);
	void draw(sf::RenderWindow &window);
	sf::Vector2f get_Position();
	std::string get_Type();
	float get_damage();
};

#endif