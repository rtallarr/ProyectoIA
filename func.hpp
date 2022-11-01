#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

bool not_in(int x, vector<int> n) {
    for (int i = 0; i < n.size(); ++i) {
        if (x == n.at(i)) {
            return false;
        }
    }
    return true;
}

//(7 11 4 23 13 26 1 )
void crear_carpeta() {
    string path = "soluciones";
    int status = mkdir(path.c_str(), 0777);
    if (status == 0) {
        cout << "directorio soluciones creado\n";
    }
}