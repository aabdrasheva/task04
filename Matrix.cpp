#include <iostream>
#include <omp.h>

using namespace std;

//вывод матриц в консоль (вывод матриц А и В не прописан в условии, 
//но для понимамания, что именно мы должны умножать, удобно будет их все же вывести)
void matrixPrint(int* matrix[], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}
int main()
{
	//вводимые пользователем значения размера матрицы и количества потоков
	int matrixSize;
	int threadsNum;

	std::cout << "input matrix size: ";
	std::cin >> matrixSize;
	std::cout << "input threads number: ";
	std::cin >> threadsNum;

	//обработка данных
	if (threadsNum <= 0 || matrixSize <= 0)
	{
		std::cout << "Wrong! Threads number or matrix size can not be less than 0." << std::endl;
	}
	else if (threadsNum > matrixSize)
	{
		std::cout << "Wrong! Threads number can not be more than matrix size." << std::endl;
	}
	else {
		int i, j, k;

		int** A = new int* [matrixSize];
		int** B = new int* [matrixSize];
		int** resultMatrix = new int* [matrixSize];

		for (int i = 0; i < matrixSize; i++)
		{
			A[i] = new int[matrixSize];
			B[i] = new int[matrixSize];
			resultMatrix[i] = new int[matrixSize];
		}


		// заполнение массивов A и B
		for (i = 0; i < matrixSize; i++) {
			for (j = 0; j < matrixSize; j++)
			{
				A[i][j] = rand() % 20; //числа от рандома получаются слишком большими, просто для удобства возьмем остатки от деления на 20
				B[i][j] = rand() % 20;
				resultMatrix[i][j] = 0;
			}
		}

		cout << "A matrix" << endl;
		//вывод первой матрицы
		matrixPrint(A, matrixSize);
		cout << "B matrix" << endl;

		//вывод второй матрицы
		matrixPrint(B, matrixSize);

		omp_set_num_threads(threadsNum);

#pragma omp parallel shared(a,b,c) private(i,j,k) 
		{
#pragma omp for  schedule(static)
			for (i = 0; i < matrixSize; i++)
				for (j = 0; j < matrixSize; j++)
					for (k = 0; k < matrixSize; k++)
						resultMatrix[i][j] += (A[i][k] * B[k][j]);
		}

		std::cout << "\n";
		std::cout << "Result matrix = A * B" << std::endl;
		std::cout << "Result matrix:" << std::endl;
		matrixPrint(resultMatrix, matrixSize);
	}
	return EXIT_SUCCESS;
}