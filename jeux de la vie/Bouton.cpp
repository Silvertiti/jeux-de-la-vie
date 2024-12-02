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
    text.setFillColor(sf::Color::Black);
    text.setString(texte);

    sf::FloatRect textBounds = text.getLocalBounds(); 
    float padding = 10.f; 

    fond.setSize(sf::Vector2f(textBounds.width + 2 * padding, textBounds.height + 2 * padding));
    fond.setFillColor(sf::Color(100, 0, 200)); 
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


void Bouton::setBackgroundColor(sf::Color c) {                                  //pour definir une couleur perso au fond d'un bouto
    fond.setFillColor(sf::Color::Red);
}


void Bouton::afficher(sf::RenderWindow& window) {
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);

    if (fond.getGlobalBounds().contains(static_cast<float>(localPosition.x), static_cast<float>(localPosition.y))) {                      //static_cast<float> sert a transformer le type en float 
        fond.setFillColor(sf::Color(100, 100, 0, 100));                         //couleur bouton avec curseur 
    }
    else {
        fond.setFillColor(sf::Color(50, 50, 0, 50));                            //couleur bouton de base 
    }

    window.draw(fond);                                                          //affichage du fond pour le bouton 
    window.draw(text);                                                          //affichage du texte pour le bouton 
}


bool Bouton::estClique(const sf::Vector2i& mousePos) const { //pour implémentation avancer une iter
    return fond.getGlobalBounds().contains((mousePos.x), (mousePos.y));
}
