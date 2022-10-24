
string path = "soluciones";
int status = mkdir(path.c_str(), 0777);
if(status == 0) {
        cout << "directorio soluciones creado\n";
}