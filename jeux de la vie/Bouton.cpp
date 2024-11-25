#include "Bouton.h"
#include <iostream>
#include <SFML/Graphics.hpp>


Bouton::Bouton( const std::string& texte) {

    fond.setSize(sf::Vector2f(100, 100));
    fond.setFillColor(sf::Color());
    fond.setPosition(0, 0);


    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police." << std::endl;
        exit(-1);
    }

    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(0, 0);
    text.setString(texte);

}

Bouton::~Bouton()
{
}

void Bouton::setPosition(int x, int y)
{
	fond.setPosition(x, y);
	text.setPosition(x, y);
}

void Bouton::setBackgroundColor(sf::Color c)
{
	fond.setFillColor(c);
}

void Bouton::afficher(sf::RenderWindow& window) {

    sf::Vector2i localPosition = sf::Mouse::getPosition(window);

    if (fond.getGlobalBounds().contains(localPosition.x,localPosition.y)) {
		fond.setFillColor(sf::Color::Red);
    }
    else {
		fond.setFillColor(sf::Color::Green);
    }
	window.draw(fond);
	window.draw(text);
}