#include <iostream>
#include <bits/stdc++.h> //leer archivos

using namespace std;

string numero_elementos(string archivo) {
    ifstream file("GA1.txt");
    string texto;
    if (file.good()) {
        getline(file, texto);
    }
    return texto;
}

int holder(string archivo) {
    fstream file;
    string texto;
    file.open(archivo.c_str());
    while (file >> texto) {
        cout << texto << "\n";
    }
    return 0;
}