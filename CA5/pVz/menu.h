#ifndef MENU
#define MENU

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>

const float CHAR_SIZE = 50;
const std::string MENU_TEXT_1 = "Play";
const std::string MENU_TEXT_2 = "Option";
const std::string MENU_TEXT_3 = "Exit";
const std::string FONT_PATH = "font/zombie_font.ttf";

const int MAX_NUMBER_OF_TEXT = 3;

class Menu
{
public:
	Menu(float width , float height);
	void draw(sf::RenderWindow &window);
	void Move_Mouse(sf::RenderWindow &window);
	std::string get_text_string();
	void play_music();
	void stop_music();
private:
	int selected_item_index;
	sf::Font font;
	sf::Text text[MAX_NUMBER_OF_TEXT];
	sf::RectangleShape background;
	sf::Music menu_soundtrack;
	sf::Texture menu_texture;
};

#endif