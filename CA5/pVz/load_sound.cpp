#include "functions.h"

void Load_Sound(sf::Sound &sound,sf::SoundBuffer &buffer,std::string path)
{
	if(!buffer.loadFromFile(path))
	{
		std:: cout << "Error in loading sound" << std::endl;
	}
	sound.setBuffer(buffer);
}
