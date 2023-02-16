#include <SFML/Graphics.hpp>

/*
 ! @fn constructor Font, Text, Shape
 ! @param font should be a sf::Font
 ! @param text should be a sf::Text
 ! @param shape should be a sf::Shape
*/
class Button
{
public:
	sf::Font font;
	sf::Text text;
	sf::RectangleShape shape;
	Button(sf::Font font, sf::Text text, sf::RectangleShape shape)
	 : font(font), text(text), shape(shape)
	{}
	Button(sf::Font font, std::string text, sf::RectangleShape shape)
	 : font(font), shape(shape)
	{ this->text.setString(text); }

};