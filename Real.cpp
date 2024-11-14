#include <iostream>
#include <vector>
#include <ctime>
#include <thread>
#include <algorithm>
#include <mutex> 
#include "Header.h"

using namespace std;

void  totalSumCounter(int arrayLength, short partsNumber, vector <int> rndArray) // Функция подсчета суммы элементов массива с использованием метода многопоточности
{
	int lpCt = 0;              // Счетчик циклов
	long long totalSum = 0;    // Сумма случайных чисел массива
	vector <thread> streams;   // Определить массив потоков
	mutex mtx;                 // Мьютекс для защиты totalSum

	auto sumComputer = [&totalSum, &rndArray, &mtx](int start, int end) // Лямбда-функция
		{
			long long localSum = 0;             // Локальная сумма для каждого потока
			for (int i = start; i <= end; i++)
			{
				localSum += rndArray.at(i);
			}
			lock_guard<mutex> lock(mtx);        // Защитит доступ к totalSum
			totalSum += localSum;
		};

	int localArrLength = arrayLength / partsNumber;

	int startOfArray = 0;  // Начало участка массива
	int endOfArray = 0;    // Конец участка массива
	while (endOfArray < arrayLength - 1)
	{
		lpCt = 0;
		endOfArray = startOfArray + localArrLength - 1;
		if (endOfArray > arrayLength - 1) endOfArray = arrayLength - 1;

		streams.push_back(std::thread(sumComputer, startOfArray, endOfArray)); // Передать аргументы

		startOfArray = endOfArray + 1;
		lpCt++;
	}

	std::for_each(streams.begin(), streams.end(), [](std::thread& t)
		{ t.join(); });

	cout << "Sum is: " << totalSum << "   ";
}