CC = g++
CFLAGS = -Wall -g
RM = rm -f
NOMBRE = proyecto
DEPS = main.o nodos.o vehiculos.o

all: $(NOMBRE)

$(NOMBRE): $(DEPS)
	$(CC) $(CFLAGS) -o $(NOMBRE) $(DEPS)
	./proyecto test

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(NOMBRE)
	$(RM) *.o

sol:
	$(RM) -r soluciones