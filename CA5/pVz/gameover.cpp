#include "functions.h"

void gameover(sf::RenderWindow &window)
{
	sf::RectangleShape dead_page;
	dead_page.setSize(sf::Vector2f(window.getSize().x,window.getSize().y));
	dead_page.setFillColor(sf::Color::Black);

	sf::Text dead_text;
	sf::Font font;

	if(!font.loadFromFile(DEAD_TEXT_FONT_PATH))
	{
		std::cout << "error in reading font !" << std::endl;
	}

	dead_text.setFont(font);
	dead_text.setString(DEAD_TEXT_STRING);
	dead_text.setFillColor(sf::Color::Red);
	dead_text.setCharacterSize(DEAD_TEXT_CHAR_SIZE);
	dead_text.setPosition(sf::Vector2f(DEAD_TEXT_X_POSITION,DEAD_TEXT_Y_POSITION));

	sf::SoundBuffer buffer;
	sf::Sound gameover_sound;

	if(!buffer.loadFromFile(GAMEOVER_SOUND_PATH))
	{
		std:: cout << "Error in loading gameover_sound" << std::endl;
	}
	gameover_sound.setBuffer(buffer);

	gameover_sound.play();

	bool end_statement = false;

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
			    end_statement = true;
			}
			if(event.type == sf::Event::Closed)
				window.close();
		}

		if(end_statement)
			break;
		window.clear();
		window.draw(dead_page);
		window.draw(dead_text);
		window.display();
	}
}
