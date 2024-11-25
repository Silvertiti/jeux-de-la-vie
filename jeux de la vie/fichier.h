#ifndef FICHIER_H
#define FICHIER_H

#include <string>

class Fichier {
public:
    static bool lireDimensions(const std::string& cheminFichier, int& lignes, int& colonnes);
    static bool lireGrille(const std::string& cheminFichier, bool* tableau, int lignes, int colonnes);
};

#endif
