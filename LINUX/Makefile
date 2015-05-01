CC=gcc
FLAGS=`pkg-config --cflags --libs gtk+-2.0`
EXEC=ppm_editor

all: $(EXEC) clean

ppm_editor: main.o fenetre_image.o callback.o menu.o error.o save.o ppm.o structures.h
	$(CC) -o $@ $^ $(FLAGS)

main.o: main.c
	$(CC) -o $@ -c $< $(FLAGS)

fenetre_image.o: fenetre_image.c
	$(CC) -o $@ -c $< $(FLAGS)

callback.o: callback.c
	$(CC) -o $@ -c $< $(FLAGS)

menu.o: menu.c
	$(CC) -o $@ -c $< $(FLAGS)

error.o: error.c
	$(CC) -o $@ -c $< $(FLAGS)

save.o: save.c
	$(CC) -o $@ -c $< $(FLAGS)

ppm.o: ppm.c
	$(CC) -o $@ -c $< $(FLAGS)

clean:
	rm -rf *.o *~


