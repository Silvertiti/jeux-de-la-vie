#include "Fichier.h"
#include <fstream>
#include <iostream>
#include <string>

bool Fichier::lireDimensions(const std::string cheminFichier, int& lignes, int& colonnes) {
    std::ifstream fichier(cheminFichier);
    if (!fichier.is_open()) return false;

    if (fichier >> lignes >> colonnes) {
        // Vérification que les dimensions sont positives
        if (lignes <= 0 || colonnes <= 0) {
            std::cout << "Erreur: Les dimensions doivent etre des entiers positifs." << std::endl;
            return false;
        }
        return true;
    }
    else {
        std::cout << "Le fichier s'est bien ouvert mais les dimensions n'ont pas pu etre lues : verifier les dans votre fichier." << std::endl;
        return false;
    }
}


bool Fichier::lireGrille(const std::string cheminFichier, bool* tableau, int lignes, int colonnes) {
    std::ifstream fichier(cheminFichier);
    if (!fichier.is_open()) return false;

    // Ignorer les deux premières lignes
    std::string ligne;
    for (int i = 0; i < 2; ++i) getline(fichier, ligne);

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            int symbole{};
            if (!(fichier >> symbole)) {
                std::cout << "Erreur: Impossible de lire un entier à la position (" << i << "," << j << ")." << std::endl;
                return false;
            }

            // Vérifier que la valeur est soit 0, soit 1
            if (symbole != 0 || symbole != 1) {
                std::cout << "Erreur: Valeur invalide" << std::endl;
                return false;
            }

            tableau[i * colonnes + j] = symbole;
        }
    }

    return true;
}