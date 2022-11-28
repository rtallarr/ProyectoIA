# Proyecto VRPwB

## Instrucciones de uso
Se requiere de una carpeta de nombre `instancias` con los archivos `.txt` adentro ubicada en el mismo directorio.

### Comandos Makefile
1. Crea un ejecutable para linux y lo corre con GA1 por defecto.
```
make
```
2. Elimina el ejecutable y los archivos intermedios creados en la fase de compilación.
```
make clean
```
3. Elimina la carpeta soluciones y sus contenidos.
```
make sol
```


### Ejecutar con otra instancia
Para correr el programa con otra instancia, se pasa como parametro del ejecutable. Por ejemplo, para correrlo con la instancia `instancias/GA4.txt`
```
./proyecto GA4
```

## Pendientes
#### Greedy
- [x] Greedy
- [x] Tiempo de ejecucion
- [x] Bug pesos y demandas
- [x] Respetar capacidad
- [x] Backhauls depues de linehauls
- [x] Asegurar pasar por todos los nodos
- [x] Bug nodo duplicado en agregar nodos faltantes
- [ ] Respetar capacidad anexado de nodos faltantes
#### Tabu Search
- [x] Bug insert despues del deposito
- [x] Usar lista tabu
- [x] Bug ruta 1-1
- [ ] Capacidades
- [ ] Bug distancias