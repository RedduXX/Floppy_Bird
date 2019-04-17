#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include <sstream>

int main()
{
    sf::Font font;
    font.loadFromFile("Lato-regular.ttf");
    int points=0;
    sf::Text text;
    text.setFont(font);
    bool inGame = 1;
    std::stringstream temp_point;
    std::string points_string;
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(20, 400); // define the range
    int timer = 300;
    double radius = 20.f;
    double velocity = 0;
    double acceleration = 0;
    double gravity = 0.02;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape player(radius);
    std::vector <sf::RectangleShape> walls;
    std::vector <sf::RectangleShape> walls2;
    //walls.push_back(sf::RectangleShape(sf::Vector2f(50,distr(eng))));
    //walls2.push_back(sf::RectangleShape(sf::Vector2f(50,distr(eng))));
    //walls.back().setPosition(750,0);
    //walls2.back().setPosition(750,walls.back().getPosition().y+20);
    player.setPosition(sf::Vector2f(400-radius,20));
    player.setFillColor(sf::Color::Green);
    window.setFramerateLimit(200);
    srand(time(0));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Space&&inGame==1) velocity = -2;
            if (event.type == sf::Event::KeyPressed&&event.key.code==sf::Keyboard::R){
                points = 0;
                walls.clear();
                walls2.clear();
                player.setPosition(sf::Vector2f(400-radius,20));
                inGame = 1;

            }
        }
    velocity+=acceleration;

    player.move(sf::Vector2f(0,velocity));
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
    //   //velocity=-2;
    //}else{
    //    acceleration=0;
    //}
    if(player.getPosition().y<600-2*radius){
        velocity+=gravity;
        //acceleration=0;
    }
    else{
            velocity = 0;
            inGame = 0;
            //std::cout<<"You lost";
    }
    if(player.getPosition().y<=0) inGame = 0;
    if(timer==0){
        walls.push_back(sf::RectangleShape(sf::Vector2f(50,distr(eng))));
        walls.back().setPosition(750,0);
        walls2.push_back(sf::RectangleShape(sf::Vector2f(50,0)));
        walls2.back().setPosition(750,walls.back().getSize().y+200);
        walls2.back().setSize(sf::Vector2f(50,600-walls2.back().getPosition().y));
        timer = 300;

    }
    else{
        if(inGame==1) timer-= 1;
    }
    for(int i = 0; i<walls.size(); i++){
        if(walls[i].getPosition().x+50<0){
            walls.erase(walls.begin()+i);
        }
    }


    //std::cout<<timer<<std::endl;
    //std::cout<<"X: "<<player.getPosition().x<<" Y: "<<player.getPosition().y<<"Velocity: "<<velocity<<" Gravity: "<<gravity<<std::endl;
        window.clear();
        window.draw(player);
        for(int i=0;i<walls.size();i++){
            if(inGame==1) walls[i].move(-1,0);
            window.draw(walls[i]);
            if(player.getGlobalBounds().intersects(walls[i].getGlobalBounds())) inGame = 0;
            if(player.getPosition().x-20==walls[i].getPosition().x-25) points +=1;
        }
        for(int i=0;i<walls2.size();i++){
            if(inGame==1) walls2[i].move(-1,0);
            window.draw(walls2[i]);
            if(player.getGlobalBounds().intersects(walls2[i].getGlobalBounds())) inGame = 0;
        }
        temp_point << points;
        temp_point >> points_string;
        temp_point.clear();
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Red);
        text.setString(points_string);
        window.draw(text);
        window.draw(player);
        window.display();
    }

    return 0;
}
