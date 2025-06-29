#include "menu.h"

Menu::Menu(float width , float height)
{
	background.setSize(sf::Vector2f(width,height));

	if(!menu_texture.loadFromFile("pic/background.jpg"))
	{
		std::cout << "Error in loading background picture !" << std::endl;
	}
	background.setTexture(&menu_texture);

	if(!menu_soundtrack.openFromFile("soundeffect/menu_track.ogg"))
	{
		std:: cout << "Error in loading music" << std::endl;
	}



	if(!font.loadFromFile(FONT_PATH))
	{
		std::cout << "error in reading font !" << std::endl;
	}

	text[0].setFont(font);
	text[0].setString(MENU_TEXT_1);
	text[0].setFillColor(sf::Color::Black);
	text[0].setCharacterSize(CHAR_SIZE);
	text[0].setPosition(sf::Vector2f(width / 2 - CHAR_SIZE, (height/4) * 1));

	text[1].setFont(font);
	text[1].setString(MENU_TEXT_2);
	text[1].setCharacterSize(CHAR_SIZE);
	text[1].setFillColor(sf::Color::Black);
	text[1].setPosition(sf::Vector2f(width / 2 - CHAR_SIZE, (height/4) * 2));


	text[2].setFont(font);
	text[2].setString(MENU_TEXT_3);
	text[2].setCharacterSize(CHAR_SIZE);
	text[2].setFillColor(sf::Color::Black);
	text[2].setPosition(sf::Vector2f(width / 2 - CHAR_SIZE, (height/4) * 3));


}

void Menu::draw(sf::RenderWindow &window)
{
	window.draw(background);
	for(int i=0 ; i<MAX_NUMBER_OF_TEXT ; i++)
	{
		window.draw(text[i]);
	}
}

void Menu::Move_Mouse(sf::RenderWindow &window)
{
	sf::Vector2i localPosition = sf::Mouse::getPosition(window);
	sf::Vector2f text_position;
	for(int i=0 ; i<MAX_NUMBER_OF_TEXT ; i++)
	{
		text_position = text[i].getPosition();
		if(localPosition.x >= text_position.x && localPosition.x <= text_position.x +(2 * CHAR_SIZE) &&
		    localPosition.y >= text_position.y && localPosition.y < text_position.y + CHAR_SIZE)
		{
			text[i].setFillColor(sf::Color::Red);
			selected_item_index = i;
			break;
		}
		else
		{
			text[i].setFillColor(sf::Color::Black);
			selected_item_index = -1;
		}
	}
	
}

std::string Menu::get_text_string()
{
	if(selected_item_index == 0 || selected_item_index == 1 || selected_item_index == 2) 
		return text[selected_item_index].getString();
	else
		return "invalid !";
}

void Menu::play_music()
{
	menu_soundtrack.play();
}

void Menu::stop_music()
{
	menu_soundtrack.stop();
}