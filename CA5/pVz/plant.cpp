#include "plant.h"

Plant::Plant(std::string t,std::vector<float> options)
{
	type = t;
	plant_options = options;
	last_reaction_time = 0;
	last_time_change_frame = 0;

	if(type == PLANT_TYPE_1)
	{
		type = PLANT_TYPE_1;
		width = SUNFLOWER_WIDTH;
		height = SUNFLOWER_HEIGHT;
		action_speed = plant_options[3];
		health = plant_options[1];
		shooter = false;
		producer = true;

		Load_Frames(PLANT_TYPE_1_FRAMES_ROOT , PLANT_TYPE_1_NUM_OF_FRAMES);
		shape.setTexture(&frames_texture[frame_index]);
	}
	else if(type == PLANT_TYPE_2)
	{
		type = PLANT_TYPE_2;
		width = PEASHOOTER_WIDTH;
		height = PEASHOOTER_HEIGHT;
		action_speed = plant_options[3];
		health = plant_options[1];
		shooter = true;
		producer = false;

		Load_Frames(PLANT_TYPE_2_FRAMES_ROOT , PLANT_TYPE_2_NUM_OF_FRAMES);
		shape.setTexture(&frames_texture[frame_index]);
	}
	else if(type == PLANT_TYPE_3)
	{
		type = PLANT_TYPE_3;
		width = SNOW_PEASHOOTER_WIDTH;
		height = SNOW_PEASHOOTER_HEIGHT;
		action_speed = plant_options[3];
		health = plant_options[1];
		shooter = true;
		producer = false;

		Load_Frames(PLANT_TYPE_3_FRAMES_ROOT , PLANT_TYPE_3_NUM_OF_FRAMES);
		shape.setTexture(&frames_texture[frame_index]);

	}
	else if(type == PLANT_TYPE_4)
	{
		type = PLANT_TYPE_4;
		width = WALNUT_WIDTH;
		height = WALNUT_HEIGHT;
		health = plant_options[1];
		shooter = false;
		producer = false;

		sf::Texture texture;
		if(!texture.loadFromFile(PLANT_TYPE_4_TEXTURE_PATH))
		{
			std:: cout << "error in loading Walnut texture !" << std::endl;
		}
		frames_texture.push_back(texture);

		if(!texture.loadFromFile(PLANT_TYPE_4_CRACKED1_TEXTURE_PATH))
		{
			std:: cout << "error in loading Walnut texture !" << std::endl;
		}
		frames_texture.push_back(texture);

		if(!texture.loadFromFile(PLANT_TYPE_4_CRACKED2_TEXTURE_PATH))
		{
			std:: cout << "error in loading Walnut texture !" << std::endl;
		}
		frames_texture.push_back(texture);
		shape.setTexture(&frames_texture[0]);
	}
	else if(type == PLANT_TYPE_5)
	{
		type = PLANT_TYPE_5;
		width = MELON_PULT_WIDTH;
		height = MELON_PULT_HEIGHT;
		action_speed = plant_options[3];
		health = plant_options[1];
		shooter = true;
		producer = false;

		Load_Frames(PLANT_TYPE_5_FRAMES_ROOT , PLANT_TYPE_5_NUM_OF_FRAMES);
		shape.setTexture(&frames_texture[frame_index]);
	}
	else if(type ==PLANT_TYPE_6)
	{
		type = PLANT_TYPE_6;
		width = KERNEL_PULT_WIDTH;
		height = KERNEL_PULT_WIDTH;
		action_speed = plant_options[3];
		health = plant_options[1];
		shooter = true;
		producer = false;

		Load_Frames(PLANT_TYPE_6_FRAMES_ROOT , PLANT_TYPE_6_NUM_OF_FRAMES);
		shape.setTexture(&frames_texture[frame_index]);
	}
}

void Plant::Load_Frames(std::string root_path , int num_of_frames)
{
	frame_rate = PLANT_FRAME_RATE;

	frame_index = 0;

	for(int i=0 ; i<num_of_frames ; i++)
	{
		sf::Texture texture;
		std::ostringstream path;
		path << root_path << i + 1 << ".png";
		if(!texture.loadFromFile(path.str()))
		{
			std:: cout << "error in loading plant frames texture !" << std::endl;
		}
		frames_texture.push_back(texture);
	}
}

void Plant::draw(sf::RenderWindow &window ,float current_global_time)
{
	if(type == PLANT_TYPE_4)
	{
		if(health == (plant_options[1]/2))
		{
			shape.setTexture(&frames_texture[1]);

		}
		else if(health == (plant_options[1]/4))
		{
			shape.setTexture(&frames_texture[2]);
		}
	}
	else
	{
		if(current_global_time - last_time_change_frame >= frame_rate)
		{
			frame_index ++;
			last_time_change_frame = current_global_time;
			if(frame_index == frames_texture.size())
				frame_index = 0;
			shape.setTexture(&frames_texture[frame_index]);	
		}
	}
	window.draw(shape);
}

void Plant::set_Square(std::string l,std::string s,float square_x_position,float square_y_position)
{
	square_id = s;
	line_id =l;
	shape.setSize(sf::Vector2f(width,height));
	if(type == PLANT_TYPE_5 || type == PLANT_TYPE_6)
		shape.setPosition(sf::Vector2f(square_x_position - 20,square_y_position-20));
	else
		shape.setPosition(sf::Vector2f(square_x_position,square_y_position));
}

Bullet* Plant::Shoot_Bullet(float current_global_time,sf::Vector2f target_position,float target_velocity)
{
	sf::Vector2f shape_position = shape.getPosition();
	Bullet* new_bullet = new Bullet(type,line_id,plant_options[4],plant_options[0],current_global_time,shape.getPosition(),target_position,target_velocity,shape_position.x,shape_position.y,width,height);
	last_reaction_time = current_global_time;
	return new_bullet;
}

Sun* Plant::Produce_Sun(float current_global_time)
{
	sf::Vector2f shape_position = shape.getPosition();
	Sun* new_sun = new Sun(0,shape_position.x,shape_position.y);
	last_reaction_time = current_global_time;
	return new_sun;
}

bool Plant::is_Act_Time(float current_global_time)
{
	if(current_global_time - last_reaction_time >= action_speed)
		return true;
	return false;
}


float Plant::get_x_Position()
{
	return shape.getPosition().x;
}

bool Plant::is_Producer()
{
	if(producer)
		return true;
	return false;
}


bool Plant::is_Shooter()
{
	if(shooter)
		return true;
	return false;
}

void Plant::getting_Damage(float zombie_damage)
{
	health -= zombie_damage;
}

float Plant::get_Width()
{
	return width;
}

bool Plant::is_Dead()
{
	if(health <=0 )
	{
		return true;
	}
	else
		return false;
}