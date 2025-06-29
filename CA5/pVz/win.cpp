#include "functions.h"

void Win(sf::RenderWindow &window)
{
	sf::RectangleShape win_page;
	win_page.setSize(sf::Vector2f(window.getSize().x,window.getSize().y));
	win_page.setFillColor(sf::Color::White);

	sf::Text win_text;
	sf::Font font;

	if(!font.loadFromFile(WIN_TEXT_FONT_PATH))
	{
		std::cout << "error in reading font !" << std::endl;
	}

	win_text.setFont(font);
	win_text.setString(WIN_TEXT_STRING);
	win_text.setFillColor(sf::Color::Green);
	win_text.setCharacterSize(DEAD_TEXT_CHAR_SIZE);
	win_text.setPosition(sf::Vector2f(DEAD_TEXT_X_POSITION,DEAD_TEXT_Y_POSITION));

	sf::SoundBuffer buffer;
	sf::Sound victory_sound;

	if(!buffer.loadFromFile(WIN_SOUND_PATH))
	{
		std:: cout << "Error in loading gameover_sound" << std::endl;
	}
	victory_sound.setBuffer(buffer);

	victory_sound.play();

	bool end_statement = false;

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
			    end_statement = true;
			}
			if(event.type == sf::Event::Closed)
				window.close();
		}

		if(end_statement)
			break;
		window.clear();
		window.draw(win_page);
		window.draw(win_text);
		window.display();
	}
}