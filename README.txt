Se asume que existe una carpeta llamada instancias con los archivos txt dentro
ubicada en este mismo directorio y que tiene por lo menos la instancia GA1s.

El makefile crea un ejecutable para linux. Con el comando basico make se compilan todos los
archivos necesarios y se corre el programa con la instancia "GA1" por defecto. Para correr otra instancia
se debe pasar el nombre del archivo como parametro. Por ejemplo ./proyecto instancias/GA4.txt

make sol - elimina la carpeta con las soluciones
make clean - elimina los archivos compilados.