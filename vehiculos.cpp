#include <iostream>
#include <vector>

#include "vehiculos.hpp"

using namespace std;

vehiculo::vehiculo(int i, int c) {
    id = i;
    capacidad = c;
    peso_actual = 0;
    ruta = {}; //vector de int => id's de nodos
}

void vehiculo::print() {
    cout << "Vehiculo " << id << "\n"
    << "  Capacidad: " << capacidad << "\n"
    << "  Peso Actual: " << peso_actual << "\n"
    << "  Ruta: (";
    for (const int i : ruta){
        cout << i << " ";
    }
    cout << ")\n" << endl;
}