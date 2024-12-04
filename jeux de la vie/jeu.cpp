#include "Jeu.h"
#include "slider.h"
#include <iostream>
#include <SFML/System.hpp>

Jeu::Jeu(const std::string& cheminFichier, int lignes, int colonnes, float cellSize)
    : lignes(lignes), colonnes(colonnes), cellSize(cellSize),
    fenetre(900, 800, "Jeu de la Vie - SFML") {
    grille = new Grille(lignes, colonnes);
    if (!grille->initialiserDepuisFichier(cheminFichier)) {
        std::cerr << "Erreur : Impossible de lire la grille." << std::endl;
        exit(-1);
    }
}

Jeu::~Jeu() {
    delete grille;
}


void Jeu::bouclePrincipale() {
    sf::Clock clock;

    while (fenetre.getWindow().isOpen()) {
        fenetre.gererEvenements(); // Capturer les événements

        delay = fenetre.getSlider().getValue();
        if (!fenetre.estPause()) {
            if (clock.getElapsedTime().asSeconds() >= delay) {
                grille->mettreAJour();
                clock.restart();
            }
        }

        fenetre.getWindow().clear(sf::Color::White);

        // dessiner lz grille
        grille->afficher(fenetre.getWindow(), cellSize);

        // affiche pause et sliders
        fenetre.getWindow().setView(fenetre.getWindow().getDefaultView());
        fenetre.afficherPause();

        fenetre.getWindow().display();
    }
}

//void Jeu::avancerIteration() {
    //grille->mettreAJour();
//}

//void Jeu::reculerIteration() {
    //grille->restaurerEtat();
//}