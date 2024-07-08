
all:	x

x:	Queue.o main.o
	g++ -o x Queue.o main.o

Queue.o:	Queue.cpp Queue.h
	g++ -c Queue.cpp

main.o:	main.cpp Queue.h
	g++ -c main.cpp

clean:	
	rm -f x *.o

