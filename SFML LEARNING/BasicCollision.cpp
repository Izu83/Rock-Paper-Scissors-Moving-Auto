#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

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
	std::vector<sf::Sprite> rocks;
	std::vector<sf::Sprite> papers;
	std::vector<sf::Sprite> scissors;

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
					sf::Vector2i mousePos = sf::Mouse::getPosition(window) - sf::Vector2i(16, 16);
					sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
					rock.setPosition(worldPos); 
					rocks.push_back(rock);
				}
				if (event.key.code == sf::Keyboard::S)
				{
					sf::Sprite scissor(scissor_texture);
					sf::Vector2i mousePos = sf::Mouse::getPosition(window) - sf::Vector2i(16, 16);
					sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
					scissor.setPosition(worldPos);
					scissors.push_back(scissor);
				}
				if (event.key.code == sf::Keyboard::P)
				{
					sf::Sprite paper(paper_texture);
					sf::Vector2i mousePos = sf::Mouse::getPosition(window) - sf::Vector2i(16, 16);
					sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
					paper.setPosition(worldPos);
					papers.push_back(paper);
				}
			}
		}

		window.clear(sf::Color::White);

		for (auto rock : rocks) { window.draw(rock); }
		for (auto paper : papers) { window.draw(paper); }
		for (auto scissor : scissors) { window.draw(scissor); }
		
		window.display();
	}
}