all: compile

compile: main.o mylib.a
	gcc main.o -L./ -lmylib -o app.out

main.o: main.c lib.h
	gcc -c main.c -o main.o

mylib.a: lib.o
	ar -r libmylib.a lib.o

lib.o: lib.c lib.h
	gcc -c lib.c -o lib.o

clean:
	rm -f mylib.a app *.o
