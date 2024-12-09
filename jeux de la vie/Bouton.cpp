#include "Bouton.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Bouton::Bouton(const std::string& texte) {


    if (!font.loadFromFile("arial.ttf")) {                                      // chargement de la police 
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

void Bouton::setString(const std::string& nouveauTexte) {
    text.setString(nouveauTexte);

    // Recalculer la taille et la position du fond pour s'adapter au nouveau texte
    sf::FloatRect textBounds = text.getLocalBounds();
    float padding = 10.f;

    fond.setSize(sf::Vector2f(textBounds.width + 2 * padding, textBounds.height + 2 * padding));
    text.setPosition(fond.getPosition().x + padding, fond.getPosition().y + padding - textBounds.top);
}

void Bouton::setBackGroundColorClear() {                                  //pour definir une couleur perso au fond d'un bouto
    fond.setFillColor(sf::Color(0,0,0,0));
}


void Bouton::afficher(sf::RenderWindow& window) {
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);

    window.draw(fond);                                                          //affichage du fond pour le bouton 
    window.draw(text);                                                          //affichage du texte pour le bouton 
}

void Bouton::mettreAJour(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // Vérifier si la souris est au-dessus du bouton
    if (fond.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
        fond.setFillColor(sf::Color(64, 64, 64, 255)); // Couleur plus claire
    }
    else {
        fond.setFillColor(sf::Color(32, 32, 32, 255));
    }
}



bool Bouton::estClique(const sf::Vector2i& mousePos) const { //pour implémentation avancer une iter
    return fond.getGlobalBounds().contains((mousePos.x), (mousePos.y));
}
