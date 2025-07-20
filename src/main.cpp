#include<SFML/Graphics.hpp>
#include<optional>
#include<string>
#include "Button.hpp"
#include "Power.hpp"

struct GameState{
    long double score = 0;
    long double scorePerSecond = 0;
    long double clickValue = 1;
    long double upgradeCost = 10;
};

int main(){
    sf::RenderWindow window(sf::VideoMode({800,600}) ,"iTower");
    window.setFramerateLimit(59);

    //assigning a clock to keep track of score beyond fps
    sf::Clock gameTick;
    // instantiating Gamestate
    GameState gameState;

    // FONT DECLARATION
    sf::Font Jetbrains,JetbrainsBold;
    if (!Jetbrains.openFromFile("res/JetBrainsMonoNerdFontMono-Medium.ttf")) {
        return -1;
    }
    if (!JetbrainsBold.openFromFile("res/JetBrainsMonoNerdFontMono-Bold.ttf")) {
        return -1;
    }
    // BUTTON AND SCORE INIT
    Button scorer("click me !!", Jetbrains, 15, {200,50}, sf::Color::Green, sf::Color::Black);
    scorer.setPosition({300,275});

    Button upgradeButton("Upgrade", Jetbrains, 15, {200,50}, sf::Color::Blue, sf::Color::Black);
    upgradeButton.setPosition({300,375});

    // text params font,char size,color,pos,content
    unsigned int score = 0, fontSize = 20, level = 0;
    long double modifier = 1;
    sf::Text scoreText(Jetbrains, "Score :: 0", fontSize);
    scoreText.setPosition({50,50});
    scoreText.setFillColor(sf::Color::Black);
    
    while(window.isOpen()){
        // restarting the clock
        sf::Time tick = gameTick.restart();
        //close if close 
        while(const std::optional event =  window.pollEvent()){
            if(event->is<sf::Event::Closed>())  window.close();
        // onclick --> score ++
            if(const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>()){
                if(mouseButton->button == sf::Mouse::Button::Left){
                    //makes it so the the click score is added to the total score
                    if(scorer.isMouseOver(window)){
                        gameState.score += modifier * gameState.clickValue;
                    }
                    // first we reduce the cost of upgrade from the score then we increse the CPS and upgrade cost
                    else if (upgradeButton.isMouseOver(window) && gameState.score>gameState.upgradeCost){
                        gameState.score -= gameState.upgradeCost;
                        gameState.scorePerSecond += 0.2 * power(1.5,level);
                        gameState.upgradeCost *= 1.15 * power(2,level);
                        level++;
                        modifier *= power(2,level);
                    }
                }
            }
        }
        // adds passive score with the multiplier
        gameState.score += gameState.scorePerSecond * tick.asSeconds();
        // on hover --> font change 
        if(scorer.isMouseOver(window)){
            scorer.setFont(JetbrainsBold, fontSize);
        }else{
            scorer.setFont(Jetbrains, fontSize);
        }
        if(upgradeButton.isMouseOver(window) && gameState.score>gameState.upgradeCost){
            upgradeButton.setFont(JetbrainsBold, fontSize);
            upgradeButton.setString("Upgrade for "+ std::to_string(gameState.upgradeCost));
        }else{
            upgradeButton.setFont(Jetbrains, fontSize);
        }

        // setting text
        scoreText.setString("Score :: " + std::to_string(gameState.score));


        window.clear(sf::Color::Red);
        //draw button and text
        scorer.drawTo(window);
        upgradeButton.drawTo(window);
        window.draw(scoreText);
        window.display();

    }
    return 0;
}