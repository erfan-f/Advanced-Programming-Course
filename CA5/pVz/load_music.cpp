#include "functions.h"

void Load_Music(sf::Music &music , std::string path)
{
	if(!music.openFromFile(path))
	{
		std:: cout << "Error in loading music!" << std::endl;
	}
}