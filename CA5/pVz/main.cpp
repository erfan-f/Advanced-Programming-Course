#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "menu.h"
#include "functions.h"

const float MENU_WIDTH = 1212;
const float MENU_HEIGHT = 720;
const int FRAME_RATE_LIMIT = 60;
const std::string Command_Type_1 = "Play";
const std::string Command_Type_2 = "Option";
const std::string Command_Type_3 = "Exit";

int main()
{
	sf::RenderWindow window(sf::VideoMode(MENU_WIDTH,MENU_HEIGHT),"test window");
	window.setFramerateLimit(FRAME_RATE_LIMIT);
	Menu menu(window.getSize().x,window.getSize().y);
	menu.play_music();

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			menu.Move_Mouse(window);
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				std::string command = menu.get_text_string();
				if(command == MENU_TEXT_1)
				{
					window.clear();
					menu.stop_music();
					Play(window);
				}
				else if(command == MENU_TEXT_3)
				{
					window.close();
				}

			}
			if(event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		menu.draw(window);
		window.display();
	}
    return 0;
}