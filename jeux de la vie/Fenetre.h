#ifndef FENETRE_H
#define FENETRE_H

#include <SFML/Graphics.hpp>
#include <string>

class Fenetre {
private:
    sf::RenderWindow window;
    sf::RectangleShape boutonPause;
    sf::RectangleShape boutonAvancer;
    sf::Text textePause;
    sf::Text texteAvancer;
    sf::Font font;
    bool pause;
    bool avancer;

public:
    Fenetre(int largeur, int hauteur, const std::string& titre);
    sf::RenderWindow& getWindow();
    bool estPause() const;
    void gererEvenements();
    void afficherPause();
};

#endif
