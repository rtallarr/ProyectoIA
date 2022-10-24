#include <iostream> //standard
#include <sys/stat.h> //mkdir
#include <bits/stdc++.h> //leer archivos
#include <vector>

#include "nodos.hpp"
#include "vehiculos.hpp"

using namespace std;

int main() { //cambiar a otro archivo que genera una solucion para un archivo.
    int id, t, n;
    float x, y;
    vector<nodo> nodos; //lista de todos los nodos
    vector<vehiculo> vehiculos; //lista de autos

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
    float d;
    file >> cant >> cap;
    //cout << "Cant Vehiculos: " << cant << " Capacidad: " << cap << endl;
    
    //asignar demanda a cada nodo ¿?¿?¿?¿?
    for(int i = 1; i < n; ++i) { //id 1 => depot
        file >> id >> d;
        if (id != 0) {
            cout << id;
        }
        nodos.at(i).demanda = d;
        //cout << nodos.at(i).demanda;
    }

    //crear vehiculos
    for(int i = 1; i <= cant; ++i) {
        vehiculo v = vehiculo(i, cap);
        vehiculos.push_back(v);
        v.set_pos(nodos.at(0).coordX, nodos.at(0).coordY); //pos inicial = depot
        //v.print();
    }

    vehiculos.at(0).print();

    //nodos disponibles para visitar
    vector<int> nodos_disp;
    for(int i = 0; i < n; ++i) {
        nodos_disp.push_back(i);
    }

    //calcular el linehaul mas cercano al depot
    float min = 9999999999;
    int numero_nodo_min; //indice del mas cercano
    for(int j = 0; j < 1; ++j) {
        for(int i = 0; i < nodos_disp.size(); ++i) {
            float d = vehiculos.at(j).dist(nodos.at(i));
            //cout << "I: " << i << " J: " << j << " d: " << d << endl;
            if (d != 0){
                if (vehiculos.at(j).ruta.empty()) { //ruta vacia siosi parte con linehaul
                    if (nodos.at(i).tipo == 1) {
                        if(d < min) {
                            min = d;
                            numero_nodo_min = i+1;
                            //cout << "N nodo: " << numero_nodo_min << endl;
                        }
                    }
                } else {
                    if(d < min) {
                        min = d;
                        numero_nodo_min = i+1;
                        //cout << "N nodo: " << numero_nodo_min << endl;
                    }
                }
            }
        }
        cout << "min: " << min << " N nodo: " << numero_nodo_min << endl;

        vehiculos.at(j).add_ruta(numero_nodo_min);
        vehiculos.at(j).add_peso(nodos.at(numero_nodo_min-1).demanda);
        vehiculos.at(j).set_pos(nodos.at(numero_nodo_min-1).coordX, nodos.at(numero_nodo_min-1).coordY);
        vehiculos.at(j).add_dist(nodos.at(j).dist(nodos.at(numero_nodo_min-1)));
        //vehiculos.at(j).print();
    }

    return 0;
}