#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

bool not_in(int x, vector<int> n) {
    for (int i = 0; i < n.size(); ++i) {
        if (x == n.at(i)) {
            return false;
        }
    }
    return true;
}

//(7 11 4 23 13 26 1 )

void crear_carpeta() {
    string path = "soluciones";
    int status = mkdir(path.c_str(), 0777);
    if (status == 0) {
        cout << "\nDirectorio soluciones creado";
    }
}

vector<int> nodos_faltantes(vector<int> nodos, vector<int> v) {
    vector<int> faltantes;
    for (int i = 0; i < nodos.size(); ++i) {
        if (count(v.begin(), v.end(), nodos.at(i)) == 0) {
            faltantes.push_back(nodos.at(i));
        }
    }
    //print
    //for (int i = 0; i < faltantes.size(); ++i) {
    //    cout << faltantes.at(i);
    //}
    return faltantes;
}