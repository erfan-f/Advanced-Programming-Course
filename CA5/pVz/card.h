#ifndef CARD
#define CARD
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


const float CARD_WIDTH = 125;
const float CARD_HEIGHT = 70;
const float PRICE_CHAR_SIZE = 15;

const std::string DIGIT_FONT_PATH = "font/digit_font.ttf";

class Card
{
public:
	Card(std::string n,std::vector<float> options,float x_position , float y_position, std::string on_card_path ,  std::string off_card_path);
	void draw(sf::RenderWindow &window ,float current_global_time,int sun_score);
	sf::Vector2f getPosition();
	bool is_Valid();
	void Payment(int &score ,float current_global_time);
	std::string get_name();

private:
	std::string name;
	int price;
	bool validation;
	sf::RectangleShape shape;
	sf::Texture on_texture;
	sf::Texture off_texture;
	sf::Text price_text;
	sf::Font font;
	float last_time_selected;
	float invalid_time;
};

#endif