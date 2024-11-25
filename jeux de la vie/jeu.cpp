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
	sf::Clock clock; // Pour mesurer le temps écoulé
    while (fenetre.getWindow().isOpen()) {
        fenetre.gererEvenements();

        if (!fenetre.estPause()) {
            grille->mettreAJour();
        }

        fenetre.getWindow().clear(sf::Color::White);
        grille->afficher(fenetre.getWindow(), cellSize);
        fenetre.afficherPause();
        fenetre.getWindow().display();


        sf::Time elapsed1 = clock.getElapsedTime();
        std::cout << elapsed1.asSeconds()  << std::endl;
        clock.restart();
    }
}
    