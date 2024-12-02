#include "Fichier.h"
#include <fstream>
#include <iostream>
#include <string>

bool Fichier::lireDimensions(const std::string& cheminFichier, int& lignes, int& colonnes) {
    std::ifstream fichier(cheminFichier);
    if (!fichier.is_open()) return false;

    if (!(fichier >> lignes >> colonnes)) return false;

    return true;
}

bool Fichier::lireGrille(const std::string& cheminFichier, bool* tableau, int lignes, int colonnes) {
    std::ifstream fichier(cheminFichier);
    if (!fichier.is_open()) return false;

    // i gnorer les deux premières lignes
    std::string ligne;
    for (int i = 0; i < 2; ++i) getline(fichier, ligne);

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            int valeur;
            if (!(fichier >> valeur)) return false;
            tableau[i * colonnes + j] = valeur;
        }
    }

    return true;
}
