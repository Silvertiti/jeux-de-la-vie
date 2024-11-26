#ifndef JEU_H
#define JEU_H

#include "Grille.h"
#include "Fenetre.h"
#include <string>

class Jeu {
private:
    Grille* grille;
    int lignes, colonnes;
    float cellSize;
    Fenetre fenetre;

public:
    Jeu(const std::string& cheminFichier, int lignes, int colonnes, float cellSize);
    ~Jeu();
    void bouclePrincipale();
};

#endif 
