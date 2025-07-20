#include<SFML/Graphics.hpp>
#include<optional>
#include<string>
#include "Button.hpp"

int main(){
    sf::RenderWindow window(sf::VideoMode({800,600}) ,"iTower");
    window.setFramerateLimit(59);

    // FONT DECLARATION
    sf::Font Jetbrains,JetbrainsBold;
    if (!Jetbrains.openFromFile("../res/JetBrainsMonoNerdFontMono-Medium.ttf")) {
        return -1;
    }
    if (!JetbrainsBold.openFromFile("../res/JetBrainsMonoNerdFontMono-Bold.ttf")) {
        return -1;
    }
    // BUTTON AND SCORE INIT
    Button scorer("click me !!", Jetbrains, 15, {200,50}, sf::Color::Green, sf::Color::Black);
    scorer.setPosition({300,275});

    // text params font,char size,color,pos,content
    unsigned int score = 0, fontSize = 20;
    sf::Text scoreText(Jetbrains, "Score :: 0", fontSize);
    scoreText.setPosition({50,50});
    scoreText.setFillColor(sf::Color::Black);

    while(window.isOpen()){
        //close if close 
        while(const std::optional event =  window.pollEvent()){
            if(event->is<sf::Event::Closed>())  window.close();
        // onclick --> score ++
            if(const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>()){
                if(mouseButton->button == sf::Mouse::Button::Left){
                    if(scorer.isMouseOver(window)){
                        score++;
                    }
                }
            }
        }

        // on hover --> font change 
        if(scorer.isMouseOver(window)){
            scorer.setFont(JetbrainsBold, fontSize);
        }else{
            scorer.setFont(Jetbrains, fontSize);
        }

        // setting text
        scoreText.setString("Score :: " + std::to_string(score));


        window.clear(sf::Color::Red);
        //draw button and text
        scorer.drawTo(window);
        window.draw(scoreText);
        window.display();

    }
    return 0;
}