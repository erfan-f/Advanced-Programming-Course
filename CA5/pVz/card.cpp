#include "card.h"

Card::Card(std::string n,std::vector<float> options,float x_position , float y_position, std::string on_card_path ,  std::string off_card_path)
{
	name = n;
	invalid_time = options[2];
	validation = false;
	price = options[5];
	last_time_selected = 0;

	shape.setSize(sf::Vector2f(CARD_WIDTH,CARD_HEIGHT));
	shape.setPosition(x_position,y_position);

	if(!on_texture.loadFromFile(on_card_path))
	{
		std::cout << "error in loading card texture!" << std::endl;
	}

	if(!off_texture.loadFromFile(off_card_path))
	{
		std::cout << "error in loading card texture!" << std::endl;
	}

	shape.setTexture(&off_texture);

	if(!font.loadFromFile(DIGIT_FONT_PATH))
	{
		std::cout << "error in loading digit font!" << std::endl;
	}

	price_text.setFont(font);
	price_text.setString(std::to_string(price));
	price_text.setCharacterSize(PRICE_CHAR_SIZE);
	price_text.setFillColor(sf::Color::Black);
	price_text.setPosition(sf::Vector2f(x_position + (0.65 * CARD_WIDTH) ,y_position + (0.65 * CARD_HEIGHT) + 2.5));

}

void Card::draw(sf::RenderWindow &window ,float current_global_time,int sun_score)
{
	if((current_global_time - last_time_selected >= invalid_time) && sun_score >= price)
		validation =true;
	else
		validation = false;

	if(validation)
		shape.setTexture(&on_texture);
	else
		shape.setTexture(&off_texture);

	window.draw(shape);
	window.draw(price_text);
}

sf::Vector2f Card::getPosition()
{
	return shape.getPosition();
}

bool Card::is_Valid()
{
	return validation;
}

void Card::Payment(int &score,float current_global_time)
{
	score-=price;
	if(score < 0)
		score+= price;
	last_time_selected = current_global_time;
	validation = false;
}

std::string Card::get_name()
{
	return name;
}