#include <iostream> //standard
#include <sys/stat.h> //mkdir
#include <bits/stdc++.h> //leer archivos
#include <vector>

#include "nodos.hpp"
#include "vehiculos.hpp"

using namespace std;

int main(int argc, char** argv) { //cambiar a otro archivo que genera una solucion para un archivo.
    int id, t, n;
    float x, y;
    vector<nodo> nodos; //lista de todos los nodos
    vector<vehiculo> vehiculos; //lista de autos

    ifstream file(argv[1]);

    //leer numero de nodos
    file >> n;
    cout << "N nodos: " << n << "\n";

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
    cout << "Cant Vehiculos: " << cant << " Capacidad: " << cap << endl;
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
        //v.print();
    }


    float min = 9999999999;
    int numero_nodo_min; //indice del mas cercano
    for(int i = 1; i < n; ++i) {
        float d = nodos.at(0).dist(nodos.at(i));
        //nodos.at(i).print();
        if(d < min) {
            min = d;
            numero_nodo_min = i+1;
        }
    }

    //cout << "min: " << min << "\n"
    //<< "numero nodo: " << numero_nodo_min;

    return 0;
}