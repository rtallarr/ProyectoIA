#include <vector>

using namespace std;

class vehiculo {
    public:
        int id;
        int capacidad;
        int peso_actual;
        vector<int> ruta;

        vehiculo(int, int); //constructor

        //metodos
        void print();
};