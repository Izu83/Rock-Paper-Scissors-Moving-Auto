#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(700, 900), "Rock, Paper, Scissors (RPS)");
	window.setFramerateLimit(60);

	sf::Texture rock_texture;
	if (!rock_texture.loadFromFile("rock.png"))
	{
		std::cerr << "There is a problem with opening rock.png" << std::endl;
		system("pause");
		return 1;
	}

	sf::Sprite rock;
	rock.setTexture(rock_texture);
	rock.setPosition(350, 450);

	sf::Texture paper_texture;
	if (!paper_texture.loadFromFile("paper.png"))
	{
		std::cerr << "There is a problem with opening paper.png" << std::endl;
		system("pause");
		return 1;
	}

	sf::Sprite paper;
	paper.setTexture(paper_texture);
	paper.setPosition(400, 500);

	sf::Texture scissors_texture;
	if (!scissors_texture.loadFromFile("scissors.png"))
	{
		std::cerr << "There is a problem with opening scissors.png" << std::endl;
		system("pause");
		return 1;
	}

	sf::Sprite scissors;
	scissors.setTexture(scissors_texture);
	scissors.setPosition(300, 500);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::White);

		window.draw(rock);
		window.draw(paper);
		window.draw(scissors);

		window.display();
	}
}