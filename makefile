CC = g++
CFLAGS = -Wall -g
NOMBRE = proyecto
DEPS = main.o funciones.o nodos.o

all: $(NOMBRE)

$(NOMBRE): $(DEPS)
	$(CC) $(CFLAGS) -o $(NOMBRE) $(DEPS)
	./proyecto

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f proyecto
	rm -f *.o