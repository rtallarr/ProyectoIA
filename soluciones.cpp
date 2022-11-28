#include <iostream>
#include <vector>

#include "nodos.hpp"
#include "vehiculos.hpp"
#include "soluciones.hpp"

solucion::solucion(float c, vector<vehiculo> v) {
    calidad = c;
    autos = v;
    mov = -1;
}

void solucion::print(bool factible) {
    if (factible) {
        cout << "Calidad: " << calidad << endl;
    } else {
        cout << "Solucion Infactible" << endl;
    }
    for (int i = 0; i < autos.size(); ++i) {
        //autos.at(i).print();
        cout << "  ruta " << i+1 << " (";
        for (int j = 0; j < autos.at(i).ruta.size(); ++j) {
            cout << " " << autos.at(i).ruta.at(j);
        }
        cout << ")\n";
    }
}

solucion solucion::mejor_vecino(vector<nodo> nodos, vector<int> lista_tabu) {
    int mejor_calidad = 99999999;
    solucion mejor(calidad, autos);
    for (int i = 0; i < autos.size(); ++i) {                     //para cada auto (ruta)
        if (!autos.at(i).ruta.empty()) {
            for(int j = 0; j < autos.at(i).ruta.size()-1; ++j) { //para cada nodo de la ruta, el ultimo es el 1 del deposito
                for (int k = 0; k < autos.size(); ++k) {         //recorrer cada ruta
                    //cout << "i: " << i << " j: " << j << " k: " << k << endl;
                    solucion copia(calidad, autos); //copia solucion (solucion candidata)
                    int num = autos.at(i).ruta.at(j);
                    nodo n = nodos.at(num-1);
                    copia.autos.at(i).ruta.erase(copia.autos.at(i).ruta.begin()+j); //borrar nodo de la ruta actual
                    //agregar a la ruta
                    if (n.tipo == 1) {          //nodo a mover es linehaul
                        //cout << "linehaul" << endl; 
                        copia.autos.at(k).ruta.insert(copia.autos.at(k).ruta.begin(), n.id);
                    } else if (n.tipo == 2) {   //nodo a mover es backhaul
                        //cout << "backhaul" << endl;
                        if (!copia.autos.at(k).ruta.empty()) {
                            copia.autos.at(k).ruta.pop_back(); 
                            copia.autos.at(k).ruta.push_back(n.id);
                            copia.autos.at(k).ruta.push_back(1);
                        } else {
                            copia.autos.at(k).ruta.push_back(n.id);
                        }
                    }

                    vector<int> bug = {1};
                    if (copia.autos.at(i).ruta == bug) {
                        copia.autos.at(i).ruta.clear();
                    }

                    if (copia.autos.at(i).ruta.size() == 1) {
                        copia.autos.at(i).ruta.push_back(nodos.at(0).id);
                    }
                    if (copia.autos.at(k).ruta.size() == 1) {
                        copia.autos.at(k).ruta.push_back(nodos.at(0).id);
                    }

                    //calcular las nuevas distancias
                    //siempre son 2 autos los que intercambian nodos
                    vector<nodo> nodos_para_recalcular1;
                    for (int m = 0; m < copia.autos.at(i).ruta.size(); m++) { //auto i
                        nodos_para_recalcular1.push_back(nodos.at(copia.autos.at(i).ruta.at(m)-1));
                    }

                    vector<nodo> nodos_para_recalcular2 = {};
                    for (int m = 0; m < copia.autos.at(k).ruta.size(); m++) { //auto k
                        nodos_para_recalcular2.push_back(nodos.at(copia.autos.at(k).ruta.at(m)-1));
                    }

                    //* print recalc
                    //cout << "recalc1: ";
                    //for (int m = 0; m < nodos_para_recalcular1.size(); ++m) {
                    //    cout << nodos_para_recalcular1.at(m).id;
                    //}
                    //cout << endl << "recalc2: ";
                    //for (int m = 0; m < nodos_para_recalcular2.size(); ++m) {
                    //    cout << nodos_para_recalcular2.at(m).id;
                    //}
                    //cout << endl;

                    // Calcular distancias
                    copia.autos.at(i).recalcularD(nodos_para_recalcular1);
                    copia.autos.at(k).recalcularD(nodos_para_recalcular2);

                    //* calcular la nueva calidad de la solucion
                    int cal = 0;
                    for (int l = 0; l < copia.autos.size(); ++l) {
                        cal += copia.autos.at(l).distancia_recorrida;
                    }
                    copia.calidad = cal;

                    //* Checkear factibilidad
                    bool solo_backhauls = false;
                    for (int m = 0; m < copia.autos.size(); m++) { //para cada auto
                        if (!copia.autos.at(m).ruta.empty()) {
                            if (nodos.at(copia.autos.at(m).ruta.at(0)-1).tipo == 2) {
                            solo_backhauls = true;
                            }
                        }
                    }

                    //Usar lista tabu
                    bool in_list = false;
                    if (copia.calidad < mejor_calidad && !solo_backhauls) {
                        if (copia.calidad != calidad) {
                            for (int m = 0; m < lista_tabu.size(); ++m) {
                                if (lista_tabu.at(m) == n.id) {
                                    in_list = true;
                                }
                            }
                            if (!in_list && i!=k) {
                                //cout << "mejor" << endl;
                                mejor = copia;
                                mejor_calidad = copia.calidad;
                                mejor.mov = n.id;
                            }
                        }
                    }

                    //* hacer solo_backhauls true para que tmb printee infactible
                    if (in_list) {
                        solo_backhauls = true; 
                    }

                    //* solucion generada por cada iteracion
                    copia.print(!solo_backhauls);
                }
            }
        }
    }
    //cout << "mejor: ";
    //mejor.print();
    //cout << "mejor vecino - mov: " << mov << endl;
    
    return mejor;
}