#include <iostream>

#include "nodos.hpp"

using namespace std;

nodo::nodo(int i, int t, float x, float y) {
    tipo = t;
    id = i;
    coordX = x;
    coordY = y;
}

void nodo::print() {
    cout << "Nodo " << id << "\n";

    if (tipo == 0) {
        cout << "Tipo: Depósito\n";
    } else if (tipo == 1) {
        cout << "Tipo: Linehaul\n";
    } else if (tipo == 2) {
        cout << "Tipo: Backhaul\n";
    } else {
        cout << "tipo: Desconocido\n";
    }

    cout << "Coord: (" << coordX << ", " << coordY << ")" << endl;
}