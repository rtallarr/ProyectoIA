class nodo {
    public:
        int tipo;
        int id;
        float coordX;
        float coordY;
        float demanda;

        nodo(int, int, float, float); //constructor
        
        //metodos
        void print();
        float dist(nodo);
};