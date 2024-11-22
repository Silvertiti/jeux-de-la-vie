#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool* creationTableau(int a, int b) {
    bool* grill = new bool[a * b](); // Crée le tableau et initialise tout à false
    return grill;
}

bool lireDimensions(const string& cheminFichier, int& lignes, int& colonnes) {
    ifstream fichier(cheminFichier);
    if (!fichier.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier." << endl;
        return false;
    }

    string ligne;
    if (getline(fichier, ligne)) {
        lignes = stoi(ligne);
    }
    else {
        cerr << "Erreur : La première ligne est vide ou invalide." << endl;
        return false;
    }

    if (getline(fichier, ligne)) {
        colonnes = stoi(ligne);
    }
    else {
        cerr << "Erreur : La deuxième ligne est vide ou invalide." << endl;
        return false;
    }

    return true;
}

bool lireTableauDepuisFichier(const string& cheminFichier, bool* tableau, int lignes, int colonnes) {
    ifstream fichier(cheminFichier);
    if (!fichier.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier." << endl;
        return false;
    }

    string ligne;
    int index = 0;

    // Ignorer les deux premières lignes (dimensions)
    for (int i = 0; i < 2; ++i) {
        if (!getline(fichier, ligne)) {
            cerr << "Erreur : Fichier trop court." << endl;
            return false;
        }
    }

    for (int i = 0; i < lignes; ++i) {
        if (getline(fichier, ligne)) {
            stringstream ss(ligne);
            for (int j = 0; j < colonnes; ++j) {
                int valeur;
                if (ss >> valeur) {
                    tableau[index++] = valeur;
                }
                else {
                    cerr << "Erreur : Format incorrect dans le fichier." << endl;
                    return false;
                }
            }
        }
        else {
            cerr << "Erreur : Ligne manquante dans le fichier." << endl;
            return false;
        }
    }

    return true;
}

int VérificationVoisin(bool* grill, int lignes, int colonnes, int x, int y) {
    int compteurDeVoisinVivant = 0;
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1},  {1, 0}, {1, 1}
    };

    for (auto& dir : directions) {
        int NouvellePositionX = x + dir[0];
        int NouvellePositionY = y + dir[1];
        if (NouvellePositionX >= 0 && NouvellePositionX < lignes &&
            NouvellePositionY >= 0 && NouvellePositionY < colonnes) {
            compteurDeVoisinVivant += grill[NouvellePositionX * colonnes + NouvellePositionY];
        }
    }
    return compteurDeVoisinVivant;
}

void MiseAjourGrill(bool* grill, int lignes, int colonnes) {
    bool* GrillTemporaire = new bool[lignes * colonnes];

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            int emplacement = i * colonnes + j;
            int voisins = VérificationVoisin(grill, lignes, colonnes, i, j);

            if (grill[emplacement]) {
                GrillTemporaire[emplacement] = (voisins == 2 || voisins == 3);
            }
            else {
                GrillTemporaire[emplacement] = (voisins == 3);
            }
        }
    }

    for (int i = 0; i < lignes * colonnes; ++i) {
        grill[i] = GrillTemporaire[i];
    }

    delete[] GrillTemporaire;
}

void afficherGrille(sf::RenderWindow& window, bool* grill, int lignes, int colonnes, float cellSize) {
    sf::RectangleShape cellule(sf::Vector2f(cellSize - 1, cellSize - 1)); // Taille de la cellule, avec une bordure

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            cellule.setPosition(j * cellSize, i * cellSize);

            // Définir la couleur de remplissage
            if (grill[i * colonnes + j]) {
                cellule.setFillColor(sf::Color::Black);
            }
            else {
                cellule.setFillColor(sf::Color::White);
            }

            // Dessiner les cellules
            window.draw(cellule);
        }
    }

    // Dessiner les lignes de la grille
    sf::Vertex line[2];
    line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;

    // Lignes horizontales
    for (int i = 0; i <= lignes; ++i) {
        line[0].position = sf::Vector2f(0, i * cellSize);
        line[1].position = sf::Vector2f(colonnes * cellSize, i * cellSize);
        window.draw(line, 2, sf::Lines);
    }

    // Lignes verticales
    for (int i = 0; i <= colonnes; ++i) {
        line[0].position = sf::Vector2f(i * cellSize, 0);
        line[1].position = sf::Vector2f(i * cellSize, lignes * cellSize);
        window.draw(line, 2, sf::Lines);
    }
}

int main() {
    string cheminFichier = "C:\\Users\\methe\\source\\repos\\jeux de la vie\\test.txt";

    int lignes = 0, colonnes = 0;

    if (!lireDimensions(cheminFichier, lignes, colonnes)) {
        return -1;
    }

    bool* tableau = creationTableau(lignes, colonnes);

    if (!lireTableauDepuisFichier(cheminFichier, tableau, lignes, colonnes)) {
        delete[] tableau;
        return -1;
    }

    float cellSize = 20.0f; // Taille d'une cellule
    sf::RenderWindow window(sf::VideoMode(colonnes * cellSize, lignes * cellSize), "Jeu de la Vie - SFML");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Mettre à jour la grille
        MiseAjourGrill(tableau, lignes, colonnes);

        // Afficher la grille
        window.clear(sf::Color::White);
        afficherGrille(window, tableau, lignes, colonnes, cellSize);
        window.display();

        sf::sleep(sf::seconds(1)); // Pause de 1 seconde entre les étapes
    }

    delete[] tableau;
    return 0;
}
