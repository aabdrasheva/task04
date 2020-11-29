﻿// homework4_arc.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <omp.h>

//вывод матриц в консоль (вывод матриц А и В не прописан в условии, 
//но для понимамания, что именно мы должны умножать, удобно будет их все же вывести)
void matrixPrint(int** matrix, int matrixSize)
{
	for (size_t i = 0; i < matrixSize; i++)
	{
		for (size_t j = 0; j < matrixSize; j++)
		{
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << "\n";
	}
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

		int** A = new int* [matrixSize];
		int** B = new int* [matrixSize];
		int** resultMatrix = new int* [matrixSize];

		// заполнение массивов A и B
		for (size_t i = 0; i < matrixSize; i++)
		{
			A[i] = new int[matrixSize];
			B[i] = new int[matrixSize];
			resultMatrix[i] = new int[matrixSize];
			for (size_t j = 0; j < matrixSize; j++)
			{
				A[i][j] = rand() % 20; //числа от рандома получаются слишком большими, просто для удобства возьмем остатки от деления на 20
				B[i][j] = rand() % 20;
				resultMatrix[i][j] = 0;
			}
		}

		std::cout << "A matrix:" << std::endl;
		//вывод первой матрицы
		matrixPrint(A, matrixSize);
		std::cout << "\n";


		std::cout << "B matrix:" << std::endl;
		//вывод второй матрицы
		matrixPrint(B, matrixSize);
		std::cout << "\n";

		std::thread* thr = new std::thread[threadsNum];

		omp_set_num_threads(threadsNum);
		// Создание потоков
		#pragma omp parallel
		{
			auto count = omp_get_thread_num();
			if (matrixSize % threadsNum != 0) {
				for (int k = count; k < matrixSize; k += threadsNum) {
					//вычисление элементов матрицы, стоящих в строке k
					for (int i = 0; i < matrixSize; i++) {
						resultMatrix[k][i] = 0;
						for (int j = 0; j < matrixSize; j++) {
							resultMatrix[k][i] += A[k][j] * B[j][i];
						}
					}
				}
			}
		}

		std::cout << "\n";
		std::cout << "Result matrix = A * B" << std::endl;
		std::cout << "Result matrix:" << std::endl;
		//вывод итоговой матрицы resultMatrix = A*B
		matrixPrint(resultMatrix, matrixSize);

		//освобождение памяти для каждого элемнта A[i]
		for (int i = 0; i < matrixSize; i++)
			delete[] A[i];
		//освобождение памяти B
		delete[] A;
		//освобождение памяти для каждого элемнта B[i]
		for (int i = 0; i < matrixSize; i++)
			delete[] B[i];
		//освобождение памяти A
		delete[] B;
		//освобождение памяти для каждого элемнта resultMatrix[i]
		for (int i = 0; i < matrixSize; i++)
			delete[] resultMatrix[i];
		//освобождение памяти resultMatrix
		delete[] resultMatrix;
	}
	system("pause");
	return 0;
}