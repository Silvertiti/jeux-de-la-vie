#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h> // Nécessaire pour Sleep sous Windows
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

void affichageTableauClassic(bool* grill, int lignes, int colonnes) {
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
    if (getline(fichier, ligne)) {
        lignes = stoi(ligne);
    }
    else {
        cerr << "Bon la premiére ligne est vide ou pas bonne" << endl;
        return false;
    }

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

    for (int i = 0; i < 2; ++i) {
        if (!getline(fichier, ligne)) {
            cerr << "Gros con le fichier TXT est vide" << endl;
            return false;
        }
    }

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

int countNeighbors(bool* grill, int lignes, int colonnes, int x, int y) {
    int count = 0;
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1},  {1, 0}, {1, 1}
    };

    for (auto& dir : directions) {
        int nx = x + dir[0];
        int ny = y + dir[1];
        if (nx >= 0 && nx < lignes && ny >= 0 && ny < colonnes) {
            count += grill[nx * colonnes + ny];
        }
    }
    return count;
}

void updateGrid(bool* grill, int lignes, int colonnes) {
    bool* newGrid = new bool[lignes * colonnes];

    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            int index = i * colonnes + j;
            int neighbors = countNeighbors(grill, lignes, colonnes, i, j);

            if (grill[index]) {
                newGrid[index] = (neighbors == 2 || neighbors == 3);
            }
            else {
                newGrid[index] = (neighbors == 3);
            }
        }
    }

    for (int i = 0; i < lignes * colonnes; ++i) {
        grill[i] = newGrid[i];
    }

    delete[] newGrid;
}

int main() {
    string cheminFichier = "C:\\Users\\methe\\source\\repos\\jeux de la vie\\test.txt";
    int lignes = 0, colonnes = 0;

    if (!lireDimensions(cheminFichier, lignes, colonnes)) {
        return -1;
    }

    bool* tableau = creationTableau(lignes, colonnes);

    if (!lireTableauDepuisFichier(cheminFichier, tableau, lignes, colonnes)) {
        delete[] tableau;
        return -1;
    }

    affichageTableauClassic(tableau, lignes, colonnes);

    for (int step = 0; step < 100; ++step) {
        updateGrid(tableau, lignes, colonnes);
        affichageTableauClassic(tableau, lignes, colonnes);
        Sleep(1000); // Pause de 2000 millisecondes (2 secondes)
    }

    delete[] tableau;
    return 0;
}
