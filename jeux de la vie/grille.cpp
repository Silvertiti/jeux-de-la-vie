#include "Grille.h"
#include <cstring>
#include <iostream>
#include <fstream>

Grille::Grille(int lignes, int colonnes) : lignes(lignes), colonnes(colonnes) {
    tableau = new bool[lignes * colonnes]();
    cellulesImmortelles = new bool[lignes * colonnes]();
    cellulesIndestructibles = new bool[lignes * colonnes](); // Initialiser toutes les cellules comme destructibles
}

Grille::~Grille() {
    delete[] tableau;
    delete[] cellulesImmortelles;
    delete[] cellulesIndestructibles;
}



bool Grille::initialiserDepuisFichier(const std::string& cheminFichier) {
    std::ifstream fichier(cheminFichier);
    if (!fichier.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << cheminFichier << std::endl;
        return false;
    }

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            char c;
            fichier >> c;
            tableau[i * colonnes + j] = (c == '1');
        }
    }

    fichier.close();
    return true;
}

int Grille::verifierVoisins(int x, int y) {
    int compteur = 0;
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1},  {1, 0}, {1, 1}
    };

    for (auto& dir : directions) {
        int nx = x + dir[0], ny = y + dir[1];
        if (nx >= 0 && nx < lignes && ny >= 0 && ny < colonnes) {
            compteur += tableau[nx * colonnes + ny];
        }
    }

    return compteur;
}

void Grille::definirCelluleIndestructible(int x, int y) {
    if (x >= 0 && x < lignes && y >= 0 && y < colonnes) {
        int index = x * colonnes + y;
        cellulesIndestructibles[index] = !cellulesIndestructibles[index]; // Basculer l'état
        tableau[index] = cellulesIndestructibles[index] ? false : tableau[index]; // Si indestructible, elle reste morte
    }
}


void Grille::definirCelluleImmortelle(int x, int y) {
    if (x >= 0 && x < lignes && y >= 0 && y < colonnes) {
        int index = x * colonnes + y;
        cellulesImmortelles[index] = !cellulesImmortelles[index]; // Basculer l'état
        tableau[index] = cellulesImmortelles[index] ? true : tableau[index]; // Si immortelle, elle devient vivante
    }
}


void Grille::sauvegarderEtat() {
    bool* etatSauvegarde = new bool[lignes * colonnes];
    std::memcpy(etatSauvegarde, tableau, lignes * colonnes * sizeof(bool));
    historique.push(etatSauvegarde);
}

bool Grille::revenirEnArriere() {
    if (historique.empty()) {
        std::cerr << "Aucun état précédent disponible." << std::endl;
        return false;
    }

    delete[] tableau; // Libérer l'état actuel
    tableau = historique.top(); // Récupérer l'état précédent
    historique.pop(); // Supprimer l'état de la pile
    return true;
}

void Grille::mettreAJour() {
    sauvegarderEtat(); // Sauvegarder l'état actuel avant de le modifier

    bool* temp = new bool[lignes * colonnes];
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            int index = i * colonnes + j;

            if (cellulesIndestructibles[index]) {
                temp[index] = false; // Cellule morte indestructible reste morte
            }
            else if (cellulesImmortelles[index]) {
                temp[index] = true; // Cellule immortelle reste vivante
            }
            else {
                int voisins = verifierVoisins(i, j);
                temp[index] = tableau[index] ? (voisins == 2 || voisins == 3) : (voisins == 3);
            }
        }
    }

    std::memcpy(tableau, temp, lignes * colonnes * sizeof(bool));
    delete[] temp;
}



void Grille::afficher(sf::RenderWindow& window, float cellSize, sf::Vector2f grilleOffset) {
    sf::RectangleShape cellule(sf::Vector2f(cellSize - 1, cellSize - 1));

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            int index = i * colonnes + j;

            cellule.setPosition(
                j * cellSize + grilleOffset.x,
                i * cellSize + grilleOffset.y
            );

            if (cellulesIndestructibles[index]) {
                cellule.setFillColor(sf::Color::Red); // Couleur spéciale pour les cellules mortes indestructibles
            }
            else if (cellulesImmortelles[index]) {
                cellule.setFillColor(sf::Color::Blue); // Couleur spéciale pour les cellules immortelles
            }
            else {
                cellule.setFillColor(tableau[index] ? sf::Color::Black : sf::Color::White);
            }

            window.draw(cellule);
        }
    }

    // Dessiner les lignes de la grille (facultatif)
    sf::Vertex line[2];
    line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;

    for (int i = 0; i <= lignes; ++i) {
        line[0].position = grilleOffset + sf::Vector2f(0, i * cellSize);
        line[1].position = grilleOffset + sf::Vector2f(colonnes * cellSize, i * cellSize);
        window.draw(line, 2, sf::Lines);
    }

    for (int j = 0; j <= colonnes; ++j) {
        line[0].position = grilleOffset + sf::Vector2f(j * cellSize, 0);
        line[1].position = grilleOffset + sf::Vector2f(j * cellSize, lignes * cellSize);
        window.draw(line, 2, sf::Lines);
    }
}


void Grille::changerCase(sf::RenderWindow& window, float cellSize, sf::Event& event, sf::Vector2f grilleOffset) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        int col = static_cast<int>((worldPos.x - grilleOffset.x) / cellSize);
        int row = static_cast<int>((worldPos.y - grilleOffset.y) / cellSize);

        if (col >= 0 && col < colonnes && row >= 0 && row < lignes) {
            int index = row * colonnes + col;
            tableau[index] = !tableau[index];
            std::cout << "Case cliquée : (" << row << ", " << col << ") nouvel état : "
                << (tableau[index] ? "vivante" : "morte") << std::endl;
        }
    }
}