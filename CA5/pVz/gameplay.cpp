#include "gameplay.h"


GamePlay::GamePlay(float width , float height)
{
	Read_From_File(plants_options,PLANTS_OPTION_PATH);
	Read_From_File(zombies_options,ZOMBIES_OPTION_PATH);
	Load_Background(width,height);
	Load_Sun_Score();
	Load_Cards();
	Load_Sound(throw_sound,buffer,THROW_SOUND_PATH);	
}

void GamePlay::Load_Background(float width , float height)
{
	playground.setSize(sf::Vector2f(width,height));

	if(!playground_texture.loadFromFile(PLAYGROUND_TEXTURE_PATH))
	{
		std::cout << "error in loading playground texture !" << std::endl;
	}
	playground.setTexture(&playground_texture);

	for(int i=0 ; i<NUM_OF_LINE ; i++)
	{
		Line *l = new Line(FIRST_LINE_X_POSITION,FIRST_LINE_Y_POSITION + ((SQUARE_LENGTH +20) *i),std::to_string(i));
		lines.push_back(l);
	}
}
void GamePlay::Load_Sun_Score()
{
	sun_score = 0;

	score_background.setSize(sf::Vector2f(SCORE_BACKGROUND_WIDTH,SCORE_BACKGROUND_HIGHT));
	score_background.setPosition(sf::Vector2f(POSITION_X_SCORE_BACKGROUND,POSITION_Y_SCORE_BACKGROUND));
	score_background.setFillColor(sf::Color(139, 69, 19));

	score_foreground.setSize(sf::Vector2f(SCORE_FOREGROUND_WIDTH,SCORE_FOREGROUND_HIGHT));
	score_foreground.setPosition(sf::Vector2f(POSITION_X_SCORE_BACKGROUND + (0.33 *SCORE_BACKGROUND_WIDTH) ,POSITION_Y_SCORE_BACKGROUND + 2.75));
	score_foreground.setFillColor(sf::Color(255, 222, 173));

	sun_score_shape.setSize(sf::Vector2f(SCORE_SUN_SAHPE_WIDTH,SCORE_SUN_SAHPE_HIGHT));
	sun_score_shape.setPosition(sf::Vector2f(POSITION_X_SCORE_BACKGROUND,POSITION_Y_SCORE_BACKGROUND));
	if(!sun_score_texture.loadFromFile(SUN_TEXTURE_PATH))
	{
		std::cout << "error in loading card texture !" << std::endl;
	}
	sun_score_shape.setTexture(&sun_score_texture);

    if(!score_font.loadFromFile(DIGIT_FONT_PATH))
	{
		std::cout << "error in reading font !" << std::endl;
	}

	score_text.setFont(score_font);
	score_text.setString(std::to_string(sun_score));
	score_text.setFillColor(sf::Color::Black);
	score_text.setCharacterSize(TEXT_SCORE_CHAR_SIZE);
	score_text.setPosition(sf::Vector2f(POSITION_X_SCORE_BACKGROUND + (0.6 *SCORE_BACKGROUND_WIDTH) ,POSITION_Y_SCORE_BACKGROUND + 20));

}

void GamePlay::Load_Cards()
{

	for(int i=0 ; i<plants_options.size() ; i++)
	{
		std::ostringstream on_path , off_path;
		on_path << PLANT_ON_CARD_ROOT << plants_options[i].first << ".png"; 
		off_path <<	PLANT_OFF_CARD_ROOT << plants_options[i].first << ".png"; 
		std::string on_card_path = on_path.str();
		std::string off_card_path = off_path.str();

		Card* new_card = new Card(plants_options[i].first,plants_options[i].second
			,FIRST_CARD_COORDINATE_X,FIRST_CARD_COORDINATE_Y + (i*(CARD_HEIGHT+10)),on_card_path,off_card_path);
		cards.push_back(new_card);
	}
	
}

void GamePlay::draw(sf::RenderWindow &window ,float current_global_time)
{

	window.draw(playground);
	Draw_Sun_Score(window);
	Draw_Cards(window,current_global_time);
	Draw_Plants(window,current_global_time);
	Draw_Zombies(window,current_global_time);
	Draw_Bullets(window);
	Draw_Falling_Suns(window);
}

void GamePlay::Move_Mouse(sf::RenderWindow &window)
{
	sf::Vector2i localPosition = sf::Mouse::getPosition(window);
	sf::Vector2f card_position;
	for(int i=0 ; i<cards.size() ; i++)
	{
		card_position = cards[i]->getPosition();
		if(localPosition.x >= card_position.x && localPosition.x <= card_position.x + CARD_WIDTH
			&& localPosition.y >= card_position.y && localPosition.y <= card_position.y + CARD_HEIGHT)
		{
			selected_card_index = i;
			break;
		}
		else
		{
			selected_card_index = -1;
		}
	}

	sf::Vector2f sun_position;

	for(int i=0 ; i<suns.size(); i++ )
	{
		sun_position = suns[i]->get_Position();

		if(localPosition.x >= sun_position.x && localPosition.x <= sun_position.x + SUN_WIDTH  
		&& localPosition.y >= sun_position.y && localPosition.y <= sun_position.y + SUN_WIDTH)
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sun_score+=SCORE_COUNTING_UNIT;
				score_text.setString(std::to_string(sun_score));
				delete suns[i];
				suns.erase(suns.begin() + i);
			}
		}
	}
}

void GamePlay::Card_Selection(sf::RenderWindow &window , float current_global_time)
{
	if(selected_card_index != -1)
	{
		Card * selected_card = cards[selected_card_index];
		if(selected_card->is_Valid())
		{
			sf::Vector2i localPosition;
			Plant *new_plant = new Plant(selected_card->get_name(),plants_options[selected_card_index].second);

			plants.push_back(new_plant);
			bool selected_statement = true;
			while(window.isOpen())
			{
				sf::Event event;
				while(window.pollEvent(event))
				{
					localPosition = sf::Mouse::getPosition(window);
					if(is_Line_Range(localPosition , new_plant))
					{
						if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{

							Line* plant_line = Find_Line(new_plant->line_id);
							plant_line->Add_Plant(new_plant);
							selected_statement =  !is_Valid_Square(new_plant);
							selected_card->Payment(sun_score,current_global_time);
							score_text.setString(std::to_string(sun_score));
							break;
						}
					}

					if(event.type == sf::Event::Closed)
						window.close();
				}
				if(!selected_statement)
					break;
				window.clear();
				draw(window,current_global_time);
				window.display();
			}
		}
	}
}
bool GamePlay::is_Line_Range(sf::Vector2i localPosition ,Plant *p)
{
	for(int i=0 ; i<NUM_OF_LINE; i++)
	{
		if(lines[i]->is_Square_Range(localPosition,p))
			return true;
	}
	return false;
	
}

void GamePlay::Draw_Sun_Score(sf::RenderWindow &window )
{
	window.draw(score_background);
	window.draw(sun_score_shape);
	window.draw(score_foreground);
	window.draw(score_text);
}
void GamePlay::Draw_Cards(sf::RenderWindow &window ,float current_global_time)
{
	for(int i=0 ; i<cards.size() ; i++)
	{
		cards[i]->draw(window,current_global_time,sun_score);
	}
}

void GamePlay::Draw_Plants(sf::RenderWindow &window , float current_global_time)
{
	for(int i=0 ; i<plants.size() ; i++)
	{
		plants[i]->draw(window,current_global_time);
	}
}
void GamePlay::Draw_Zombies(sf::RenderWindow &window , float current_global_time)
{
	for(int i=0 ; i<zombies.size() ; i++)
	{
		zombies[i]->draw(window,current_global_time);
	}
}

void GamePlay::Draw_Bullets(sf::RenderWindow &window)
{
	for(int i=0 ; i<bullets.size() ; i++)
	{
		bullets[i]->draw(window);
	}
}

void GamePlay::Draw_Falling_Suns(sf::RenderWindow &window)
{
	for(int i=0 ; i<suns.size() ; i++)
	{
		suns[i]->draw(window);
	}
}


bool GamePlay::is_Valid_Square(Plant *p)
{
	for(int i=0 ; i<NUM_OF_LINE ; i++)
	{
		if(p->line_id == lines[i]->id)
			if(lines[i]->is_Square_Free(p))
				return true;
	}
	return false;
}

void GamePlay::Generate_Zombie()
{
	std::srand(time(0));
	int zombie_type_index = 0 + (std::rand() % zombies_options.size());
	std::srand(time(0));
	Zombie* z = lines[0 +(std::rand() % 5)]->Generate_Zombie(zombies_options[zombie_type_index]);
	zombies.push_back(z);
}

void GamePlay::Generate_Falling_Sun(float sun_x_position ,float sun_y_position,float vertical_speed)
{
	Sun* new_sun = new Sun(vertical_speed,sun_x_position,sun_y_position);
	suns.push_back(new_sun);
}

void GamePlay::Generate_Produced_Sun(float current_global_time)
{
	for(int i=0 ; i<plants.size() ; i++)
	{
		if(plants[i]->is_Act_Time(current_global_time) && plants[i]->is_Producer())
		{	
			Sun* new_sun = plants[i]->Produce_Sun(current_global_time);	
			suns.push_back(new_sun);
		}
	}
}

void GamePlay::Move_Zombies()
{
	for(int i=0 ; i<zombies.size() ; i++)
	{
		zombies[i]->Move();
	}
}

void GamePlay::Move_Falling_Suns()
{
	for(int i=0 ; i<suns.size() ; i++)
	{
		suns[i]->Move();
	}
}

void GamePlay::Plants_Fire(float current_global_time)
{
	for(int i=0 ; i<plants.size() ; i++)
	{
		Line *plant_line = Find_Line(plants[i]->line_id);
		if(plant_line->is_Zombie_Coming())
		{
			float zombie_velocity = plant_line->get_First_Zombie_Velocity();
			sf::Vector2f zombie_position = plant_line->get_First_Zombie_Position();
			if(plants[i]->is_Act_Time(current_global_time) && plants[i]->is_Shooter())
			{
				if(plant_line->is_Deadline(plants[i]))
				{
					Bullet* new_bullet = plants[i]->Shoot_Bullet(current_global_time,zombie_position,zombie_velocity);
					throw_sound.play();
					bullets.push_back(new_bullet);

				}
			}
		}
	}
}

Line* GamePlay::Find_Line(std::string line_id)
{
	for(int i=0 ; i<lines.size() ; i++)
	{
		if(lines[i]->id == line_id)
			return lines[i];
	}
	return NULL;
}

void GamePlay::Move_Bullets(float current_global_time)
{
	for(int i=0 ; i<bullets.size() ; i++)
	{
		bullets[i]->Move(current_global_time);
	}
}

void GamePlay::Bullet_Impact(float current_global_time)
{
	Line* bullet_line;
	for(int i=0 ; i<bullets.size() ; i++)
	{
		bullet_line = Find_Line(bullets[i]->line_id);
		if(bullet_line->is_Collided(bullets[i],current_global_time))
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
	}
}

void GamePlay::Kill_Plants(float current_global_time)
{
	Line* zombie_line;
	for(int i=0 ; i<zombies.size() ; i++)
	{
		if(zombies[i]->is_Bite_Time(current_global_time))
		{
			zombie_line = Find_Line(zombies[i]->line_id);
			zombie_line->Eat_Plant(zombies[i],current_global_time);
		}
	}

}

void GamePlay::Plants_Death()
{
	for(int i=0 ; i<plants.size() ; i++)
	{
		if(plants[i]->is_Dead())
		{
			Line* plant_line = Find_Line(plants[i]->line_id);
			plant_line->Clean_Square(plants[i]);
			plants.erase(plants.begin() + i);
		}
	}
}

void GamePlay::Zombies_Death()
{
	for(int i=0 ; i<zombies.size() ; i++)
	{
		if(!zombies[i]->Are_You_Okay())
		{
			Line* zombie_line = Find_Line(zombies[i]->line_id);
			zombie_line->Delete_Zombie(zombies[i]);
			delete zombies[i];
			zombies.erase(zombies.begin() + i);
		}
	}	
}

bool GamePlay::GameOver(float house_x_position)
{
	for(int i=0 ; i<zombies.size() ; i++)
	{
		if(zombies[i]->is_House_Reached(house_x_position))
			return true;
	}
	return false;
}

void GamePlay::Read_From_File(std::vector<std::pair<std::string,std::vector<float>>> &options , std::string file_path)
{
	std::pair <std::string , std::vector<float>> option;
	std::string name;
	std::string option_str;

	std::fstream fin;
	fin.open(file_path,std::ios::in);

	std::string temp_str;
	getline(fin,temp_str);

	while(getline(fin,temp_str))
	{
		std::vector <float> option_data;
		std::stringstream S(temp_str);
		getline(S,name,SEPRATOR);
		
		while(getline(S,option_str,SEPRATOR))
		{
			option_data.push_back(std::stof(option_str));
		}
		option.first = name;
		option.second = option_data;
		options.push_back(option);
	}	 

	fin.close();
}
void GamePlay::Sort_Zombies()
{
	Sort_By_Line();
	for(int i=0 ; i<lines.size() ; i++)
	{
		lines[i]->Sort_Zombies_By_X_Position();
	}
}

void GamePlay::Sort_By_Line()
{
	Zombie* temp_zombie;
	for(int i=0;  i<zombies.size() ; i++)
	{
		for(int j=0 ; j<zombies.size() - 1 ;j++)
		{
			if(zombies[j]->line_id > zombies[j+1]->line_id)
			{
				temp_zombie = zombies[j];
				zombies[j] = zombies[j+1];
				zombies[j+1] = temp_zombie;
			}
		}
	}
}


bool GamePlay::is_Any_Zombie_Left()
{
	if(zombies.size() == 0)
		return false;
	return true;
}

void GamePlay::Break_Ice(float current_global_time)
{
	for(int i=0 ; i <zombies.size() ; i++)
	{
		zombies[i]->Check_Ice_Break(current_global_time);
	}
}
