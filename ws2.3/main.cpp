#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <set>
#include <ctime>
#include <cassert>
#include <random>

struct Ball
{
    sf::CircleShape ball;
    sf::Vector2f speed;
};

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    // Создаём псевдо-устройство для получения случайного зерна.
    const unsigned seed = unsigned(std::time(nullptr));
    // Получаем случайное зерно последовательности
    generator.engine.seed(seed);
}

unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    // Проверяем корректность аргументов
    assert(minValue < maxValue);

    // Создаём распределение
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);

    // Вычисляем псевдослучайное число: вызовем распределение как функцию,
    //  передав генератор произвольных целых чисел как аргумент.
    return distribution(generator.engine);
}

float getRandomFloat(PRNG &generator, float minValue, float maxValue)
{
    // Проверяем корректность аргументов
    assert(minValue < maxValue);

    // Создаём распределение
    std::uniform_real_distribution<float> distribution(minValue, maxValue);

    // Вычисляем псевдослучайное число: вызовем распределение как функцию,
    //  передав генератор произвольных целых чисел как аргумент.
    return distribution(generator.engine);
}

sf::Vector2f getSpeed(PRNG &generator)
{
    float minSpeed = -500.f;
    float maxSpeed = 500.f;

    return {getRandomFloat(generator, minSpeed, maxSpeed), getRandomFloat(generator, minSpeed, maxSpeed)};
}
//скалярное произведение векторов
double calculateScalarProduct(const sf::Vector2f &i, const sf::Vector2f &j)
{
    sf::Vector2f temp;
    temp.x = i.x * j.x;
    temp.y = i.y + j.y;
    float total = (temp.x + temp.y);
    return total;
}

float getVectorLenght(const sf::Vector2f delta)
{
    const float lenght = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
    return lenght;
}

void setNewSpeed(Ball &i, Ball &j)
{

    // разницы позиций и скоростей первого и второго
    sf::Vector2f deltaPosition = i.ball.getPosition() - j.ball.getPosition();
    sf::Vector2f deltaSpeed = i.speed - j.speed;
    // разницы позиций и скоростей второго и первого
    sf::Vector2f deltaPosition2 = j.ball.getPosition() - i.ball.getPosition();
    sf::Vector2f deltaSpeed2 = j.speed - i.speed;

    double temp = calculateScalarProduct(deltaSpeed, deltaPosition) / pow(getVectorLenght(deltaPosition), 2);
    double temp2 = calculateScalarProduct(deltaSpeed2, deltaPosition2) / pow(getVectorLenght(deltaPosition2), 2);

    sf::Vector2f t = {float(temp * deltaPosition.x), float(temp * deltaPosition.y)};
    sf::Vector2f t2 = {float(temp * deltaPosition2.x), float(temp2 * deltaPosition2.y)};

    sf::Vector2f ttemp = i.speed - t;
    sf::Vector2f ttemp2 = j.speed - t2;

    i.speed = ttemp;
    j.speed = ttemp2;
}

// рассчитать скорость после столкновения
void setSpeed(std::vector<Ball> &structContent, const int WINDOW_WIDTH, const int WINDOW_HEIGHT)
{

    for (size_t i = 0; i < structContent.size(); ++i)
    {
        for (size_t j = i + 1; j < structContent.size(); ++j)
        {
            //вектор - разница между центрами шаров
            sf::Vector2f delta = structContent[i].ball.getPosition() - structContent[j].ball.getPosition();

            // найдем длину этого вектора
            int lenghtDelta = getVectorLenght(delta);

            // вычисляем момент столкновения
            int distanseBeetweenBalls = structContent[i].ball.getRadius() + structContent[j].ball.getRadius();
            if (lenghtDelta <= distanseBeetweenBalls)
            {
                //рассчитать скорость шаров после столкновения
                setNewSpeed(structContent[i], structContent[j]);
            }
        }
    }

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
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Running balls with random initiation speed", sf::Style::Default,
                            settings);

    sf::Clock clock;
    constexpr unsigned ballsCount = 5;
    std::vector<Ball> balls(ballsCount);
    const float dt = clock.restart().asSeconds();
    PRNG generator;
    initGenerator(generator);

    balls[0].ball.setRadius(25);
    balls[0].ball.setPosition({(100), 100});
    balls[0].speed = getSpeed(generator);
    balls[0].ball.setFillColor({255, 200, 120});

    balls[1].ball.setRadius(30);
    balls[1].ball.setPosition({222, 333});
    balls[1].speed = getSpeed(generator);
    balls[1].ball.setFillColor({100, 200, 115});

    balls[2].ball.setRadius(35);
    balls[2].ball.setPosition({322, 153});
    balls[2].speed = getSpeed(generator);
    balls[2].ball.setFillColor({100, 2, 200});

    balls[3].ball.setRadius(32);
    balls[3].ball.setPosition({422, 183});
    balls[3].speed = getSpeed(generator);
    balls[3].ball.setFillColor({55, 56, 55});

    balls[4].ball.setRadius(40);
    balls[4].ball.setPosition({122, 193});
    balls[4].speed = getSpeed(generator);
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