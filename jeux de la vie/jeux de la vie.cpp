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
    int* grill = new int[a * b]();

    for (int i = 0; i < a * b; ++i) {
        grill[i] = 0;
    }
    return grill;
}

bool lireFichier(const string& cheminFichier, string& ligne1, string& ligne2) {
    ifstream fichier(cheminFichier);

    if (getline(fichier, ligne1)) {
        if (!getline(fichier, ligne2)) {
            cerr << "y'a pas de deuxiéme ligne batard" << endl;
            return false;
        }
    }
    else {
        cerr << "Ton fichier TXT est vide fdp" << endl;
        return false;
    }

    return true;
}

int main() {
    string cheminFichier = "C:\\Users\\methe\\source\\repos\\jeux de la vie\\test.txt";
    string ligne1, ligne2;

	lireFichier(cheminFichier, ligne1, ligne2);
    

    int lignes = stoi(ligne1);
    int colonnes = stoi(ligne2);

    int* tableau = creationTableau(lignes, colonnes);
    affichageTableau(tableau, lignes, colonnes);
    delete[] tableau;

}
