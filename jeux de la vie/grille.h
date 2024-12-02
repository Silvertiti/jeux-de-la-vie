#ifndef GRILLE_H
#define GRILLE_H

#include <SFML/Graphics.hpp>
#include "Fichier.h"

class Grille {
private:
    int lignes, colonnes;
    bool* tableau;
    std::vector<bool*> historique;

public:
    Grille(int lignes, int colonnes);
    ~Grille();

    bool initialiserDepuisFichier(const std::string& cheminFichier);
    int verifierVoisins(int x, int y);
    void mettreAJour();
    void afficher(sf::RenderWindow& window, float cellSize);
    void sauvegarderEtat();
    void restaurerEtat();
};

#endif
