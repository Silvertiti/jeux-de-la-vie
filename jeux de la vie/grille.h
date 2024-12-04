#ifndef GRILLE_H
#define GRILLE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <stack> // Inclure la biblioth�que pour g�rer la pile

class Grille {
private:
    int lignes, colonnes;
    bool* tableau;
    std::stack<bool*> historique; // Pile pour l'historique

public:
    Grille(int lignes, int colonnes);
    ~Grille();

	int verifierVoisins(int x, int y);
    void sauvegarderEtat(); // Sauvegarde l'�tat actuel
    bool revenirEnArriere(); // Revenir � l'�tat pr�c�dent
	bool initialiserDepuisFichier(const std::string& cheminFichier);
    void mettreAJour();
    void afficher(sf::RenderWindow& window, float cellSize, sf::Vector2f grilleOffset);
    void changerCase(sf::RenderWindow& window, float cellSize, sf::Event& event, sf::Vector2f grilleOffset);
};


#endif
