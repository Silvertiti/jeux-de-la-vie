#ifndef FENETREBONUS_H
#define FENETREBONUS_H

#include <SFML/Graphics.hpp>
#include <string>

class FenetreTouche {
public:
    FenetreTouche(const sf::Font& font); // Constructeur qui prend une police en param�tre
    void bouclePrincipaleTouche();              // G�re la boucle d'affichage et les �v�nements

private:
    sf::RenderWindow fenetre;             // La fen�tre SFML
    sf::Text TexteTouche;             // Texte � afficher dans la fen�tre
};

class FenetreDesign {
public:
    FenetreDesign(const sf::Font& font); // Constructeur qui prend une police en param�tre
    void bouclePrincipaleDesign();              // G�re la boucle d'affichage et les �v�nements

private:
    sf::RenderWindow fenetreDesign;             // La fen�tre SFML
    sf::Text TexteDesign;             // Texte � afficher dans la fen�tre
};

#endif // NOUVELLEFENETRE_H
