#ifndef GRILLE_H
#define GRILLE_H

#include <SFML/Graphics.hpp>
#include <string>

class Grille {
private:
    int lignes, colonnes;
    bool* tableau;

public:
    Grille(int lignes, int colonnes);
    ~Grille();

    bool initialiserDepuisFichier(const std::string& cheminFichier);
    int verifierVoisins(int x, int y);
    void mettreAJour();
    void afficher(sf::RenderWindow& window, float cellSize, sf::Vector2f grilleOffset);
    void changerCase(sf::RenderWindow& window, float cellSize, sf::Event& event, sf::Vector2f grilleOffset);
};

#endif
