#include <iostream>
#include <cmath>

#include "nodos.hpp"

using namespace std;

nodo::nodo(int t, int i, float x, float y) {
    tipo = t;
    id = i;
    coordX = x;
    coordY = y;
    demanda = 0;
}

void nodo::print() {
    cout << "Nodo " << id << "\n";
    if (tipo == 0) {
        cout << "  Tipo: Depósito\n";
    } else if (tipo == 1) {
        cout << "  Tipo: Linehaul\n";
    } else if (tipo == 2) {
        cout << "  Tipo: Backhaul\n";
    } else {
        cout << "  Tipo: Desconocido\n";
    }
    cout << "  Demanda: " << demanda << "\n";
    cout << "  Coord: (" << coordX << ", " << coordY << ")\n" << endl;
}

float nodo::dist(nodo uno) {
    int xs = pow(uno.coordX - coordX, 2);
    int ys = pow(uno.coordY - coordY, 2);
    float distancia = sqrt(xs + ys);
    return distancia;
}

void nodo::set_d(int d) {
    demanda = d;
}