#include <vector>

using namespace std;

class vehiculo {
    public:
        int id;
        int capacidad;
        int demandaL;
        int demandaB;
        double distancia_recorrida;
        vector<float> posicion;
        vector<int> ruta;

        vehiculo(int, int); //constructor

        //metodos
        void print();
        void add_ruta(int);
        void add_ruta_faltante(int);
        void recalcularD(vector<nodo>);
        void add_l(int);
        void add_b(int);
        void rem_l(int);
        void rem_b(int);
        void set_pos(float x, float y);
        void add_dist(double d);
        double dist(nodo uno);
        bool recorrido_terminado();
        bool recorriendo_backhauls();
};