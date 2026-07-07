all: program

program: main.o helper.o
	g++ -o program main.o helper.o

main.o: main.cpp helper.hpp
	g++ -c main.cpp

helper.o: helper.cpp helper.hpp
	g++ -c helper.cpp

clean:
	rm -f *.o program
