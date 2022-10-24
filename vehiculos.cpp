#include <iostream>
#include <vector>
#include <cmath>

#include "nodos.hpp"
#include "vehiculos.hpp"

using namespace std;

vehiculo::vehiculo(int i, int c) {
    id = i;
    capacidad = c;
    peso_actual = 0;
    distancia_recorrida = 0;
    posicion = {0, 0};
    ruta = {}; //vector de int => id's de nodos
}

void vehiculo::print() {
    cout << "Vehiculo " << id << "\n"
    << "  Capacidad: " << capacidad << "\n"
    << "  Peso Actual: " << peso_actual << "\n"
    << "  Distancia Recorrida: " << distancia_recorrida << "\n"
    << "  Pos: (" << posicion.at(0) << ", " << posicion.at(1) << ")" << "\n"
    << "  Ruta: (";
    for (const int i : ruta){
        cout << i << " ";
    }
    cout << ")\n";
}

void vehiculo::add_ruta(int x) {
    ruta.push_back(x);
}

void vehiculo::add_peso(int x) {
    peso_actual += x;
}

void vehiculo::add_dist(float d) {
    distancia_recorrida += d;
}

void vehiculo::set_pos(float x, float y) {
    vector<float> p;
    p.push_back(x);
    p.push_back(y);
    posicion = p;
}

float vehiculo::dist(nodo uno) {
    int xs = pow(uno.coordX - posicion.at(0), 2);
    int ys = pow(uno.coordY - posicion.at(1), 2);
    float distancia = sqrt(xs + ys);
    return distancia;
}