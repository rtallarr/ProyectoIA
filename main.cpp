#include <iostream> //standard
#include <sys/stat.h> //mkdir
#include <bits/stdc++.h> //leer archivos
#include <vector>
#include <bits/stdc++.h> //calcular tiempo ejecucion
#include <chrono>

#include "nodos.hpp"
#include "vehiculos.hpp"
#include "func.hpp"
#include "soluciones.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    auto start = chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);

    int id, t, n;
    float x, y;
    vector<nodo> nodos;             //lista de todos los nodos
    vector<vehiculo> vehiculos;     //lista de autos

    string nombre_archivo = argv[1];
    ifstream file("instancias/"+nombre_archivo+".txt");

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

    int cant;
    int otro_id;
    float d, cap;
    file >> cant >> cap;
    //cout << "Cant Vehiculos: " << cant << " Capacidad: " << cap << endl;
    
    //asignar demanda a cada nodo
    for(int i = 1; i < n; ++i) { //id 1 => depot
        file >> otro_id >> d;
        nodos.at(i).set_d(d);
        //nodos.at(i).print();
    }

    file.close();

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
        //cout << "i: " << i << endl;
    }

    vector<int> nodos_visitados;

    //=========================GREEDY=======================================
    for(int j = 0; j < cant; ++j) {                         //para cada auto
        bool fin = false;
        bool recorriendo_backhauls = false;
        while (!fin) {                                      //mientras no termine el recorrido
        double min = 9999999999;
        int numero_nodo_min;
            for(int i = 0; i < nodos_disp.size(); ++i) {    //recorrer cada nodo buscando el mas cercano
                float d = vehiculos.at(j).dist(nodos.at(i));
                //cout << "I: " << i << " J: " << j << " d: " << d << endl;
                if (d != 0) {
                    if (d < min && not_in(nodos_disp.at(i), nodos_visitados)) {
                        if (vehiculos.at(j).ruta.empty()) { //ruta vacia siosi parte con linehaul
                            if (nodos.at(i).tipo == 1) {
                                min = d;
                                numero_nodo_min = nodos_disp.at(i);
                            }
                        } else { //no anotar un linehaul dps de un backhaul
                            if (nodos.at(i).tipo == 1) {
                                if (vehiculos.at(j).demandaL + nodos.at(i).demanda <= cap) {
                                    if (!recorriendo_backhauls) {
                                        min = d;
                                        numero_nodo_min = nodos_disp.at(i);      
                                    }
                                }
                            } else if (nodos.at(i).tipo == 2) {
                                if (vehiculos.at(j).demandaB + nodos.at(i).demanda <= cap) {
                                    if (!recorriendo_backhauls) {                              
                                        min = d;
                                        numero_nodo_min = nodos_disp.at(i);
                                        recorriendo_backhauls = true;
                                    } else {
                                        min = d;
                                        numero_nodo_min = nodos_disp.at(i);
                                    }
                                }
                            } else { //deposito                        
                                min = d;
                                numero_nodo_min = nodos_disp.at(i);
                            }
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
                if (nodos.at(numero_nodo_min-1).tipo == 1) { //linehaul
                    vehiculos.at(j).add_l(nodos.at(numero_nodo_min-1).demanda);
                } else { //backhaul
                    vehiculos.at(j).add_b(nodos.at(numero_nodo_min-1).demanda);
                }
                vehiculos.at(j).add_ruta(numero_nodo_min);
                vehiculos.at(j).set_pos(nodos.at(numero_nodo_min-1).coordX, nodos.at(numero_nodo_min-1).coordY);
                vehiculos.at(j).add_dist(min);
                //vehiculos.at(j).print();

                fin = vehiculos.at(j).recorrido_terminado();
                //fin = true;
            }
        }
        //vehiculos.at(j).print();
    }
    //=====agregar los nodos que no se visitaron al primer vehiculo=====
    vector<int> faltantes = nodos_faltantes(nodos_disp, nodos_visitados);
    //print
    //for(int i = 0; i < faltantes.size(); ++i) {
    //    cout << faltantes.at(i);
    //}

    for (int i = 1; i < faltantes.size(); i++) { //el deposito siempre falta, pq no se agrega
        //cout << "falta: " << faltantes.at(i) << endl;
        //nodos.at(faltantes.at(i)-1).print();
        for (int j = 0; j < vehiculos.size(); ++j) {
            if (nodos.at(faltantes.at(i)-1).tipo == 1) { //si es linehaul agregar el inicio de la ruta
                if (vehiculos.at(j).demandaL + nodos.at(faltantes.at(i)-1).demanda <= cap) {
                    vehiculos.at(j).ruta.insert(vehiculos.at(j).ruta.begin(), faltantes.at(i));
                    vehiculos.at(j).add_l(nodos.at(faltantes.at(i)-1).demanda);
                    break;
                }
            } else {
                if (vehiculos.at(j).demandaB + nodos.at(faltantes.at(i)-1).demanda <= cap) {
                    vehiculos.at(j).add_ruta_faltante(faltantes.at(i));
                    vehiculos.at(j).add_b(nodos.at(faltantes.at(i)-1).demanda);
                    break;
                }
            }
        }
    }

    //vehiculos.front().print();
    vector<nodo> nodos_para_recalcular;
    for(int i = 0; i < vehiculos.front().ruta.size(); ++i) {
        nodos_para_recalcular.push_back(nodos.at(vehiculos.front().ruta.at(i)-1));
    }

    //print nodos para recalcular
    //for(int i = 0; i < nodos_para_recalcular.size(); ++i) {
    //    nodos_para_recalcular.at(i).print();
    //}

    vehiculos.front().recalcularD(nodos_para_recalcular);
    cout << endl;

    //printeo de autos
    //for (int i = 0; i < cant; i++) {
    //    vehiculos.at(i).print();
    //}
    
    
    //=========================TABU SEARCH=======================================
    int calidad = 0;
    int largo_lista = nodos.size()/7;
    //cout << "largo list: " << largo_lista << endl;
    int numero_iteraciones = 250;
    vector<int> lista_tabu = {};
    
    for (int i = 0; i < vehiculos.size(); ++i) {
        calidad += vehiculos.at(i).distancia_recorrida;
    }

    solucion mejor_solucion = solucion(calidad, vehiculos);
    solucion solucion_actual = solucion(calidad, vehiculos); // al inicio mejor solucion = actual

    cout << "Iteracion 1 (greedy): \n";
    solucion_actual.print();
    cout << endl;

    for (int i = 0; i < numero_iteraciones; ++i) {
        solucion_actual = solucion_actual.mejor_vecino(nodos, lista_tabu);
        lista_tabu.push_back(solucion_actual.mov);
        //cout << "mejor vecino - mov: " << solucion_actual.mov << endl;

        //* eliminar elemento mas antiguo
        if (lista_tabu.size() > largo_lista) {
            lista_tabu.erase(lista_tabu.begin()); 
        }
        
        if (solucion_actual.calidad < mejor_solucion.calidad) {
            //cout << "actual: " << solucion_actual.calidad << " mejor: " << mejor_solucion.calidad << endl;
            mejor_solucion = solucion_actual;
        }

        //* prints
        cout << "Iteracion " << i+2 << ":\n";
        cout << "  main calidad actual: " << solucion_actual.calidad << endl;
        solucion_actual.print();
        cout << "   Lista tabu:";
        for (int j = 0; j < lista_tabu.size(); ++j) {
            cout << " " << lista_tabu.at(j);
        }
        cout << "\n" << endl;
    }

    cout << "\nMejor solucion final: ";
    mejor_solucion.print();



    //========================OUTPUT======================================
    auto end = chrono::high_resolution_clock::now();
    double tiempo = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    tiempo *= 1e-9;

    int nClientes = n;
    int nVehiculos = 0;

    for (int i = 0; i < mejor_solucion.autos.size(); ++i) {
        if (!mejor_solucion.autos.at(i).ruta.empty()) {
            nVehiculos += 1;
        }
    }

    crear_carpeta();

    ofstream out("soluciones/"+nombre_archivo+".out");
    out << to_string((int)mejor_solucion.calidad) << " " << to_string(nClientes) << " " << to_string(nVehiculos) << " " << to_string(tiempo) << "\n";
    for(int i = 0; i < nVehiculos; ++i) {      //por cada auto
        out << "1-";
        for(int j = 0; j < mejor_solucion.autos.at(i).ruta.size(); ++j) {  //por cada id en la ruta
            out << mejor_solucion.autos.at(i).ruta.at(j);
            if (j+1 != mejor_solucion.autos.at(i).ruta.size()) {
                out << "-";
            } else {
                out << " ";
            }
        }
        out << mejor_solucion.autos.at(i).distancia_recorrida << " " << mejor_solucion.autos.at(i).demandaL << " " << mejor_solucion.autos.at(i).demandaB << "\n";
    }

    out.close();
    cout << "\nArchivo " << nombre_archivo << ".out" << " generado\n";

    return 0;
}