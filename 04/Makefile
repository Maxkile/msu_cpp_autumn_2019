main: main.o BigInteger.o
	g++ -Wall -Werror main.o BigInteger.o -o main
BigInteger.o: BigInteger.hpp BigInteger.cpp
	g++ -Wall -Werror -c  BigInteger.cpp
main.o: main.cpp
	g++ -Wall -Werror -c  main.cpp
clear:
	rm -r *.o
uninstall:
	rm main
test:
	python3 tester.py
