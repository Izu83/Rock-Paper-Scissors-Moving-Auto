#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>

std::vector<sf::Sprite> rocks;
std::vector<sf::Sprite> papers;
std::vector<sf::Sprite> scissors;

void move(sf::Sprite &moving_sprite, std::vector<sf::Sprite> &target_sprites, float speed)
{
	if (target_sprites.size() == 0)
	{
		return;
	}
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
	sf::Vector2f moving_sprite_pos = moving_sprite.getPosition();	
	sf::Vector2f direction = closest_pos - moving_sprite_pos;
	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (distance > speed)
	{
		direction = direction / distance * speed;
	}
	moving_sprite.move(direction);
}

// You kill the second one
void check_collision(std::vector<sf::Sprite>& master_sprites, std::vector<sf::Sprite>& slave_sprites, sf::Texture& master_texture, sf::Texture& slave_texture)
{
	for (size_t i = 0; i < master_sprites.size(); i++)
	{
		for (size_t j = 0; j < slave_sprites.size(); j++)
		{
			if (master_sprites.at(i).getGlobalBounds().intersects(slave_sprites.at(j).getGlobalBounds()))
			{
				auto prev_pos = slave_sprites.at(j).getPosition();
				slave_sprites.erase(slave_sprites.begin() + j);
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
	// Rendering window
	sf::RenderWindow window(sf::VideoMode(700, 900), "Rock, Paper, Scissors (RPS)");
	window.setFramerateLimit(60);

	// Rock texture
	sf::Texture rock_texture;
	if (!rock_texture.loadFromFile("rock.png"))
	{
		std::cerr << "There is a problem with opening rock.png" << std::endl;
		system("pause");
		return 1;
	}

	// Paper texture
	sf::Texture paper_texture;
	if (!paper_texture.loadFromFile("paper.png"))
	{
		std::cerr << "There is a problem with opening paper.png" << std::endl;
		system("pause");
		return 1;
	}

	// Scissors texture
	sf::Texture scissor_texture;
	if (!scissor_texture.loadFromFile("scissors.png"))
	{
		std::cerr << "There is a problem with opening scissors.png" << std::endl;
		system("pause");
		return 1;
	}

	// Vectors of sprites

	// Main loop
	while (window.isOpen())
	{
		// Catching events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::R)
				{
					sf::Sprite rock(rock_texture);
					sf::Vector2i mousePos = sf::Mouse::getPosition(window) - sf::Vector2i(32, 32);
					sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
					rock.setPosition(worldPos); 
					rocks.push_back(rock);
				}
				if (event.key.code == sf::Keyboard::S)
				{
					sf::Sprite scissor(scissor_texture);
					sf::Vector2i mousePos = sf::Mouse::getPosition(window) - sf::Vector2i(32, 32);
					sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
					scissor.setPosition(worldPos);
					scissors.push_back(scissor);
				}
				if (event.key.code == sf::Keyboard::P)
				{
					sf::Sprite paper(paper_texture);
					sf::Vector2i mousePos = sf::Mouse::getPosition(window) - sf::Vector2i(32, 32);
					sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
					paper.setPosition(worldPos);
					papers.push_back(paper);
				}
			}
		}

		check_collision(rocks, scissors, rock_texture, scissor_texture);
		check_collision(papers, rocks, paper_texture, rock_texture);
		check_collision(scissors, papers, scissor_texture, paper_texture);

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
		

		window.clear(sf::Color::White);

		for (auto rock : rocks) { window.draw(rock); }
		for (auto paper : papers) { window.draw(paper); }
		for (auto scissor : scissors) { window.draw(scissor); }
		
		window.display();
	}
}