main: MatrSum.o main.o
	g++ -Wall -Werror main.o MatrSum.o -o main --std=c++14
MatrSum.o: MatrSum.hpp MatrSum.cpp
	g++ -Wall -Werror -c MatrSum.cpp --std=c++14
main.o: main.cpp
	g++ -Wall -Werror -c main.cpp --std=c++14
clean:
	rm *.o
run:
	./main
test:
	python3 ./tester.py
