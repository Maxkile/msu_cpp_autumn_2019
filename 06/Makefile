all: main.o format.o
	g++ -Wall -Werror main.o format.o -o main -std=c++17
main: main.cpp
	g++ -Wall -Werror -c main.cpp -std=c++17
format: format.hpp format.cpp
	g++ -Wall -Werror -c format.cpp -std=c++17
clear:
	rm -r *.o
uninstall:
	rm main
test:
	./main
