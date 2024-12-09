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
    grille->mettreAJour(); // Met � jour la grille pour une seule it�ration
}

void Jeu::reculerIteration() {
    if (!grille->revenirEnArriere()) {
        std::cerr << "Impossible de reculer : aucun �tat pr�c�dent disponible." << std::endl;
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
            fenetre.gererEvenements(event, *grille, cellSize);
        }

        // R�cup�re la valeur des sliders pour r�gler la vitesse et le zoom
        float delay = fenetre.getSlider1().getCurrentValeur();
        cellSize = fenetre.getSlider2().getCurrentValeur();




        // Met � jour la grille si le jeu n'est pas en pause et que le d�lai est �coul�
        if (!fenetre.estPause() && clock.getElapsedTime().asSeconds() >= delay) {
            grille->mettreAJour();
            clock.restart();
        }
        fenetre.getWindow().clear(sf::Color::White);
        grille->afficher(fenetre.getWindow(), cellSize, fenetre.getGrilleOffset());
        fenetre.afficherPause(*grille, cellSize); // Appel� apr�s le dessin de la grille
        fenetre.getWindow().setView(fenetre.getWindow().getDefaultView());
        fenetre.getWindow().display();

    }
}
#include <fstream>
#include <iostream>
#include <cstring>

void Jeu::boucleConsole() {
    std::cout << "Vous avez choisi la boucle console.\n\nDemarrage de la simulation.\n";

    int iterationschoisis;
    std::cout << "Entrez le nombre d'iterations: ";
    std::cin >> iterationschoisis;
    if (iterationschoisis > 0 && iterationschoisis < 1000000) {
        // Ouvrir le fichier de log pour �crire les �tats des it�rations
        std::ofstream fichierLog("C:\\Users\\laara\\OneDrive\\Bureau\\test github3\\log.txt");
        if (!fichierLog.is_open()) {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier de log." << std::endl;
            return;
        }

        // Effectuer les it�rations
        for (int iteration = 0; iteration < iterationschoisis; ++iteration) {
            // Afficher l'it�ration en cours
            std::cout << "Iteration " << iteration + 1 << " :\n";


            // Afficher l'�tat de la grille
            for (int i = 0; i < lignes; ++i) {
                for (int j = 0; j < colonnes; ++j) {
                    std::cout << (grille->getTableau()[i * colonnes + j] ? "1" : "0") << " ";
                }
                std::cout << "\n";  // Nouvelle ligne pour chaque ligne de la grille
            }

            std::cout << "\n";  // S�paration entre les it�rations
        }

        fichierLog.close();  // Fermer le fichier log


    }
}
