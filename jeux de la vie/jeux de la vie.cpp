#include <iostream>
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
    string cheminFichier = "C:\\Users\\methe\\\repos\\ de la vie\\test.txt";
    int lignes = 100;
    int colonnes = 100;
    int* tableau = creationTableau(lignes, colonnes); 

    cout << "Utilisation du tableau retourné :\n";
    affichageTableau(tableau, lignes, colonnes);

    delete[] tableau;

    return 0;
}
