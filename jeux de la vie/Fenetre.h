#ifndef FENETRE_H
#define FENETRE_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Bouton.h"

class Fenetre {
private:
    sf::RenderWindow window;
    Bouton avancer;
    Bouton avancerRapide;

    sf::RectangleShape boutonPause;
    sf::Text textePause;
    sf::Font font;
    bool pause;

public:
    Fenetre(int largeur, int hauteur, const std::string& titre);
    sf::RenderWindow& getWindow();
    bool estPause() const;
    void gererEvenements();
    void afficherPause();
};

#endif