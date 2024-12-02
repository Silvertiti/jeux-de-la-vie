#ifndef FENETRE_H
#define FENETRE_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Bouton.h"
#include "Slider.h"
#include "grille.h"

class Fenetre {
private:
    sf::RenderWindow window;
    Bouton avancer;
    Bouton reculer;
    
    Slider slider1; // vitesse
    Slider slider2; // zoom

    sf::RectangleShape boutonPause; 
    sf::RectangleShape affichagePause;
    sf::Text textePause;
    sf::Font font;
    bool pause;

    //Grille* grille;

public:
    Fenetre(int largeur, int hauteur, const std::string& titre);
    sf::RenderWindow& getWindow();
    bool estPause();
    void gererEvenements();
    void afficherPause();
    Slider& getSlider2() ;
    Slider& getSlider1() ;
   
   // void avancerIteration();
   //void reculerIteration();
};

#endif // FENETRE_H