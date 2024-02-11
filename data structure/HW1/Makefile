all: wi

wi: walkIn.o List.o Patient.o
	g++ -Wall -o wi walkIn.o List.o Patient.o

walkIn.o: walkIn.cpp List.h Patient.h
	g++ -Wall -std=c++03 -c walkIn.cpp

List.o: List.h List.cpp
	g++ -Wall -std=c++03 -c List.cpp

Patient.o: Patient.h Patient.cpp
	g++ -Wall -std=c++03 -c Patient.cpp

clean:
	rm -f wi *.o