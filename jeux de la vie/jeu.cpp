#include "Jeu.h"
#include <iostream>
#include <SFML/System.hpp>

Jeu::Jeu(const std::string& cheminFichier, int lignes, int colonnes, float cellSize)
    : lignes(lignes), colonnes(colonnes), cellSize(cellSize), fenetre(colonnes* cellSize, lignes* cellSize + 50, "Jeu de la Vie - SFML") {
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
    float delay = 0.9f;  //c la val de la vitesse

    while (fenetre.getWindow().isOpen()) {
        fenetre.gererEvenements();


        if (!fenetre.estPause()) {

            if (clock.getElapsedTime().asSeconds() >= delay) {
                grille->mettreAJour();
                clock.restart();
            }
        }


        fenetre.getWindow().clear(sf::Color::White);
        grille->afficher(fenetre.getWindow(), cellSize);
        fenetre.afficherPause();
        fenetre.getWindow().display();


        //sf::Time elapsed = clock.getElapsedTime();
        //std::cout << "Temps : " << elapsed.asSeconds() << " secondes" << std::endl;
    }
}