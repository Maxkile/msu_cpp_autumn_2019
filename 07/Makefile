all: MyVector.hpp MyIterator.hpp MyAllocator.hpp
	g++ -Wall -Werror main.cpp -o main -std=c++17
clear:
	rm -r *.o
uninstall:
	rm main
test:
	valgrind --leak-check=full --track-origins=yes -v ./main 
run:
	./main
