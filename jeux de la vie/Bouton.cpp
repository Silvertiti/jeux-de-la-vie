#include "Bouton.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Bouton::Bouton(const std::string& texte) {

    // Charger la police
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police." << std::endl;
        exit(-1);
    }

    text.setFont(font);
    text.setCharacterSize(20); 
    text.setFillColor(sf::Color::White);
    text.setString(texte);

    sf::FloatRect textBounds = text.getLocalBounds();
    float padding = 10.f; 

    fond.setSize(sf::Vector2f(textBounds.width + 2 * padding, textBounds.height + 2 * padding));
    fond.setFillColor(sf::Color(100, 100, 200)); 
    fond.setPosition(0, 0);

    text.setPosition(fond.getPosition().x + padding, fond.getPosition().y + padding - textBounds.top);
}

// Destructeur
Bouton::~Bouton() {}

void Bouton::setPosition(int x, int y) {
    fond.setPosition(x, y);
    text.setPosition(x + fond.getSize().x / 2.f - text.getLocalBounds().width / 2.f,
        y + fond.getSize().y / 2.f - text.getLocalBounds().height / 2.f);
}

void Bouton::setBackgroundColor(sf::Color c) {
    fond.setFillColor(c);
}

void Bouton::afficher(sf::RenderWindow& window) {
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);

    if (fond.getGlobalBounds().contains(static_cast<float>(localPosition.x), static_cast<float>(localPosition.y))) {
        fond.setFillColor(sf::Color::Yellow);
    }
    else {
        fond.setFillColor(sf::Color::Green);
    }

    window.draw(fond);
    window.draw(text);
}

bool Bouton::estClique(const sf::Vector2i& mousePos) const {
    return fond.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}
