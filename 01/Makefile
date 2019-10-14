main: main.o CalcSimple.o
	g++ main.o CalcSimple.o -o main --std=c++14
main.o: main.cpp
	g++ -Wall -Werror -O2 -c main.cpp --std=c++14
CalcSimple.o: CalcSimple.cpp
	g++ -Wall -Werror -O2 -c CalcSimple.cpp --std=c++14
clean:
	rm -r *.o
run:
	./test "13-12/12 + 213123 - 12 / 2"
test:
	python3 ./tester.py 