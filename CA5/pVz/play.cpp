#include "gameplay.h"

void Play(sf::RenderWindow &window)
{
	GamePlay gameplay(window.getSize().x,window.getSize().y);

	std::vector<float> attacks_options;
	std::vector<float> falling_sun_options;
	
	Read_From_File(attacks_options,ATTACKS_OPTION_PATH);
	Read_From_File(falling_sun_options,FALLING_SUN_OPTION_PATH);

	sf::Clock global_time;
	sf::Clock wave_periodicity;
	sf::Clock generate_zombie_periodicity;
	sf::Clock falling_sun_periodicity;

	sf::Music soundtrack;
	sf::Sound zombie_intro_sound;
	sf::SoundBuffer buffer;


	Load_Music(soundtrack,MAIN_SOUNDTRACK_PATH);
	Load_Sound(zombie_intro_sound,buffer,ZOMBIE_INTRO_SOUND_PATH);


	soundtrack.play();


	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			gameplay.Move_Mouse(window);
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				gameplay.Card_Selection(window,global_time.getElapsedTime().asSeconds());
			}
			if(event.type == sf::Event::Closed)
				window.close();
		}

		if(global_time.getElapsedTime().asSeconds() > attacks_options[1] && global_time.getElapsedTime().asSeconds() < attacks_options[1] + 0.02)
			zombie_intro_sound.play();

		if(global_time.getElapsedTime().asSeconds() > attacks_options[1] )
		{
			if(global_time.getElapsedTime().asSeconds() <= attacks_options[0] + 1)
			{
				float periodicity = attacks_options[1] / attacks_options[2];

				if(generate_zombie_periodicity.getElapsedTime().asSeconds() >=  periodicity)
				{
					gameplay.Generate_Zombie();
					generate_zombie_periodicity.restart();
					if(wave_periodicity.getElapsedTime().asSeconds() >= attacks_options[1])
					{
						attacks_options[2] += attacks_options[3];
						wave_periodicity.restart();
					}
				}
			}
			else 
			{
				if(!gameplay.is_Any_Zombie_Left())
				{
					soundtrack.stop();	
					Win(window);
					break;
				}
			}
		}

		if(falling_sun_periodicity.getElapsedTime().asSeconds() >= falling_sun_options[1])
		{
			std::srand(time(0));
			float sun_x_position = FALLING_SUN_PRIMARY_X_POSITION  + (std::rand() % window.getSize().x - (2*SQUARE_LENGTH));
			float sun_y_position = FALLING_SUN_PRIMARY_Y_POSITION;
			gameplay.Generate_Falling_Sun(sun_x_position,sun_y_position,falling_sun_options[0]);
			falling_sun_periodicity.restart();
		}

		if(gameplay.GameOver(HOUSE_X_POSITION))
		{
			sf::Sound dead_sound;
			Load_Sound(dead_sound,buffer,DEAD_SOUND_PATH);
			dead_sound.play();
			soundtrack.stop();	
			gameover(window);
			break;
		}

		gameplay.Generate_Produced_Sun(global_time.getElapsedTime().asSeconds());
		gameplay.Break_Ice(global_time.getElapsedTime().asSeconds());
		gameplay.Sort_Zombies();
		gameplay.Plants_Fire(global_time.getElapsedTime().asSeconds());
		gameplay.Move_Zombies();
		gameplay.Move_Bullets(global_time.getElapsedTime().asSeconds());
		gameplay.Move_Falling_Suns();
		gameplay.Bullet_Impact(global_time.getElapsedTime().asSeconds());
		gameplay.Zombies_Death();
		gameplay.Plants_Death();
		gameplay.Kill_Plants(global_time.getElapsedTime().asSeconds());
		window.clear();
		gameplay.draw(window,global_time.getElapsedTime().asSeconds());
		window.display();
	}
}