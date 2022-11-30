#include <vector>

using namespace std;

class solucion {
    public:
        double calidad;
        vector<vehiculo> autos;
        int mov;

        solucion(double, vector<vehiculo>); //constructor

        //metodos
        void print(bool = true);
        solucion mejor_vecino(vector<nodo>, vector<int>);
};