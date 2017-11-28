#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "paddle.hpp"
#include "settings.h"


Paddle::Paddle(sf::Vector2f pos, float w, float h, sf::Keyboard::Key up, sf::Keyboard::Key down, Paddle::Label which)
    {
        setPosition(pos);
        setSize(sf::Vector2f(w, h));

        upKey = up;
        downKey = down;
        side = which;

        setFillColor(sf::Color::White);

        // move the point of origin to the center
        setOrigin(w/2, h/2);
    }

void Paddle::setVelocity(sf::Vector2f newVel)
    {
        vel = newVel;
    }

sf::Vector2f Paddle::getVelocity() const
    {
        return vel;
    }

void Paddle::applyPhysics()
    {
        vel.y = 0;

        if (sf::Keyboard::isKeyPressed(upKey))
            {
                vel.y = -PADDLE_SPEED;
                edge(upKey);
            }
        if (sf::Keyboard::isKeyPressed(downKey))
            {
                vel.y = PADDLE_SPEED;
                edge(downKey);
            }

        move(vel);
        update();
    }

void Paddle::edge(sf::Keyboard::Key key)
    {
        float y = getPosition().y;
        float offset = getSize().y / 2;

        if ((y + offset >= HEIGHT + Y_OFFSET) && (key == downKey))
            vel.y = 0;
        if ((y - offset <= Y_OFFSET) && (key == upKey))
            vel.y = 0;
    }
