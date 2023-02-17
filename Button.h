#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cctype>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

/*
 ! @param button_shape is a shape that IS A RECTANGLE
 ! @param button_text is a string that is a normal text with the @param button_font
 ! @param button_color is the color of the button, not the text, the text is automaticly set to black, its set to the shape!
*/
class Button
{
private:
    sf::RectangleShape button_shape;
    sf::Text button_text;
    sf::Font button_font;
    sf::Color button_color;
public:
    Button() = default;
    /*
     ! @param button_size will be 2 floats aka Vector2f that will define the size of the button
     ! @param button_pos will be 2 floats aka Vector2f that will define the position of the button
     ! @param font_name needs to be the name of the font that you want, and it should end at .ttf!!!
     ! @param button_color will be the @param this->button_color!!!
    */
    Button(sf::Vector2f button_size, sf::Vector2f button_pos, std::string font_name,
           sf::Color button_color)
    {
        this->button_shape.setPosition(button_pos);
        this->button_shape.setSize(button_size);
        if(this->button_font.loadFromFile(font_name))
        {
            std::cerr << "A problem with opening " << font_name << std::endl;
            system("pause");
            std::abort();
        }
        this->button_text.setFont(this->button_font);
        this->button_color = button_color;
        this->button_shape.setFillColor(button_color);
    }
    // * Getters *
    sf::RectangleShape get_shape() { return this->button_shape; }
    sf::Vector2f get_size() { return this->button_shape.getSize(); }
    sf::Vector2f get_position() { return this->button_shape.getPosition(); }
    sf::Text get_text() { return this->button_text; }
    std::string get_text_string() { return this->button_text.getString(); }
    sf::Font get_font() { return this->button_font; }
    sf::Color get_color() { return this->button_color; }
};

#endif