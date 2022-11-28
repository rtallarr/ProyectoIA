#include <iostream>
#include <vector>

#include "nodos.hpp"
#include "vehiculos.hpp"
#include "soluciones.hpp"

conjunto_solucion::conjunto_solucion(float c, solucion) {
    calidad = c;
    autos = v;
}

void solucion::print() {
    cout << "Calidad: " << calidad << endl;
    for(int i = 0; i < autos.size(); ++i) {
        autos.at(i).print();
    }
}

vector<solucion> solucion::vecindario() {
    vector<solucion> veci;
    for (int i = 0; i < autos.size(); ++i) {
        for(int j = 0; j < autos.at(i).ruta.size(); ++j) {
            solucion nueva = solucion()
        }
    }

    return veci;
}