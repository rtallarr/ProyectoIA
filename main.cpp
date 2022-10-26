#include <iostream> //standard
#include <sys/stat.h> //mkdir
#include <bits/stdc++.h> //leer archivos
#include <vector>

#include "nodos.hpp"
#include "vehiculos.hpp"
#include "func.hpp"

using namespace std;

int main() { //cambiar a otro archivo que genera una solucion para un archivo.
    int id, t, n;
    float x, y;
    vector<nodo> nodos;             //lista de todos los nodos
    vector<vehiculo> vehiculos;     //lista de autos

    ifstream file("GA1.txt");

    //leer numero de nodos
    file >> n;
    //cout << "N nodos: " << n << "\n";

    //asignar cada dato de cada nodo (sin demanda)
    for(int i = 0; i < n; ++i){
        file >> t >> id >> x >> y;
        nodo n = nodo(t, id, x, y);
        //n.print();
        nodos.push_back(n);
    }

    int cap, cant;
    int otro_id;
    float d;
    file >> cant >> cap;
    //cout << "Cant Vehiculos: " << cant << " Capacidad: " << cap << endl;
    
    //asignar demanda a cada nodo ¿?¿?¿?¿?
    for(int i = 1; i < n; ++i) { //id 1 => depot
        file >> otro_id >> d;
        if (otro_id != 0) {
            cout << otro_id;
        }
        nodos.at(i).set_d(d);
        //cout << nodos.at(i).demanda;
    }

    //crear vehiculos
    for(int i = 1; i <= cant; ++i) {
        vehiculo v = vehiculo(i, cap);
        vehiculos.push_back(v);
        vehiculos.at(i-1).set_pos(nodos.at(0).coordX, nodos.at(0).coordY); //pos inicial = depot
        //v.print();
    }

    //numeros de los nodos
    vector<int> nodos_disp;
    for(int i = 1; i <= n; ++i) {
        nodos_disp.push_back(i);
    }

    vector<int> nodos_visitados;

    //calcular ruta de cada vehiculo
    //=========================GREEDY=======================================
    for(int j = 0; j < cant; ++j) {                         //para cada auto
        bool fin = false;
        while (!fin) {                                      //mientras no termine el recorrido
        float min = 9999999999;
        int numero_nodo_min;
            for(int i = 0; i < nodos_disp.size(); ++i) {    //recorrer cada nodo
                float d = vehiculos.at(j).dist(nodos.at(i));
                //cout << "I: " << i << " J: " << j << " d: " << d << endl;
                if (d != 0){
                    if (vehiculos.at(j).ruta.empty()) { //ruta vacia siosi parte con linehaul
                        if (nodos.at(i).tipo == 1) {
                            if(d < min && not_in(nodos_disp.at(i), nodos_visitados)) {
                                min = d;
                                numero_nodo_min = nodos_disp.at(i);
                            }
                        }
                    } else {
                        if(d < min && not_in(nodos_disp.at(i), nodos_visitados)) {
                            min = d;
                            numero_nodo_min = nodos_disp.at(i);
                        }
                    }
                }
            }
            //cout << "min: " << min << " N nodo: " << numero_nodo_min << endl;
            if (min == 9999999999) { //no quedan nodos disponibles
                fin = true;
            } else {
                if (numero_nodo_min != 1) { //siempre se puede volver al deposito
                    nodos_visitados.push_back(numero_nodo_min);
                }

                vehiculos.at(j).add_ruta(numero_nodo_min);
                vehiculos.at(j).add_peso(nodos.at(numero_nodo_min-1).demanda);
                vehiculos.at(j).set_pos(nodos.at(numero_nodo_min-1).coordX, nodos.at(numero_nodo_min-1).coordY);
                vehiculos.at(j).add_dist(min);
                //vehiculos.at(j).print();

                fin = vehiculos.at(j).recorrido_terminado();
                //fin = true;
            }
        }
        vehiculos.at(j).print();
    }
    //=========================GREEDY=======================================

    return 0;
}