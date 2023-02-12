#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>

/*
 	! RULES:
 ? 1. Rock kills scissors, rock goes after scissors. 
 ? 2. Scissors kills paper, scissors goes after paper. 
 ? 3. Paper kills rock, paper goes after rock.

*/

std::vector<sf::Sprite> rocks;
std::vector<sf::Sprite> papers;
std::vector<sf::Sprite> scissors;
// * ^ Vectors are needed for displaying and moving, checking collision, and pretty much everything

/*
 ! You need to put the sprite you want to move in the left
 ! and the sprite you want to move to the right
 ! the last ons is the speed you want the moving_sprite to move with
*/
void move(sf::Sprite &moving_sprite, std::vector<sf::Sprite> &target_sprites, float speed)
{
	// * This avoids exception DividingByZero
	if (target_sprites.size() == 0)
	{
		return;
	}
	// * Finds the closest sprite in the vector
	// ! DOESNT WORK
	// TODO: Fix it!
	sf::Vector2f closest_pos = target_sprites.at(0).getPosition();
	for (auto it = target_sprites.begin(); it != target_sprites.end(); it++)
	{
		sf::Vector2f temp_pos = (*it).getPosition();
		if (closest_pos.x <= temp_pos.x && closest_pos.y <= temp_pos.y)
		{
			closest_pos.x = temp_pos.x;
			closest_pos.y = temp_pos.y;
		}
	}
	// TODO: Fix ^!
	// * Finding the direction
	sf::Vector2f moving_sprite_pos = moving_sprite.getPosition();	
	sf::Vector2f direction = closest_pos - moving_sprite_pos;
	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (distance > speed)
	{
		direction = direction / distance * speed;
	}
	// * Moving the sprite
	moving_sprite.move(direction);
}

/*
 ! Pass the stronger sprites in the first parameter
 ! Pass the weaker sprites in the seconds parameter
 ! Pass the stronger sprites texture in the third paramater
 ! Pass the weaker sprites texture in the fourth parameter
*/
void check_collision(std::vector<sf::Sprite>& master_sprites, std::vector<sf::Sprite>& weaker_sprites, sf::Texture& master_texture, sf::Texture& slave_texture)
{
	for (size_t i = 0; i < master_sprites.size(); i++)
	{
		for (size_t j = 0; j < weaker_sprites.size(); j++)
		{
			// * Checking for collision
			if (master_sprites.at(i).getGlobalBounds().intersects(weaker_sprites.at(j).getGlobalBounds()))
			{
				// * Replacing the weaker sprite with a stronger(master) sprite
				// ** We just get the position of the weaker and erase it from the vector
				// ** After that we are making a new_sprite that has the master_texture
				// ** We are setting the new_sprite's position to the already erased weaker sprite's position
				// ** We push it back in the vector
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
	// * Rendering the window
	sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(videoMode, "Rock, Paper, Scissors (RPS)", sf::Style::Default);
	window.setFramerateLimit(60);
	bool isFullscreen{ false };

	// * Loading the rock texture
	sf::Texture rock_texture;
	if (!rock_texture.loadFromFile("rock.png"))
	{
		std::cerr << "There is a problem with opening rock.png" << std::endl;
		system("pause");
		return 1;
	}

	// * Loading the paper texture
	sf::Texture paper_texture;
	if (!paper_texture.loadFromFile("paper.png"))
	{
		std::cerr << "There is a problem with opening paper.png" << std::endl;
		system("pause");
		return 1;
	}

	// * Loading the scissor texture
	sf::Texture scissor_texture;
	if (!scissor_texture.loadFromFile("scissors.png"))
	{
		std::cerr << "There is a problem with opening scissors.png" << std::endl;
		system("pause");
		return 1;
	}

	// * Main game loop
	while (window.isOpen())
	{
		// * Catching events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// * If the window is closed you close the application
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			// * If the user presses a key
			if (event.type == sf::Event::KeyPressed)
			{
				// * Spawning a rock at mouse position
				if (event.key.code == sf::Keyboard::R)
				{
					sf::Sprite rock(rock_texture);
					sf::Vector2i mousePos = sf::Mouse::getPosition(window) - sf::Vector2i(32, 32);
					sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
					rock.setPosition(worldPos); 
					rocks.push_back(rock);
				}
				// * Spawning a scissor at mouse position
				if (event.key.code == sf::Keyboard::S)
				{
					sf::Sprite scissor(scissor_texture);
					sf::Vector2i mousePos = sf::Mouse::getPosition(window) - sf::Vector2i(32, 32);
					sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
					scissor.setPosition(worldPos);
					scissors.push_back(scissor);
				}
				// * Spawning a paper at mouse position
				if (event.key.code == sf::Keyboard::P)
				{
					sf::Sprite paper(paper_texture);
					sf::Vector2i mousePos = sf::Mouse::getPosition(window) - sf::Vector2i(32, 32);
					sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
					paper.setPosition(worldPos);
					papers.push_back(paper);
				}
				// * Checking for F11 to make fullscreen
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
				// * Checking for Escape to close the window
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
		}
		
		// * Checking collision for rocks, papers, scissors with the rules
		check_collision(rocks, scissors, rock_texture, scissor_texture);
		check_collision(papers, rocks, paper_texture, rock_texture);
		check_collision(scissors, papers, scissor_texture, paper_texture);

		// * Moving every vector
		for (auto it = rocks.begin(); it != rocks.end(); it++)
		{
			move(*it, scissors, 1);
		}
		for (auto it = papers.begin(); it != papers.end(); it++)
		{
			move(*it, rocks, 1);
		}
		for (auto it = scissors.begin(); it != scissors.end(); it++)
		{
			move(*it, papers, 1);
		}
		
		// * Making the background to be light grey
		sf::Color color{ 181,181,181 }; 
		window.clear(color);

		// * Displaying vectors
		for (auto rock : rocks) { window.draw(rock); }
		for (auto paper : papers) { window.draw(paper); }
		for (auto scissor : scissors) { window.draw(scissor); }
		
		window.display();
	}
}