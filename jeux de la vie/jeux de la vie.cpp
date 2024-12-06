#include "Fichier.h"
#include "Jeu.h"
#include <iostream>

int max = 600000;

int main() {

    int lignes = 0, colonnes = 0;

    std::cout << "Voulez-vous un modele predefini (1) ou voulais vous charger votre fichier test.txt" << "(2)" << std::endl;

    int choixFichier;
    std::cin >> choixFichier;
    if (choixFichier != 1 && choixFichier != 2) {
        std::cerr << "Choix invalide. Le programme va se fermer." << std::endl;
        return -1;
    }
    if (choixFichier == 2) {

        std::string cheminFichier = "C:\\Users\\laara\\OneDrive\\Bureau\\test github3\\test.txt";


        if (!Fichier::lireDimensions(cheminFichier, lignes, colonnes)) {
            std::cerr << "Erreur : Impossible de lire les dimensions depuis " << cheminFichier << "." << std::endl;
            return -1;
        }

        if (lignes * colonnes > max) {
            std::cerr << "Erreur : Les dimensions sont trop grandes : " << max << " cellules." << std::endl;
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

        Jeu jeu(cheminFichier, lignes, colonnes, 20.0f);
        std::cout << "Démarrage de la boucle principale..." << std::endl;

        if (choix == 1) {
            std::cout << "Interface graphique sélectionnée." << std::endl;
            jeu.bouclePrincipale();

        }
        else (choix == 2); {
            std::cout << "Interface console/fichier sélectionnée." << std::endl;

            int nbiteration;// a prendre en private dans 
            std::cout << "combien d'itération voulez vous" << std::endl;
            std::cin >> nbiteration;
            //jeu.boucleConsole(nbiteration);
        }

    }



    if (choixFichier == 1) {

        std::cout << "Vous avez choisi un modele predefinis  " << std::endl;

        std::cout << "Choisissez le modele\n\n  " << std::endl;
        std::cout << "1: blinker\n2: Gosper Glider Gun\n" << std::endl;

        int choixModele;
        std::cin >> choixModele;

        if (choixModele == 1) {
            std::cout << "vous avez choissis blinker";
            std::string cheminFichier = "C:\\Users\\laara\\OneDrive\\Bureau\\test github3\\modele predefinis\\blinker.txt"; // Utilisation d'un chemin relatif



            if (!Fichier::lireDimensions(cheminFichier, lignes, colonnes)) {
                std::cerr << "Erreur : Impossible de lire les dimensions depuis " << cheminFichier << "." << std::endl;
                return -1;
            }

            if (lignes * colonnes > max) {
                std::cerr << "Erreur : Les dimensions sont trop grandes : "
                    << max << " cellules." << std::endl;
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

            Jeu jeu(cheminFichier, lignes, colonnes, 20.0f);
            std::cout << "Démarrage de la boucle principale..." << std::endl;

            if (choix == 1) {
                std::cout << "Interface graphique sélectionnée." << std::endl;
                jeu.bouclePrincipale();
            }
            else if (choix == 2) {
                std::cout << "Interface console/fichier sélectionnée." << std::endl;
                //jeu.boucleConsole();
            }
        }

        if (choixModele == 2) {
            std::cout << "vous avez choissis Gosper Glider Gun";
            std::string cheminFichier = "C:\\Users\\laara\\OneDrive\\Bureau\\test github3\\modele predefinis\\Gosper Glider Gun.txt"; // Utilisation d'un chemin relatif



            if (!Fichier::lireDimensions(cheminFichier, lignes, colonnes)) {
                std::cerr << "Erreur : Impossible de lire les dimensions depuis " << cheminFichier << "." << std::endl;
                return -1;
            }

            if (lignes * colonnes > max) {
                std::cerr << "Erreur : Les dimensions sont trop grandes : "
                    << max << " cellules." << std::endl;
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

            Jeu jeu(cheminFichier, lignes, colonnes, 20.0f);
            std::cout << "Démarrage de la boucle principale..." << std::endl;

            if (choix == 1) {
                std::cout << "Interface graphique sélectionnée." << std::endl;
                jeu.bouclePrincipale();
            }
            else if (choix == 2) {
                std::cout << "Interface console/fichier sélectionnée." << std::endl;
                //jeu.boucleConsole();
            }
        }
    }

    return 0;
}
