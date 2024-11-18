#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

bool* creationTableau(int a, int b) {
    bool* grill = new bool[a * b](); // crée le tableau et initialise tout à false
    return grill;
}

bool changerValeur(bool* grill, int emplacement) {
    // Change la valeur de l'emplacement spécifié
    grill[emplacement] = !grill[emplacement]; // Inversion de la valeur pour montrer le changement
    return grill[emplacement];
}

void affichageTableauClassic(bool* grill, int lignes, int colonnes) {  /// affichage du tableau
    system("cls");
    cout << "Tableau de taille " << lignes << "x" << colonnes << " :\n";
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            cout << grill[i * colonnes + j] << " ";
        }
        cout << endl;
    }
}

void affichageTableauBool(bool* grill, int lignes, int colonnes) {
    system("cls");
    cout << "Tableau de taille " << lignes << "x" << colonnes << " :\n";
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            // Affichage de `true` et `false` comme 1 et 0 respectivement
            cout << (grill[i * colonnes + j] ? "true " : "false ");
        }
        cout << endl;
    }
}

bool lireDimensions(const string& cheminFichier, int& lignes, int& colonnes) {
    ifstream fichier(cheminFichier);
    if (!fichier.is_open()) {
        cerr << "FDP ferme le fichier" << endl;
        return false;
    }

    string ligne;

	// association de la deuxiéme ligne pour les lignes
    if (getline(fichier, ligne)) {
        lignes = stoi(ligne);
    }
    else {
        cerr << "Bon la premiére ligne est vide ou pas bonne" << endl;
        return false;
    }

	// association de la deuxiéme ligne pour les colonnes
    if (getline(fichier, ligne)) {
        colonnes = stoi(ligne);
    }
    else {
        cerr << "Bon la deuxiéme ligne est vide ou pas bonne" << endl;
        return false;
    }

    return true;
}

bool lireTableauDepuisFichier(const string& cheminFichier, bool* tableau, int lignes, int colonnes) {
    ifstream fichier(cheminFichier);
    if (!fichier.is_open()) {
        cerr << "ferme le fichier ou tu la suprimer" << endl;
        return false;
    }
    string ligne;
    int index = 0;

	// sa saute les 2 premieres lignes car la on  cherche a lire le tableau 
    for (int i = 0; i < 2; ++i) {
        if (!getline(fichier, ligne)) {
            cerr << "Gros con le fichier TXT est vide" << endl;
            return false;
        }
    }
    // début de la lecture du tableau
    for (int i = 0; i < lignes; ++i) {
        if (getline(fichier, ligne)) {
            stringstream ss(ligne);
            for (int j = 0; j < colonnes; ++j) {
                int valeur;
                if (ss >> valeur) {
                    tableau[index++] = valeur;
                }
                else {
                    cerr << "gros con ta pas mis le tableau dans le fichier txt " << endl;
                    return false;
                }
            }
        }
        else {             
            cerr << "bon ton fichier est vide FDP" << endl;

            return false;
        } 
    }
    return true;
}

int main() {
    string cheminFichier = "C:\\Users\\methe\\source\\repos\\jeux de la vie\\test.txt";
    int lignes = 0, colonnes = 0;

    if (!lireDimensions(cheminFichier, lignes, colonnes)) {
        return -1;
    }

    bool* tableau = creationTableau(lignes, colonnes);

    lireTableauDepuisFichier(cheminFichier, tableau, lignes, colonnes);

    affichageTableauClassic(tableau, lignes, colonnes);

	changerValeur(tableau, 10);

    affichageTableauBool(tableau, lignes, colonnes);

    
    delete[] tableau;
    return 0;
}
