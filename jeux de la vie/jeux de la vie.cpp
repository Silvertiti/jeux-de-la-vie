#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void affichageTableau(int* grill, int lignes, int colonnes) {
    cout << "Tableau de taille " << lignes << "x" << colonnes << " :\n";
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            cout << grill[i * colonnes + j] << " ";
        }
        cout << endl;
    }
}

int* creationTableau(int a, int b) {
    int lignes = a;
    int colonnes = b;

    int* grill = new int[lignes * colonnes]();


    for (int i = 0; i < lignes * colonnes; ++i) {
        grill[i] = 0;
    }
    return grill;
}

int main() {
    string cheminFichier = "C:\\Users\\methe\\source\\repos\\jeux de la vie\\test.txt"; // Remplacez par le chemin de votre fichier
    ifstream fichier(cheminFichier);

    if (!fichier) {
        cerr << "ferme le fichier fdp" << endl;
        return 1;
    }

    string ligne1, ligne2;
    if (getline(fichier, ligne1)) {
    }
    else {
        cout << "casser sa marche pas " << endl;
    }
    if (getline(fichier, ligne2)) {
        cout << "Premiere ligne : " << ligne2 << endl;
    }
    else {
        cout << "casser sa marche pas 2" << endl;
    }

    int lignes = stoi(ligne1);
    int colonnes = stoi(ligne2);
    int* tableau = creationTableau(lignes, colonnes);

    affichageTableau(tableau, lignes, colonnes);



    delete[] tableau;

    return 0;
}
