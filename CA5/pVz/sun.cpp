#include "sun.h"

Sun::Sun(float v,float x_Position , float y_Position)
{
	velocity = v;
	
	if(!texture.loadFromFile(SUN_TEXTURE_PATH))
	{ 
		std:: cout << "error in loading sun texture !" << std::endl;	
	}
	shape.setSize(sf::Vector2f(SUN_WIDTH,SUN_HEIGHT));
	shape.setTexture(&texture);
	shape.setPosition(sf::Vector2f(x_Position,y_Position));
 }

void Sun::draw(sf::RenderWindow &window)
{
	window.draw(shape);
}

void Sun::Move()
{
	shape.move(0,velocity);

}

sf::Vector2f Sun::get_Position()
{
	return shape.getPosition(); 
}