#include <vector>

using namespace std;

class conjunto_solucion {
    public:
        float calidad;
        solucion mejor_vecino;

        conjunto_solucion(float, solucion); //constructor

        //metodos
        void print();
        solucion mejor_vecino();
};