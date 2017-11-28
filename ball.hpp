#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "paddle.hpp"


class Ball : public sf::CircleShape
{
    private:

        sf::Vector2f vel; // velocity of the ball


    public:

        Ball(sf::Vector2f pos, float r);

        void setVelocity(sf::Vector2f newVel);
        sf::Vector2f getVelocity() const;

        void applyPhysics();
        void edge();
        void reset(Paddle::Label winner);
        void hit(const Paddle &p);
};

#endif // BALL_H
