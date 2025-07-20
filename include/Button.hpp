#pragma once
#include<SFML/Graphics.hpp>
#include<string>
#include<functional>

class Button{

    public:
        Button(const std::string& text, const sf::Font& font, unsigned int fontSize, sf::Vector2f size, sf::Color bg, sf::Color fg);

        void setFont(const sf::Font& font,  unsigned int fontSize);
        void setPosition(const sf::Vector2f& pos);
        void setBackgroundColor(const sf::Color& color);

        void centerText();
        void drawTo(sf::RenderWindow& window);
        bool isMouseOver(sf::RenderWindow& window);

    private:
        sf::Text Btext;
        sf::RectangleShape Bshape;

};