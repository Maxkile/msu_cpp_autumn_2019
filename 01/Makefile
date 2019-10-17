main: main.o Calc.o
	g++ main.o Calc.o -o main --std=c++14
main.o: main.cpp
	g++ -Wall  -O2 -c main.cpp --std=c++14
Calc.o: Calc.cpp Calc.hpp
	g++ -Wall  -O2 -c Calc.cpp --std=c++14
clean:
	rm -r *.o
run:
	./test "13-12/12 + 213123 - 12 / 2"
test:
	python3 ./tester.py 