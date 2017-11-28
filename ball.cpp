#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "ball.hpp"
#include "settings.h"
#include "paddle.hpp"
using namespace std;

#define PI 3.14159265

//static Paddle::Label lastHit = Unknown;

sf::Vector2f mapAngle(float val, float a, float b, float minAngle, float maxAngle, float x, float y)
    {
        val -= a;
        b -= a;
        float fraction = val / b;
        float range = maxAngle - minAngle;
        float newAngle = fraction * range;
        newAngle += minAngle;
        float magnitude = hypot(x, y);

        sf::Vector2f result;
        result.x = magnitude * cos(newAngle);
        result.y = magnitude * sin(newAngle);

        return result;
    }

Ball::Ball(sf::Vector2f pos, float r)
    {
        setPosition(pos);
        setRadius(r);

        setFillColor(sf::Color::White);

        // move the point of origin to the center
        setOrigin(r, r);

        // set random velocity
        srand(time(NULL));
        float speed = rand() % BALL_SPEED_RANGE + BALL_MIN_SPEED;
        float angle = rand() % 21 - 10;
        angle *= (PI / 180);
        vel.x = speed * cos(angle);
        vel.y = speed * sin(angle);
        if (rand() % 2)
            vel.x *= -1;
    }

void Ball::setVelocity(sf::Vector2f newVel)
    {
        vel = newVel;
    }

sf::Vector2f Ball::getVelocity() const
    {
        return vel;
    }

void Ball::applyPhysics()
    {
        edge();
        move(vel);
        update();
    }

void Ball::edge()
    {
        float y = getPosition().y;
        float r = getRadius();

        if ((y-r <= Y_OFFSET) || (y+r >= HEIGHT + Y_OFFSET))
            {
                vel.y *= -1;
            }
    }

void Ball::reset(Paddle::Label winner)
    {
        setPosition(WIDTH/2 + X_OFFSET, HEIGHT/2 + Y_OFFSET);

        float speed = rand() % BALL_SPEED_RANGE + BALL_MIN_SPEED;
        float angle = rand() % 21 - 10;
        angle *= (PI / 180);
        vel.x = speed * cos(angle);
        vel.y = speed * sin(angle);
        if (winner == Paddle::Left)
            vel.x *= -1;
    }

void Ball::hit(const Paddle &p)
    {
        float minX = p.getGlobalBounds().left;
        float minY = p.getGlobalBounds().top;
        float maxX = p.getGlobalBounds().left + p.getGlobalBounds().width;
        float maxY = p.getGlobalBounds().top + p.getGlobalBounds().height;
        float nearestX = max(minX, min(getPosition().x, maxX));
        float nearestY = max(minY, min(getPosition().y, maxY));

        // collision check
        float deltaX = getPosition().x - nearestX;
        float deltaY = getPosition().y - nearestY;
        bool collision = (deltaX * deltaX + deltaY * deltaY) < (getRadius() * getRadius());

        if (collision)
            {
                vel = mapAngle(nearestY, minY, maxY, -PI/4, PI/4, vel.x, vel.y);

                if (p.side == Paddle::Right)
                    {
                        vel.x = abs(vel.x) * -1;
                        //lastHit = p.side;
                    }
                else if (p.side == Paddle::Left)
                    {
                        vel.x = abs(vel.x);
                        //lastHit = p.side;
                    }
            }
    }
