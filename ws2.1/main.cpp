#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>

struct Ball
{
    sf::CircleShape ball;
    sf::Vector2f speed;
};

void setSpeed(std::vector<Ball> &structContent, const int WINDOW_WIDTH, const int WINDOW_HEIGHT)
{
    for (size_t i = 0; i < structContent.size(); ++i)
    {
        if ((structContent[i].ball.getPosition().x + 2 * structContent[i].ball.getRadius() >= WINDOW_WIDTH) && (structContent[i].speed.x > 0))
        {
            structContent[i].speed.x = -structContent[i].speed.x;
        }
        if ((structContent[i].ball.getPosition().x < 0) && (structContent[i].speed.x < 0))
        {
            structContent[i].speed.x = -structContent[i].speed.x;
        }
        if ((structContent[i].ball.getPosition().y + 2 * structContent[i].ball.getRadius() >= WINDOW_HEIGHT) && (structContent[i].speed.y > 0))
        {
            structContent[i].speed.y = -structContent[i].speed.y;
        }
        if ((structContent[i].ball.getPosition().y < 0) && (structContent[i].speed.y < 0))
        {
            structContent[i].speed.y = -structContent[i].speed.y;
        }
    }
}

void updateBallPosition(std::vector<Ball> &structContent, const float dt)
{
    for (size_t i = 0; i < structContent.size(); ++i)
    {
        sf::Vector2f position = structContent[i].ball.getPosition();
        position = position + structContent[i].speed * dt;
        structContent[i].ball.setPosition(position);
    }
}

void draw(sf::RenderWindow &window, std::vector<Ball> structContent)
{
    window.draw(structContent[0].ball);
    window.draw(structContent[1].ball);
    window.draw(structContent[2].ball);
    window.draw(structContent[3].ball);
    window.draw(structContent[4].ball);
}

int main()
{
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const int ANTIALIASING_LEVEL = 8;

    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Running balls", sf::Style::Default,
                            settings);

    sf::Clock clock;
    constexpr unsigned ballsCount = 5;
    std::vector<Ball> balls(ballsCount);
    const float dt = clock.restart().asSeconds();

    balls[0].ball.setRadius(25);
    balls[0].ball.setPosition({(100), 100});
    balls[0].speed = {1115.f, -715.f};
    balls[0].ball.setFillColor({255, 200, 120});

    balls[1].ball.setRadius(30);
    balls[1].ball.setPosition({222, 333});
    balls[1].speed = {305.f, 3225.f};
    balls[1].ball.setFillColor({100, 200, 115});

    balls[2].ball.setRadius(35);
    balls[2].ball.setPosition({322, 153});
    balls[2].speed = {1635.f, -1635.f};
    balls[2].ball.setFillColor({100, 2, 200});

    balls[3].ball.setRadius(32);
    balls[3].ball.setPosition({422, 183});
    balls[3].speed = {1115.f, -2945.f};
    balls[3].ball.setFillColor({55, 56, 55});

    balls[4].ball.setRadius(40);
    balls[4].ball.setPosition({122, 193});
    balls[4].speed = {-655.f, 525.f};
    balls[4].ball.setFillColor({23, 200, 15});

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
        window.clear();
        setSpeed(balls, WINDOW_WIDTH, WINDOW_HEIGHT);
        updateBallPosition(balls, dt);
        draw(window, balls);
        window.display();
    }
}