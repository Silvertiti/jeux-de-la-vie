#include "Grille.h"
#include <cstring>

Grille::Grille(int lignes, int colonnes) : lignes(lignes), colonnes(colonnes) {
    tableau = new bool[lignes * colonnes]();
}

Grille::~Grille() {
    delete[] tableau;
}

bool Grille::initialiserDepuisFichier(const std::string& cheminFichier) {
    return Fichier::lireGrille(cheminFichier, tableau, lignes, colonnes);
}

int Grille::verifierVoisins(int x, int y) {
    int compteurDeVoisinVivant = 0;
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1},  {1, 0}, {1, 1}
    };

    for (auto& dir : directions) {
        int nx = x + dir[0], ny = y + dir[1];
        if (nx >= 0 && nx < lignes && ny >= 0 && ny < colonnes)
            compteurDeVoisinVivant += tableau[nx * colonnes + ny];
    }

    return compteurDeVoisinVivant;
}

void Grille::mettreAJour() {
    bool* temp = new bool[lignes * colonnes];
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            int voisins = verifierVoisins(i, j);
            int index = i * colonnes + j;
            temp[index] = tableau[index] ? (voisins == 2 || voisins == 3) : (voisins == 3);
        }
    }
    memcpy(tableau, temp, lignes * colonnes * sizeof(bool));
    delete[] temp;
}

void Grille::afficher(sf::RenderWindow& window, float cellSize) {
    sf::RectangleShape cellule(sf::Vector2f(cellSize - 1, cellSize - 1));

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            cellule.setPosition(j * cellSize, i * cellSize);
            cellule.setFillColor(tableau[i * colonnes + j] ? sf::Color::Black : sf::Color::White);
            window.draw(cellule);
        }
    }

    sf::Vertex line[2];
    line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;

    for (int i = 0; i <= lignes; ++i) {
        line[0].position = sf::Vector2f(0, i * cellSize);
        line[1].position = sf::Vector2f(colonnes * cellSize, i * cellSize);
        window.draw(line, 2, sf::Lines);
    }

    for (int j = 0; j <= colonnes; ++j) {
        line[0].position = sf::Vector2f(j * cellSize, 0);
        line[1].position = sf::Vector2f(j * cellSize, lignes * cellSize);
        window.draw(line, 2, sf::Lines);
    }
}
