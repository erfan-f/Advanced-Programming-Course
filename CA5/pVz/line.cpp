#include "line.h"

Line::Line(float x , float y , std::string n)
{
 	id = n;
 	deadline = false;

 	if(!buffer.loadFromFile(EATING_SOUND_PATH))
	{
		std:: cout << "Error in loading throw sound !" << std::endl;
	}
	eating_sound.setBuffer(buffer);

	for(int i=0 ; i<NUM_OF_SQUARE ; i++)
	{
		Square *s = new Square(x + (SQUARE_LENGTH *i),y,id,std::to_string(i));
		x+=2;
		squares.push_back(s);
	}
}


bool Line::is_Square_Range(sf::Vector2i globalPosition ,Plant *p)
{
	for(int i=0 ; i<NUM_OF_SQUARE ; i++)
	{
		if(globalPosition.x >= squares[i]->x_position && globalPosition.x <= squares[i]->x_position + SQUARE_LENGTH
		 	&& globalPosition.y >= squares[i]->y_position && globalPosition.y <= squares[i]->y_position + SQUARE_LENGTH)
		{ 
			p->set_Square(id,squares[i]->get_id() , squares[i]->x_position , squares[i]->y_position);
			return true;
		}
	}
	return false;
}

bool Line::is_Square_Free(Plant *p)
{
	for(int i=0 ; i<NUM_OF_SQUARE ; i++)
	{
		if(squares[i]->id == p->square_id)
			if(squares[i]->is_Free(p))
				return true;
	}
	return false;
}

Zombie* Line::Generate_Zombie(std::pair <std::string,std::vector<float>> zombie_option)
{
	std::string new_zombie_id = std::to_string((std::stoi(id) + 1) * 100 + zombies.size());
	Zombie *new_zombie  = new Zombie(zombie_option.first,zombie_option.second,new_zombie_id,id,squares[squares.size() - 1]->x_position + SQUARE_LENGTH , squares[squares.size() - 1]->y_position);
	zombies.push_back(new_zombie);
	deadline = true;
	return new_zombie;
}

bool Line::is_Deadline(Plant* plant)
{
	bool zombie_in_front_statement =false;
	for(int i=0 ; i<zombies.size() ; i++)
	{
		if(zombies[i]->get_x_Position() > plant->get_x_Position())
		{
			zombie_in_front_statement = true;
			break;
		}
	}

	if(deadline && zombie_in_front_statement)
		return true;
	return false;
}

bool Line::is_Collided(Bullet *bullet,float current_global_time)
{
	sf::Vector2f bullet_position = bullet->get_Position();
	for(int i=0 ; i<zombies.size(); i++)
	{
		if(zombies[i]->is_get_Shot(bullet_position,bullet->get_Type(),bullet->get_damage(),current_global_time))
			return true;
	}
	return false;
}

void Line::Eat_Plant(Zombie* zombie , float current_global_time)
{
	bool zombie_eating_status = false;
	for(int i=0 ; i<plants.size() ; i++)
	{
		if(abs(zombie->get_x_Position() - (plants[i]->get_x_Position())) <= 5)
		{
			zombie->Stop();
			zombie->Bite(current_global_time);
			plants[i]->getting_Damage(zombie->get_Damage());
			eating_sound.play();
			zombie_eating_status = true;
		}
	}
	if(!zombie_eating_status)
		zombie->go_Forward();
}

void Line::Clean_Square(Plant* plant)
{
	for(int i=0 ; i<squares.size() ; i++)
	{
		if(squares[i]->id == plant->square_id)
		{
			squares[i]->Clean();
		}
	}
	for(int j=0 ; j<plants.size() ; j++)
	{
		if(plants[j] == plant)
		{
			plants.erase(plants.begin() + j);
		}
	}
	delete plant;
}

void Line::Add_Plant(Plant* plant)
{
	plants.push_back(plant);
}

void Line::Delete_Zombie(Zombie *zombie)
{
	for(int i=0 ; i<zombies.size() ; i++)
	{
		if(zombies[i] == zombie)
		{
			zombies.erase(zombies.begin() + i);
			break;
		}
	}	
}

void Line::Sort_Zombies_By_X_Position()
{
	Zombie* temp_zombie;
	for(int i=0;  i<zombies.size() ; i++)
	{
		for(int j=0 ; j<zombies.size() - 1 ;j++)
		{
			if(zombies[j]->get_x_Position() > zombies[j+1]->get_x_Position())
			{
				temp_zombie = zombies[j];
				zombies[j] = zombies[j+1];
				zombies[j+1] = temp_zombie;
			}
		}
	}
}

float Line::get_First_Zombie_Velocity()
{	
	return zombies[0]->get_Velocity();
}

sf::Vector2f Line::get_First_Zombie_Position()
{
	sf::Vector2f position;
	position.x = zombies[0]->get_x_Position();
	position.y = zombies[0]->get_y_Position();
	return position;
}


bool Line::is_Zombie_Coming()
{
	if(zombies.size() != 0)
		return true;
	return false;
}