#ifndef FENETREBONUS_H
#define FENETREBONUS_H

#include <SFML/Graphics.hpp>
#include <string>

class FenetreTouche {
public:
    FenetreTouche(const sf::Font& font); // Constructeur qui prend une police en paramètre
    void bouclePrincipaleTouche();              // Gère la boucle d'affichage et les événements

private:
    sf::RenderWindow fenetre;             // La fenêtre SFML
    sf::Text TexteTouche;             // Texte à afficher dans la fenêtre
};

class FenetreDesign {
public:
    FenetreDesign(const sf::Font& font); // Constructeur qui prend une police en paramètre
    void bouclePrincipaleDesign();              // Gère la boucle d'affichage et les événements

private:
    sf::RenderWindow fenetreDesign;             // La fenêtre SFML
    sf::Text TexteDesign;             // Texte à afficher dans la fenêtre
};

#endif // NOUVELLEFENETRE_H
