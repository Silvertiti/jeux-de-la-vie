#include "Fichier.h"
#include "Jeu.h"
#include <iostream>

int main() {
    std::string cheminFichier = "C:\\Users\\laara\\OneDrive\\Bureau\\test github 2\\test.txt";
    int lignes = 0, colonnes = 0;

    if (!Fichier::lireDimensions(cheminFichier, lignes, colonnes)) {
        std::cerr << "Erreur : Impossible de lire les dimensions." << std::endl;
        return -1;
    }

    Jeu jeu(cheminFichier, lignes, colonnes, 20.0f);
    jeu.bouclePrincipale();

    return 0;
}
