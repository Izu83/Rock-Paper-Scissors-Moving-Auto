#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <map>


// ? ? ? MAYBE DELETE THIS ? ? ?
std::vector<sf::CircleShape> circles;
// ? ? ? MAYBE DELETE THIS ? ? ?

/*
 	! RULES:
 ? 1. Rock kills scissors, rock goes after scissors. ?
 ? 2. Scissors kills paper, scissors goes after paper. ? 
 ? 3. Paper kills rock, paper goes after rock. ?

*/

// * Function prototypes *
void running_away(sf::Sprite&, std::vector<sf::Sprite>&, float);
void move(sf::Sprite&,std::vector<sf::Sprite>&,float);
void check_collision(std::vector<sf::Sprite>&, std::vector<sf::Sprite>&, sf::Texture&, sf::Texture&);
void check_collision_window(sf::RenderWindow&, std::vector<sf::Sprite>&);

std::vector<sf::Sprite> rocks;
std::vector<sf::Sprite> papers;
std::vector<sf::Sprite> scissors;
// * ^ Vectors are needed for displaying and moving, checking co llision, and pretty much everything *

/*
 ! On the first you put the window,
 ! on the second (final) you put the sprite you want to check the collision for
*/
void check_collision_window(sf::RenderWindow& window, sf::Sprite& sprite)
{
	if (sprite.getPosition().x > window.getSize().x - 32)
		sprite.move(-1.f, 0.f);
	if (sprite.getPosition().x < 0.f)
		sprite.move(1.f, 0.f);
	if (sprite.getPosition().y > window.getSize().y - 32)
		sprite.move(0.f, -1.f);
	if (sprite.getPosition().y < 0.f)
		sprite.move(0.f, 1.f);
}

/*
 ! On the first you put the sprite you want to run away,
 ! on the second you put the type of sprites you want the moving_sprite to run away from,
 ! on the third you put the speed 
*/
void running_away(sf::Sprite& moving_sprite, std::vector<sf::Sprite>& enemy_sprites, float speed)
{
	float radius = 25.0f;
	sf::CircleShape circle(radius);
	circle.setPosition(moving_sprite.getPosition().x + moving_sprite.getGlobalBounds().width / 2 - radius,
					   moving_sprite.getPosition().y + moving_sprite.getGlobalBounds().height / 2 - radius);
	
	for (auto it = enemy_sprites.begin(); it != enemy_sprites.end(); it++)
	{
		if (circle.getGlobalBounds().intersects((*it).getGlobalBounds()))
		{
			sf::Vector2f direction = (*it).getPosition() - moving_sprite.getPosition();
			float length = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
			direction = -direction / length;
			direction = direction * speed;
			moving_sprite.move(direction);
			break;
		}
	}
}

/*
 ! You need to put the sprite you want to move in the left !
 ! and the sprite you want to move to the right !
 ! the last ons is the speed you want the moving_sprite to move with !
*/
void move(sf::Sprite& moving_sprite, std::vector<sf::Sprite>& target_sprites, float speed)
{
	// * This avoids exception DividingByZero *
	if (target_sprites.size() == 0)
	{
		return;
	}

	// * Finds the closest sprite in the vector *
	sf::Vector2f closest_pos = target_sprites.at(0).getPosition();
	float closest_distance = std::numeric_limits<float>::max();
	for (auto it = target_sprites.begin(); it != target_sprites.end(); it++)
	{
		sf::Vector2f temp_pos = (*it).getPosition();
		float temp_distance = std::sqrt(std::pow(temp_pos.x - moving_sprite.getPosition().x, 2) + std::pow(temp_pos.y - moving_sprite.getPosition().y, 2));
		if (temp_distance < closest_distance)
		{
			closest_pos = temp_pos;
			closest_distance = temp_distance;
		}
	}

	// * Finding the direction *
	sf::Vector2f moving_sprite_pos = moving_sprite.getPosition();	
	sf::Vector2f direction = closest_pos - moving_sprite_pos;
	if (closest_distance > speed)
	{
		direction = direction / closest_distance * speed;
	}

	// * Moving the sprite *
	moving_sprite.move(direction);
}

/*
 ! Pass the stronger sprites in the first parameter !
 ! Pass the weaker sprites in the seconds parameter !
 ! Pass the stronger sprites texture in the third paramater !
 ! Pass the weaker sprites texture in the fourth parameter !
*/
void check_collision(std::vector<sf::Sprite>& master_sprites, std::vector<sf::Sprite>& weaker_sprites, sf::Texture& master_texture, sf::Texture& slave_texture)
{
	for (size_t i = 0; i < master_sprites.size(); i++)
	{
		for (size_t j = 0; j < weaker_sprites.size(); j++)
		{
			// * Checking for collision *
			if (master_sprites.at(i).getGlobalBounds().intersects(weaker_sprites.at(j).getGlobalBounds()))
			{
				// * Replacing the weaker sprite with a stronger(master) sprite *
				// ** We just get the position of the weaker and erase it from the vector **
				// ** After that we are making a new_sprite that has the master_texture **
				// ** We are setting the new_sprite's position to the already erased weaker sprite's position **
				// ** We push it back in the vector **
				auto prev_pos = weaker_sprites.at(j).getPosition();
				weaker_sprites.erase(weaker_sprites.begin() + j);
				sf::Sprite new_sprite(master_texture);
				new_sprite.setPosition(prev_pos);
				master_sprites.push_back(new_sprite);
				break;
			}
		}
	}
}


int main()
{
    // * Seed RNG *
    srand(time(NULL));

	// * Rendering the window *
	sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(videoMode, "Rock, Paper, Scissors (RPS)", sf::Style::Default);
	window.setFramerateLimit(60);
	bool isFullscreen{ false };

	// * Loading the rock texture *
	sf::Texture rock_texture;
	if (!rock_texture.loadFromFile("rock.png"))
	{
		std::cerr << "There is a problem with opening rock.png" << std::endl;
		system("pause");
		return 1;
	}

	// * Loading the paper texture *
	sf::Texture paper_texture;
	if (!paper_texture.loadFromFile("paper.png"))
	{
		std::cerr << "There is a problem with opening paper.png" << std::endl;
		system("pause");
		return 1;
	}

	// * Loading the scissor texture *
	sf::Texture scissor_texture;
	if (!scissor_texture.loadFromFile("scissors.png"))
	{
		std::cerr << "There is a problem with opening scissors.png" << std::endl;
		system("pause");
		return 1;
	}

	// * Main game loop *
	while (window.isOpen())
	{
		// * Catching events *
		sf::Event event;
		while (window.pollEvent(event))
		{
			// * If the window is closed you close the application *
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			// * If the user presses a key *
			if (event.type == sf::Event::KeyPressed)
			{
				// * Spawning a rock at mouse position *
				if (event.key.code == sf::Keyboard::R)
				{
					sf::Sprite rock(rock_texture);
					sf::Vector2i mousePos = sf::Mouse::getPosition(window) - sf::Vector2i(32, 32);
					sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
					rock.setPosition(worldPos); 
					rocks.push_back(rock);
				}
				// * Spawning a scissor at mouse position *
				if (event.key.code == sf::Keyboard::S)
				{
					sf::Sprite scissor(scissor_texture);
					sf::Vector2i mousePos = sf::Mouse::getPosition(window) - sf::Vector2i(32, 32);
					sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
					scissor.setPosition(worldPos);
					scissors.push_back(scissor);
				}
				// * Spawning a paper at mouse position *
				if (event.key.code == sf::Keyboard::P)
				{
					sf::Sprite paper(paper_texture);
					sf::Vector2i mousePos = sf::Mouse::getPosition(window) - sf::Vector2i(32, 32);
					sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
					paper.setPosition(worldPos);
					papers.push_back(paper);
				}
				// * Checking for F11 to make fullscreen *
				if (event.key.code == sf::Keyboard::F11)
				{
					if (event.key.code == sf::Keyboard::F11)
					{
						isFullscreen = !isFullscreen;
						if (isFullscreen)
						{
							window.create(videoMode, "SFML Window", sf::Style::Fullscreen);
							window.setFramerateLimit(60);
						}
						else
						{
							window.create(videoMode, "SFML Window", sf::Style::Default);
							window.setFramerateLimit(60);
						}
					}
				}
				// * Checking for Escape to close the window *
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
		}
		
		// * Checking collision for the sprites and the window
		for (auto it = rocks.begin() ; it != rocks.end() ; it++)
		{
			check_collision_window(window, *it);
		}
		for (auto it = papers.begin() ; it!= papers.end() ; it++)
		{
			check_collision_window(window, *it);
		}
		for (auto it = scissors.begin() ; it!= scissors.end() ; it++)
		{
			check_collision_window(window, *it);
		}

		// * Checking for running away with the rules *
		for (auto it = rocks.begin() ; it != rocks.end() ; ++it)
		{
			running_away(*it, papers, 1.f);
		}
		for (auto it = papers.begin() ; it!= papers.end() ; ++it)
		{
			running_away(*it, scissors, 1.f);
		}
		for (auto it = scissors.begin() ; it!= scissors.end() ; ++it)
		{
			running_away(*it, rocks, 1.f);
		}

		// * Checking collision for rocks, papers, scissors with the rules *
		check_collision(rocks, scissors, rock_texture, scissor_texture);
		check_collision(papers, rocks, paper_texture, rock_texture);
		check_collision(scissors, papers, scissor_texture, paper_texture);

		// * Moving every vector *
		for (auto it = rocks.begin() ; it != rocks.end() ; it++)
		{
			move(*it, scissors, 1);
		}
		for (auto it = papers.begin() ; it != papers.end() ; it++)
		{
			move(*it, rocks, 1);
		}
		for (auto it = scissors.begin() ; it != scissors.end() ; it++)
		{
			move(*it, papers, 1);
		}
		
		// * Making the background to be light grey *
		sf::Color color{ 181,181,181 }; 
		window.clear(color);

		// * Displaying vectors *
		for (auto rock : rocks) { window.draw(rock); }
		for (auto paper : papers) { window.draw(paper); }
		for (auto scissor : scissors) { window.draw(scissor); }
		for (auto circle : circles) { window.draw(circle); }
		
		// * Clearing circles because it causes
		// * real big preformance issues *
		circles.clear();

		window.display();
	}
}