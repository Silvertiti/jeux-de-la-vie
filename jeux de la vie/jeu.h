
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

    bool pause; // Ajout� pour g�rer la pause

public:
    Jeu(std::string& cheminFichier, int lignes, int colonnes, float cellSize);
    ~Jeu();
    void bouclePrincipale();
    void avancerIteration(); // M�thode pour avancer d'une it�ration
    void reculerIteration(); // M�thode pour reculer d'une it�ration
    void boucleConsole();

};

