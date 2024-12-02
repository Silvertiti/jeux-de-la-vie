#ifndef FENETRE_H
#define FENETRE_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Bouton.h"
#include "Slider.h"

class Fenetre {
private:
    sf::RenderWindow window;
    Bouton avancer;
     
    
    Slider slider1; // vitesse
    Slider slider2; // zoom

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
    const Slider& getSlider2() const;
    const Slider& getSlider1() const;
};

#endif // FENETRE_H