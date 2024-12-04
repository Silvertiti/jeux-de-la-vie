#ifndef GRILLE_H
#define GRILLE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <stack> // Inclure la bibliothèque pour gérer la pile

class Grille {
private:
    int lignes, colonnes;
    bool* tableau;
    std::stack<bool*> historique; // Pile pour l'historique
    bool* cellulesImmortelles;  // Indique si une cellule est immortelle
    bool* cellulesIndestructibles; // Indique si une cellule est morte indestructible

public:
    Grille(int lignes, int colonnes);
    ~Grille();
    void definirCelluleIndestructible(int x, int y); // Définit une cellule comme morte indestructible
    void definirCelluleImmortelle(int x, int y); // Définit une cellule comme immortelle
	int verifierVoisins(int x, int y);
    void sauvegarderEtat(); // Sauvegarde l'état actuel
    bool revenirEnArriere(); // Revenir à l'état précédent
	bool initialiserDepuisFichier(const std::string& cheminFichier);
    void mettreAJour();
    void afficher(sf::RenderWindow& window, float cellSize, sf::Vector2f grilleOffset);
    void changerCase(sf::RenderWindow& window, float cellSize, sf::Event& event, sf::Vector2f grilleOffset);
};


#endif
