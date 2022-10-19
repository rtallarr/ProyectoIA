CC = g++
CFLAGS = -Wall -g
NOMBRE = proyecto

all: $(NOMBRE)

$(NOMBRE): main.o funciones.o
	$(CC) $(CFLAGS) -o $(NOMBRE) main.o funciones.o 
	./proyecto

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f proyecto
	rm *.o