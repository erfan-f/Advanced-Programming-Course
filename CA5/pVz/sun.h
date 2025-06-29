#ifndef SUN
#define SUN

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>


const std::string SUN_TEXTURE_PATH = "pic/sun/sun.png";

const float SUN_WIDTH = 100;
const float SUN_HEIGHT = 100;
const float FALLING_SUN_VELOCITY = 2 ; 

class Sun
{
private:
	sf::RectangleShape shape;
	sf::Texture texture;
	float velocity;
public:
	Sun(float v,float x_Position , float y_Position);
	void Move();
	void draw(sf::RenderWindow &window );
    sf::Vector2f get_Position();
};


#endif