#include "Button.h"
#include <SFML/Graphics.hpp>

/*
 ! @param window should be a sf::RenderWindow and the window you want your button to be displayed
*/
void Button::draw(sf::RenderWindow& window)
{
    window.draw(this->text);
    window.draw(this->shape);
}
/*
 ! @param str should be a std::string and it will be the string that will be displayed in the button
 ! @param char_size should be the size of the text
 ! @param text_fill_color should be the color of the inside of the text
 ! @param outline_thickness should be the thickness of the outline of the text
 ! @param text_outline_color should be the outline color of the text
*/
void Button::set_text(std::string str, float char_size, sf::Color text_fill_color, float outline_thickness, sf::Color text_outline_color)
{
    this->text.setString(str);
	this->text.setCharacterSize(char_size);
	this->text.setFillColor(text_fill_color);
	this->text.setOutlineThickness(outline_thickness);
	this->text.setOutlineColor(text_outline_color);
}