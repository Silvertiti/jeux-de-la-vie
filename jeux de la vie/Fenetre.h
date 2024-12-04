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
    Bouton activerClicBouton; // Nouveau bouton
    bool clicsGrilleActifs;   // Indique si les clics sur la grille sont actifs

    bool isDragging;               // Indique si l'utilisateur est en train de glisser
    sf::Vector2i dragStartPos;     // Position initiale de la souris au début du glissement
    sf::Vector2f initialViewPos;  // Position initiale de la vue



    //Grille* grille;

public:
    Fenetre(int largeur, int hauteur, const std::string& titre);
    sf::RenderWindow& getWindow();
    bool estPause();
    void gererEvenements(sf::Event& event);
    void afficherPause();
    Slider& getSlider2();
    Slider& getSlider1();
    bool sontClicsGrilleActifs() const; // Accesseur pour clicsGrilleActifs



    // void avancerIteration();
    //void reculerIteration();
};

#endif // FENETRE_H