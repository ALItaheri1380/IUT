
infixeval:	Scanner.o Eval.o
	g++ -o infixeval Scanner.o Eval.o -std=c++0x

Scanner.o:	Scanner.cpp Scanner.h
	g++ -c Scanner.cpp -std=c++0x
	
Eval.o:	Eval.cpp Scanner.h Stack.h
	g++ -c Eval.cpp -std=c++0x
	
clean:	
	rm -f *.o infixeval

