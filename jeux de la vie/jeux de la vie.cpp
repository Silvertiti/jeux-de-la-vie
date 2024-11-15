#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void creationMatrice(int a, int b) {
    const int lignes = a;
    const int colonnes = b;

    vector<vector<int>> matrice(lignes, vector<int>(colonnes, 0));

    cout << "Matrice remplie de 0 :\n";
	for (int i = 0; i < lignes; ++i) { /// associe a i toute les valeur de la  variable LIGNES 
        for (int j = 0; j < colonnes; ++j) { /// associe a i toute les valeur de la  variable COLONNES
            cout << matrice[i][j] << " ";
        }
        cout << endl;
    }
}


int main() {
	creationMatrice(5, 5);

}

