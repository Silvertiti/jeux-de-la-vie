#include <string>

class Fichier {
public:
    static bool lireDimensions(const std::string cheminFichier, int& lignes, int& colonnes);       //static per�et d'appeller la classe sans creer d objrt 
    static bool lireGrille(const std::string cheminFichier, bool* tableau, int lignes, int colonnes);
};


