#include "fenetrebonus.h"

FenetreTouche::FenetreTouche(const sf::Font& font)
    : fenetre(sf::VideoMode(800, 180), "Nouvelle Fenetre") {
    // Initialisation du texte
    TexteTouche.setFont(font);
    TexteTouche.setCharacterSize(35);
    TexteTouche.setFillColor(sf::Color::White);
    TexteTouche.setString("Menu de commande:\n I = Généré une case Immortelle\n M = Généré une case Infiniment Morte");
    TexteTouche.setPosition(50, 10);
}

void FenetreTouche::bouclePrincipaleTouche() {
    while (fenetre.isOpen()) {
        sf::Event event;
        while (fenetre.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                fenetre.close();
            }

            // Vous pouvez ajouter d'autres interactions ici si nécessaire
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                // Gestion du clic gauche
            }
        }

        fenetre.clear(sf::Color::Black); // Efface l'écran avec une couleur noire
        fenetre.draw(TexteTouche);  // Dessine le texte
        fenetre.display();              // Affiche le contenu de la fenêtre
    }
}

FenetreDesign::FenetreDesign(const sf::Font& font)
    : fenetreDesign(sf::VideoMode(800, 800), "Nouvelle Fenetre") {
    // Initialisation du texte
    TexteDesign.setFont(font);
    TexteDesign.setCharacterSize(35);
    TexteDesign.setFillColor(sf::Color::White);
    TexteDesign.setString("");
    TexteDesign.setPosition(50, 10);
}

void FenetreDesign::bouclePrincipaleDesign() {
    while (fenetreDesign.isOpen()) {
        sf::Event event;
        while (fenetreDesign.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                fenetreDesign.close();
            }

            // Vous pouvez ajouter d'autres interactions ici si nécessaire
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                // Gestion du clic gauche
            }
        }

        fenetreDesign.clear(sf::Color::Black); // Efface l'écran avec une couleur noire
        fenetreDesign.draw(TexteDesign);  // Dessine le texte
        fenetreDesign.display();              // Affiche le contenu de la fenêtre
    }
}

