using namespace std;

class nodo {
    public:
        int tipo;
        int ID;
        float coordX;
        float coordY;

        nodo(int t, int i, float x, float y){
            tipo = t;
            ID = i;
            coordX = x;
            coordY = y;
        }
};