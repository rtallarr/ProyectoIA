#include <iostream> //standard
#include "funciones.hpp"
using namespace std;

int main() {
    cout << "Iniciando programa!\n";
    string numero_de_elementos = numero_elementos("GA1.txt");
    cout <<  numero_de_elementos << endl;

    return 0;
}