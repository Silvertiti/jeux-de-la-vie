#include "Jeu.h"
#include <iostream>
#include <SFML/System.hpp>

Jeu::Jeu(const std::string& cheminFichier, int lignes, int colonnes, float cellSize)
    : lignes(lignes), colonnes(colonnes), cellSize(cellSize),
    fenetre(1000, 900, "Jeu de la Vie - SFML") {
    grille = new Grille(lignes, colonnes);
    if (!grille->initialiserDepuisFichier(cheminFichier)) {
        std::cerr << "Erreur : Impossible de lire la grille." << std::endl;
        exit(-1);
    }
}

void Jeu::avancerIteration() {
    grille->mettreAJour(); // Met à jour la grille pour une seule itération
}

void Jeu::reculerIteration() {
    if (!grille->revenirEnArriere()) {
        std::cerr << "Impossible de reculer : aucun état précédent disponible." << std::endl;
    }
}

Jeu::~Jeu() {
    delete grille;
}

void Jeu::bouclePrincipale() {
    sf::Clock clock;

    while (fenetre.getWindow().isOpen()) {
        sf::Event event;

        while (fenetre.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                fenetre.getWindow().close();
            }

            // Gestion des événements liés à la fenêtre
            fenetre.gererEvenements(event, *grille, cellSize);
        }

        // Récupère la valeur des sliders pour régler la vitesse et le zoom
        float delay = fenetre.getSlider1().getCurrentValeur();
        cellSize = fenetre.getSlider2().getCurrentValeur();




        // Met à jour la grille si le jeu n'est pas en pause et que le délai est écoulé
        if (!fenetre.estPause() && clock.getElapsedTime().asSeconds() >= delay) {
            grille->mettreAJour();
            clock.restart();
        }
        fenetre.getWindow().clear(sf::Color::White);
        grille->afficher(fenetre.getWindow(), cellSize, fenetre.getGrilleOffset());
        fenetre.afficherPause(*grille, cellSize); // Appelé après le dessin de la grille
        fenetre.getWindow().setView(fenetre.getWindow().getDefaultView());
        fenetre.getWindow().display();

    }
}
