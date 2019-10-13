test: test.o CalcList.o
	g++ test.o CalcList.o -o test --std=c++14
test.o: test.cpp
	g++ -Wall -Werror -O2 -c test.cpp --std=c++14
CalcList.o: CalcList.cpp
	g++ -Wall -Werror -O2 -c CalcList.cpp --std=c++14
clean:
	rm -r *.o
run:
	./test