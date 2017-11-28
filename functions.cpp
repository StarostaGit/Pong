#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>


std::string convert2str (int number)
    {
        int current, mod = 1;
        std::string result = "";

        while (mod <= number || mod == 1)
            {
                mod *= 10;
                current = number % mod;
                current /= (mod/10);
                number -= current * (mod/10);
                result = char('0' + current) + result;
            }

        return result;
    }

int convert2int(const std::string &val)
    {
        int mod = 1;
        int result = 0;

        for (int i = val.length()-1; i >= 0; i--)
            {
                result += (val[i]-'0') * mod;
                mod *= 10;
            }

        return result;
    }

void calculateOrigin(sf::Text &t)
    {
        sf::FloatRect textBox = t.getLocalBounds();
        t.setOrigin(textBox.left + textBox.width/2, textBox.top + textBox.height/2);
    }

void addScore(sf::Text &t)
    {
        int points = convert2int(t.getString());
        points++;
        t.setString(convert2str(points));
    }
