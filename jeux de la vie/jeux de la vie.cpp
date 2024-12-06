#include "Fichier.h"
#include "Jeu.h"
#include <iostream>

int Max = 600000;

int main() {
    std::string cheminFichier = "C:\\Users\\methe\\source\\repos\\jeux de la vie\\test.txt";    
    int lignes = 0, colonnes = 0;

    if (!Fichier::lireDimensions(cheminFichier, lignes, colonnes)) {
        std::cerr << "Erreur : Impossible de lire les dimensions depuis " << cheminFichier << "." << std::endl;
        return -1;
    }

    if (lignes * colonnes > Max) {
        std::cerr << "Erreur : Les dimensions sont trop grandes : "
            << Max << " cellules." << std::endl;
        return -1;
    }

    std::cout << "Dimensions lues : " << lignes << " x " << colonnes << std::endl;
    std::cout << "Voulez-vous une interface graphique (1) ou une interface console/fichier (2) ? ";

    int choix;
    std::cin >> choix;

    // Vérifier que l'utilisateur a fait un choix valide
    if (choix != 1 && choix != 2) {
        std::cerr << "Choix invalide. Le programme va se fermer." << std::endl;
        return -1;
    }

    Jeu jeu(cheminFichier, lignes, colonnes, 10.0f);
    std::cout << "Démarrage de la boucle principale..." << std::endl;

    if (choix == 1) {
        std::cout << "Interface graphique sélectionnée." << std::endl;
        jeu.bouclePrincipale();
    }
    else if (choix == 2) {
        std::cout << "Interface console/fichier sélectionnée." << std::endl;
        jeu.bouclePrincipale();
    }

    return 0;
}