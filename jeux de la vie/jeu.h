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

    bool pause; // Ajout� pour g�rer la pause

public:
    Jeu(const std::string& cheminFichier, int lignes, int colonnes, float cellSize);
    ~Jeu();
    void bouclePrincipale();

    //void avancerIteration(); // Avancer d'une it�ration
    //void reculerIteration(); // Reculer d'une it�ration

};

#endif 
