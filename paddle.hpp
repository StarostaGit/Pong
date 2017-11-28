#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


class Paddle : public sf::RectangleShape
{

    private:

        sf::Vector2f vel;
        sf::Keyboard::Key upKey;
        sf::Keyboard::Key downKey;

    public:

        enum Label {Left = 0, Right,};

        Label side;

        Paddle(sf::Vector2f pos, float w, float h, sf::Keyboard::Key up, sf::Keyboard::Key down, Label which);

        void setVelocity(sf::Vector2f newVel);
        sf::Vector2f getVelocity() const;

        void applyPhysics();
        void edge(sf::Keyboard::Key key);
};

#endif // PADDLE_H
