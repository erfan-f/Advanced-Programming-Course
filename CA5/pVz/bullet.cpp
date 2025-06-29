#include "bullet.h"

Bullet::Bullet(std::string plant_name,std::string l_i,float v,float d,float current_global_time,sf::Vector2f p_p,sf::Vector2f t_p,float t_v,float x_plant,float y_plant,float plant_width , float plant_height)
{
	shoot_time = current_global_time;
	target_velocity = t_v;
	target_position = t_p;
	plant_position = p_p;

	if(plant_name == PLANT_TYPE_2)
	{
		if(!bullet_texture.loadFromFile(BULLET_TYPE_1_TEXTURE_PATH))
		{
			std:: cout << "error in loading bullet texture !" << std::endl;
		}

		line_id = l_i;
		shape.setRadius(BULLET_TYPE_1_SIZE);
		shape.setTexture(&bullet_texture);
		shape.setPosition(sf::Vector2f(x_plant + plant_width - 15 , y_plant + 0.2 * plant_height - 10));
		velocity = v;
		damage = d;
		type = BULLET_TYPE_1;

	}
	else if(plant_name == PLANT_TYPE_3)
	{
		if(!bullet_texture.loadFromFile(BULLET_TYPE_2_TEXTURE_PATH))
		{
			std:: cout << "error in loading bullet texture !" << std::endl;
		}
		line_id = l_i;
		shape.setRadius(BULLET_TYPE_2_SIZE);
		shape.setTexture(&bullet_texture);
		shape.setPosition(sf::Vector2f(x_plant + plant_width - 15 , y_plant + 0.2 * plant_height - 10));	
		velocity = v;
		damage = d;
		type = BULLET_TYPE_2;
	}
	else if(plant_name == PLANT_TYPE_5)
	{
		if(!bullet_texture.loadFromFile(BULLET_TYPE_3_TEXTURE_PATH))
		{
			std:: cout << "error in loading bullet texture !" << std::endl;
		}
		shape.setRadius(BULLET_TYPE_3_SIZE);
		shape.setTexture(&bullet_texture);
		shape.setPosition(sf::Vector2f(x_plant +10 , y_plant +10));	

		line_id = l_i;
		velocity = v;
		horizontal_velocity = v;
		vertical_velocity = -v;
		damage = d;
		type = BULLET_TYPE_3;
	}
	else if(plant_name == PLANT_TYPE_6)
	{
		if(!bullet_texture.loadFromFile(BULLET_TYPE_4_TEXTURE_PATH))
		{
			std:: cout << "error in loading bullet texture !" << std::endl;
		}
		shape.setRadius(BULLET_TYPE_4_SIZE);
		shape.setTexture(&bullet_texture);
		shape.setPosition(sf::Vector2f(x_plant +10 , y_plant +10));	

		line_id = l_i;
		velocity = v;
		horizontal_velocity = v;
		vertical_velocity = -v;
		damage = d;
		type = BULLET_TYPE_4;
	}

}

void Bullet::Move(float current_global_time)
{
	float fly_time = (target_position.x - plant_position.x - 150)/(target_velocity + horizontal_velocity);
	float a = (2*velocity)/fly_time;
	if(type == BULLET_TYPE_3 || type == BULLET_TYPE_4)
	{
		shape.move(horizontal_velocity,vertical_velocity);

		float dt = current_global_time - shoot_time;
		float dvy = a * dt;
		vertical_velocity += dvy;
		if(vertical_velocity == velocity)
		{
			horizontal_velocity = 0;
			vertical_velocity = 0;
		}
	}
	else
		shape.move(velocity,0);
}

void Bullet::draw(sf::RenderWindow &window)
{
	window.draw(shape);
}

sf::Vector2f Bullet::get_Position()
{
	return shape.getPosition(); 
}

std::string Bullet::get_Type()
{
	return type;
}

float Bullet::get_damage()
{
	return damage;
}
