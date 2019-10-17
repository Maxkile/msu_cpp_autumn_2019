test: test.o allocator.o
	g++ test.o allocator.o -o test --std=c++14
test.o: test.cpp
	g++ -Wall  -O2 -c test.cpp --std=c++14
allocator.o: allocator.cpp allocator.hpp
	g++ -Wall  -O2 -c allocator.cpp --std=c++14
clean:
	rm -r *.o
run:
	./test
test: