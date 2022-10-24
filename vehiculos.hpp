#include <vector>

using namespace std;

class vehiculo {
    public:
        int id;
        int capacidad;
        int peso_actual;
        float distancia_recorrida;
        vector<float> posicion;
        vector<int> ruta;

        vehiculo(int, int); //constructor

        //metodos
        void print();
        void add_ruta(int);
        void add_peso(int);
        void set_pos(float x, float y);
        void add_dist(float d);
        float dist(nodo uno);
};