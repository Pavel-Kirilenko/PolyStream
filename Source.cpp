#include <iostream>
#include <chrono>
#include "Header.h"

using namespace std;
using namespace std::chrono;

int main()
{
	long long totalSum = 0;    // Сумма случайных чисел массива
	vector <int> rndArray;     // Определить массив случайных чисел
   
	int streamsNumber[] = { 1, 2, 4, 8, 10 };                // Массив со значениями количества потоков
	long long arrayLength[] = { 10000, 1000000, 10000000 };  // Массив со значениями длины массива случайных чисел 

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			srand(std::time(0));

			for (long long k = 0; k < arrayLength[i]; k++)   // Заполнить массив случайными числами
			{
				rndArray.push_back(rand() % 65535 + 0);
			}

			cout << "For length = " << arrayLength[i] << " and stream's number = " << streamsNumber[j] << "   ";

			auto start = high_resolution_clock::now();       // Начало измерения времени

			totalSumCounter(arrayLength[i], streamsNumber[j], rndArray);

			auto end = high_resolution_clock::now();         // Конец измерения времени

			auto duration = duration_cast<microseconds>(end - start);             // Вычислить время в микросекундах
			cout << "Time of executing: " << duration.count() << " mks" << endl;  // Вывести время в микросекундах
		}
	}

	return 0;
}