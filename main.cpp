#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "ball.hpp"
#include "settings.h"
#include "paddle.hpp"
#include "functions.hpp"


int main()
    {
        // setting the game window
        sf::VideoMode current = sf::VideoMode::getDesktopMode();
        sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(WIDTH + 2*X_OFFSET, HEIGHT + 2*Y_OFFSET, current.bitsPerPixel), "Pong", sf::Style::Titlebar | sf::Style::Close);
        window->setFramerateLimit(60);
        window->setPosition(sf::Vector2i(current.width/2 - WIDTH/2 - X_OFFSET, current.height/2 - HEIGHT/2 - Y_OFFSET - 25));

        // some graphic features
        sf::RectangleShape *frame = new sf::RectangleShape(sf::Vector2f(WIDTH, HEIGHT));
        frame->setOutlineColor(sf::Color::White);
        frame->setFillColor(sf::Color::Transparent);
        frame->setOutlineThickness(15);
        frame->setPosition(X_OFFSET, Y_OFFSET);

        sf::VertexArray middleLine(sf::LinesStrip, 2);
        middleLine[0].position = sf::Vector2f(WIDTH/2 + X_OFFSET, Y_OFFSET);
        middleLine[1].position = sf::Vector2f(WIDTH/2 + X_OFFSET, HEIGHT + Y_OFFSET);
        middleLine[0].color = sf::Color::White;
        middleLine[0].color.a = 120;
        middleLine[1].color = sf::Color::White;
        middleLine[1].color.a = 120;

        sf::Font *scoreFont = new sf::Font;
        sf::Text *leftScore, *rightScore;
        leftScore = new sf::Text;
        rightScore = new sf::Text;
        if (!scoreFont->loadFromFile("Fonts/half_bold_pixel-7.ttf"))
            throw "Font not loaded correctly";
        leftScore->setFont(*scoreFont);
        rightScore->setFont(*scoreFont);
        leftScore->setString("0");
        rightScore->setString("0");
        leftScore->setCharacterSize(50);
        rightScore->setCharacterSize(50);
        calculateOrigin(*leftScore);
        calculateOrigin(*rightScore);
        leftScore->setPosition(X_OFFSET + WIDTH/3, Y_OFFSET + 50);
        rightScore->setPosition(X_OFFSET + 2*WIDTH/3, Y_OFFSET + 50);


        // initialize game elements
        Ball *ball = new Ball(sf::Vector2f(WIDTH/2 + X_OFFSET, HEIGHT/2 + Y_OFFSET), BALL_RADIUS);
        Paddle *left = new Paddle(sf::Vector2f(SPACE_BEFORE_PADDLES + X_OFFSET, HEIGHT/2 + Y_OFFSET), PADDLE_WIDTH, PADDLE_HEIGHT, sf::Keyboard::W, sf::Keyboard::S, Paddle::Left);
        Paddle *right = new Paddle(sf::Vector2f(WIDTH - SPACE_BEFORE_PADDLES + X_OFFSET, HEIGHT/2 + Y_OFFSET), PADDLE_WIDTH, PADDLE_HEIGHT, sf::Keyboard::Up, sf::Keyboard::Down, Paddle::Right);

        while (window->isOpen())
            {
                sf::Event event;
                while (window->pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            window->close();

                        if (event.type == sf::Event::KeyPressed)
                            {
                                if (event.key.code == sf::Keyboard::Escape)
                                    window->close();
                            }
                    }

                left->applyPhysics();
                right->applyPhysics();
                ball->applyPhysics();

                if ((ball->getPosition().x >= WIDTH + X_OFFSET) || (ball->getPosition().x <= X_OFFSET))
                    {
                        Paddle::Label winner = ball->getPosition().x <= X_OFFSET ? Paddle::Right : Paddle::Left;
                        ball->reset(winner);
                        if (winner == Paddle::Right)
                            {
                                addScore(*rightScore);
                                calculateOrigin(*rightScore);
                            }
                        else
                            {
                                addScore(*leftScore);
                                calculateOrigin(*leftScore);
                            }
                    }

                ball->hit(*left);
                ball->hit(*right);

                window->clear(sf::Color::Black);

                window->draw(*frame);
                window->draw(middleLine);
                window->draw(*leftScore);
                window->draw(*rightScore);
                window->draw(*ball);
                window->draw(*left);
                window->draw(*right);

                window->display();
            }

        return 0;
    }
