CPPFLAGS = -g -c -Wall -Wextra -ansi -DNDEBUG
OBJECT1 = main.o
BIN1 = main


all: main
	rm -f $(OBJECT1)

main: main.o
	g++ -o main $(OBJECT1)

main.o: main.cpp main.hpp grafo.hpp lado.hpp vertice.hpp
	g++ $(CPPFLAGS) main.cpp

clean:
	rm -f $(OBJECT1) $(BIN1)
