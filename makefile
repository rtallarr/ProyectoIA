CC = g++
CFLAGS = -Wall -g
RM = rm -f
NOMBRE = proyecto
DEPS = main.o funciones.o nodos.o vehiculos.o

all: $(NOMBRE)

$(NOMBRE): $(DEPS)
	$(CC) $(CFLAGS) -o $(NOMBRE) $(DEPS)
	./proyecto GA1.txt

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(NOMBRE)
	$(RM) *.o

sol:
	$(RM) -r soluciones