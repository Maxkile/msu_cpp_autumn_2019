all: main.o 
	g++ -Wall -Werror -pthread main.o -o main
main.o: main.cpp BinSort.hpp
	g++ -Wall -Werror -c main.cpp -std=c++17
test:
	./main "input.txt" "output.txt"
clear:
	rm -r *.o
uninstall:
	rm main	
check:
	valgrind --leak-check=full -v  ./main input.txt output.txt