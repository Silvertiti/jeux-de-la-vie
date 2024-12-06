#include "texte.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Texte::Texte(const std::string& texte) {

    if (!font.loadFromFile("arial.ttf")) {                                      // chargement de la police 
        std::cerr << "Erreur : Impossible de charger la police." << std::endl;
        exit(-1);
    }

    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setString(texte);
}


// Destructeur
Texte::~Texte() {}


void Texte::setPosition(int x, int y) {
	text.setPosition(x, y);
}

void Texte::setString(const std::string& nouveauTexte) {
    text.setString(nouveauTexte);
}


void Texte::afficher(sf::RenderWindow& window) {
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);

    window.draw(text);                                                          //affichage du texte pour le bouton 
}