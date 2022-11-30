#include <iostream>
#include <vector>
#include <cmath>

#include "nodos.hpp"
#include "vehiculos.hpp"

using namespace std;

vehiculo::vehiculo(int i, int c) {
    id = i;
    capacidad = c;
    demandaL = 0;
    demandaB = 0;
    distancia_recorrida = 0;
    posicion = {0, 0};
    ruta = {}; //vector de int => id's de nodos
}

void vehiculo::print() {
    cout << "Vehiculo " << id << "\n"
    << "  Capacidad: " << capacidad << "\n"
    << "  Demanda Linehaul: " << demandaL << "\n"
    << "  Demanda Backhaul: " << demandaB << "\n"
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

void vehiculo::add_ruta_faltante(int x) {
    ruta.pop_back();
    ruta.push_back(x);
    ruta.push_back(1);
}

void vehiculo::add_l(int x) {
    demandaL += x;
}

void vehiculo::rem_l(int x) {
    demandaL -= x;
}

void vehiculo::add_b(int x) {
    demandaB += x;
}

void vehiculo::rem_b(int x) {
    demandaB -= x;
}

void vehiculo::add_dist(double d) {
    distancia_recorrida += d;
}

void vehiculo::set_pos(float x, float y) {
    vector<float> p;
    p.push_back(x);
    p.push_back(y);
    posicion = p;
}

double vehiculo::dist(nodo uno) {
    double xs = pow(uno.coordX - posicion.at(0), 2);
    double ys = pow(uno.coordY - posicion.at(1), 2);
    double distancia = sqrt(xs + ys);
    //cout << "xs: " << xs << " ys " << ys << " d " << distancia << endl;
    return distancia;
}

bool vehiculo::recorrido_terminado() {
    if (ruta.at(ruta.size() - 1) == 1 || ruta.empty()) {
        return true;
    } else {
        return false;
    }
}

//auxiliar para recalcular
double distancia_2nodos(float x1, float y1, float x2, float y2){
    double xs = pow(x1 - x2, 2);
    double ys = pow(y1 - y2, 2);
    double distancia = sqrt(xs + ys);
    return distancia;
}

void vehiculo::recalcularD(vector<nodo> nodos) {
    if (!nodos.empty()) {
        //el 1 no viene, se calcula como el primero y el ultimo
        double d = distancia_2nodos(nodos.at(nodos.size()-1).coordX, nodos.at(nodos.size()-1).coordY, nodos.front().coordX, nodos.front().coordY); 
        //cout << "d: " << d << endl;
        for (int i = 1; i < ruta.size(); ++i) {
            float x1 = nodos.at(i).coordX;
            float y1 = nodos.at(i).coordY;
            float x2 = nodos.at(i-1).coordX;
            float y2 = nodos.at(i-1).coordY;
            d += distancia_2nodos(x1, y1, x2, y2);
            //cout << "x1 " << x1
            //    << " y1 " << y1
            //    << " x2 " << x2
            //    << " y2 " << y2
            //    << " d: " << d << endl;
        }
        distancia_recorrida = d;
    }
}