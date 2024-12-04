#include "Grille.h"
#include <cstring>
#include <iostream>
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

void Grille::changerCase(sf::RenderWindow& window, float cellSize, sf::Event& event) {
    sf::Vector2f decalage(100, 100); // Décalage pour positionner la grille

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        // Calcul des coordonnées de la case dans la grille
        int col = static_cast<int>((worldPos.x - decalage.x) / cellSize);
        int row = static_cast<int>((worldPos.y - decalage.y) / cellSize);

        // Vérifie si les coordonnées sont dans les limites de la grille
        if (col >= 0 && col < colonnes && row >= 0 && row < lignes) {
            int index = row * colonnes + col;
            tableau[index] = !tableau[index]; // Change l'état de la case
            std::cout << "Case cliquée : (" << row << ", " << col << ") nouvel état : "
                << (tableau[index] ? "vivante" : "morte") << std::endl;
        }
    }
}

void Grille::afficher(sf::RenderWindow& window, float cellSize) {
    //sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	//view.zoom(0.5f);    
    //window.setView(view);

    sf::Vector2f decalage(100,100);

    sf::RectangleShape cellule(sf::Vector2f(cellSize - 1, cellSize - 1));

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            cellule.setPosition(j * cellSize+decalage.x, i * cellSize+decalage.y);
            cellule.setFillColor(tableau[i * colonnes + j] ? sf::Color::Black : sf::Color::White);
            window.draw(cellule);
        }
    }


    // Cooldown check
    if (clickCooldown.getElapsedTime().asSeconds() > 0.f) { // Cooldown of 200ms
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

            // Calculate grid coordinates
            int col = static_cast<int>((worldPos.x - decalage.x) / cellSize);
            int row = static_cast<int>((worldPos.y - decalage.y) / cellSize);

            if (col >= 0 && col < colonnes && row >= 0 && row < lignes) {
                std::cout << "Clicked cell at: (" << row << ", " << col << ")" << std::endl;
                clickCooldown.restart(); // Reset cooldown timer
            }
        }
    }

    sf::Vertex line[2];
    line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;

    for (int i = 0; i <= lignes; ++i) {
        line[0].position = decalage + sf::Vector2f(0, i * cellSize);
        line[1].position = decalage + sf::Vector2f(colonnes * cellSize, i * cellSize);
        window.draw(line, 2, sf::Lines);
    }

    for (int j = 0; j <= colonnes; ++j) {
        line[0].position = decalage + sf::Vector2f(j * cellSize, 0);
        line[1].position = decalage + sf::Vector2f(j * cellSize, lignes * cellSize);
        window.draw(line, 2, sf::Lines);
    }
}

