#include "Button.hpp"

Button::Button(const std::string& text, const sf::Font& font, unsigned int fontSize, sf::Vector2f size, sf::Color bg, sf::Color fg):Btext(font, text, fontSize){
    Btext.setFillColor(fg);

    Bshape.setSize(size);
    Bshape.setFillColor(bg);
}

void Button::setFont(const sf::Font& font, unsigned int fontSize){
    Btext.setFont(font);
    Btext.setCharacterSize(fontSize);

    centerText();
}

void Button::setText(const std::string& string){
    Btext.setString(string);

    centerText();
}
void Button::centerText(){
    sf::FloatRect textRect = Btext.getLocalBounds();
    sf::FloatRect shapeRect = Bshape.getGlobalBounds();
    float modifier = Btext.getCharacterSize()/3;

    float textX = shapeRect.position.x + (shapeRect.size.x - textRect.size.x) / 2.0f;
    float textY = shapeRect.position.y + (shapeRect.size.y - textRect.size.y - modifier) / 2.0f;

    Btext.setPosition({textX,textY});
}
void Button::setPosition(const sf::Vector2f& pos){

    Bshape.setPosition(pos);

    centerText();

}
void Button::setBackgroundColor(const sf::Color& color){
    Bshape.setFillColor(color);
}

void Button::drawTo(sf::RenderWindow& window){
    window.draw(Bshape);
    window.draw(Btext);
}
bool Button::isMouseOver(sf::RenderWindow& window){
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    return Bshape.getGlobalBounds().contains(mousePosF);
}


