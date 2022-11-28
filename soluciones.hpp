#include <vector>

using namespace std;

class solucion {
    public:
        float calidad;
        vector<vehiculo> autos;
        int mov;

        solucion(float, vector<vehiculo>); //constructor

        //metodos
        void print(bool = true);
        solucion mejor_vecino(vector<nodo>, vector<int>);
};