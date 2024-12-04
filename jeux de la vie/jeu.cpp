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
        sf::Event event;

        while (fenetre.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                fenetre.getWindow().close();
            }

            // Gestion des �v�nements li�s � la fen�tre
            fenetre.gererEvenements(event);

            // Permet les clics sur la grille seulement si clicsGrilleActifs est true
            if (fenetre.sontClicsGrilleActifs()) {
                grille->changerCase(fenetre.getWindow(), cellSize, event);
            }
        }

        // R�cup�re la valeur des sliders pour r�gler la vitesse et le zoom
        float delay = fenetre.getSlider1().getCurrentValue();
        float zoomLevel = fenetre.getSlider2().getCurrentValue();

        // Met � jour la vue pour g�rer le zoom
        sf::View view = fenetre.getWindow().getView();
        view.setSize(900 / zoomLevel, 800 / zoomLevel);
        fenetre.getWindow().setView(view);

        // Met � jour la grille si le jeu n'est pas en pause et que le d�lai est �coul�
        if (!fenetre.estPause() && clock.getElapsedTime().asSeconds() >= delay) {
            grille->mettreAJour();
            clock.restart();
        }

        // Dessine la fen�tre et ses composants
        fenetre.getWindow().clear(sf::Color::White);
        grille->afficher(fenetre.getWindow(), cellSize);
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