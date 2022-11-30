CC = g++
CFLAGS = -Wall -g
RM = rm -f
NOMBRE = proyecto
DEPS = main.o nodos.o vehiculos.o soluciones.o

all: $(NOMBRE)

$(NOMBRE): $(DEPS)
	$(CC) $(CFLAGS) -o $(NOMBRE) $(DEPS)
	./proyecto GA1

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(NOMBRE)
	$(RM) *.o

sol:
	$(RM) -r soluciones