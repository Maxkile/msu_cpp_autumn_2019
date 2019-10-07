all: sum_by_columns sum_by_rows

sum_by_columns: MatrixSumByColumns.o Timer.o
	g++ -Wall  MatrixSumByColumns.o Timer.o -o sum_by_columns --std=c++14 -O2
sum_by_rows: MatrixSumByRows.o Timer.o
	g++ -Wall  MatrixSumByRows.o Timer.o -o sum_by_rows --std=c++14 -O2	
MatrixSumByColumns.o: MatrixSumByColumns.cpp
	g++ -c MatrixSumByColumns.cpp --std=c++14 -O2
MatrixSumByRows.o: MatrixSumByRows.cpp
	g++ -c MatrixSumByRows.cpp --std=c++14 -O2
Timer.o: Timer.cpp 
	g++ -c Timer.cpp --std=c++14 -O2
clean:
	rm -rf *.o
run:
	./sum_by_columns
	./sum_by_rows
