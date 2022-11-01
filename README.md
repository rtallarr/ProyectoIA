# Proyecto VRPwB

Se requiere de una carpeta de nombre `instancias` con los archivos `.txt` adentro ubicada en el mismo directorio.

### Comandos Makefile
1. Crea un ejecutable para linux y lo corre con GA1 por defecto.
```
make
```
2. Elimina el ejecutable y los archivos archivos intermedios creados en la fase de compilación.
```
make clean
```
3. Elimina la carpeta soluciones y sus contenidos.
```
make sol
```


### Ejecutar con otra instancia
Para correr el programa con otra instancia, se pasa como parametro del ejecutable. Por ejemplo para ejecutarlo con instancia/GA4.txt
```
./proyecto GA4
```