all: ThreadPool.o test.o
	g++ ThreadPool.o test.o -pthread -o test -std=c++17
test: test.o
	g++ -c test.cpp -std=c++17
threadpool: ThreadPool.cpp ThreadPool.hpp 
	g++ -c ThreadPool.cpp -std=c++17
clear:
	rm -r *.o
uninstall:
	rm test