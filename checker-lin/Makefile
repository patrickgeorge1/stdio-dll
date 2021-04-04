CFLAGS = -Wall -fPIC
CC = gcc

build:	libso_stdio.so

libso_stdio.so:	util/so_stdio.o
	$(CC) -shared -o libso_stdio.so util/so_stdio.o $(CFLAGS)

so_stdio.o: util/so_stdio.c

clean:
	rm -rf *.o util/*.o libso_stdio.so main


main: libso_stdio.so main.c
	$(CC) main.c -o main -lso_stdio -L.

run: main
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.  ./main