
#include "Grille.h"
#include "Fenetre.h"
#include <string>

class Jeu {
private:
    Grille* grille;
    int lignes;
    int colonnes;
    float cellSize;
    Fenetre fenetre;

    bool pause; // Ajouté pour gérer la pause

public:
    Jeu(std::string& cheminFichier, int lignes, int colonnes, float cellSize);
    ~Jeu();
    void bouclePrincipale();
    void avancerIteration(); // Méthode pour avancer d'une itération
    void reculerIteration(); // Méthode pour reculer d'une itération
    void boucleConsole();

};

