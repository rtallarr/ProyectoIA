#include <iostream> //standard
#include <sys/stat.h> //crear directorio

#include "funciones.hpp"
#include "nodos.hpp"

using namespace std;

int main() {
    cout << "Iniciando programa!\n";
    string numero_de_elementos = numero_elementos("GA1.txt");
    cout << numero_de_elementos << endl;

    nodo dep = nodo(1, 0, 3.0, 4.0);
    dep.print();

    string path = "soluciones";
    int status = mkdir(path.c_str(), 0777);

    if(status == 0){
        cout << "directorio soluciones creado\n";
    } 

    return 0;
}