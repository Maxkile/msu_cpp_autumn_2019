#include "Timer.cpp"


int main(int argc, char const *argv[])
{
	const int32_t rows = 500;
	const int32_t cols = 500;
	const int32_t range = 10;

	std::srand(std::time(0));

	int32_t matr1[rows][cols];
	int32_t matr2[rows][cols];
	volatile int32_t res[rows][cols];

	for(int i = 0;i<cols;++i)
	{
		for(int j = 0;j<cols;++j)
		{
			matr1[i][j] = std::rand() % range;
			matr2[i][j] = std::rand() % range;
		}
	}

	Timer t;

	for(int i = 0;i<rows;++i)
	{
		for(int j = 0;j<cols;++j)
		{
			res[i][j] = matr1[i][j] + matr2[i][j];
		}
	}
	
}