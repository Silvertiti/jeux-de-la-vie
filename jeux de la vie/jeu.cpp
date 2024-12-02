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

    float delay = fenetre.getSlider1().getCurrentValue(); // Ajout de la valeur du slider
    
    if (clock.getElapsedTime().asSeconds() >= delay) {
        grille->mettreAJour();
        clock.restart();
    }

    while (fenetre.getWindow().isOpen()) {
        fenetre.gererEvenements(); 

        
        float delay = fenetre.getSlider1().getCurrentValue();    // vitesse
        float zoomLevel = fenetre.getSlider2().getCurrentValue(); //  zoom

       
        sf::View view = fenetre.getWindow().getView();
        view.setSize(900 / zoomLevel, 800 / zoomLevel); 
        fenetre.getWindow().setView(view);

        if (!fenetre.estPause() && clock.getElapsedTime().asSeconds() >= delay) {
            grille->mettreAJour();
            clock.restart();
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