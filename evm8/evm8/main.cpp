#include <iostream>
#include <intrin.h> 


void main() {
	int Nmin = 1024 / 4; // 256
	int Nmax = 32 * 1024 * 1024 / 4; // 8388608
	//int Nmax = 512;
	int K = 100; // Кол-во проходов по массиву размера n
	float k = 1; // Скорость роста размера массива в цикле
	int R = 10; // Кол-во проходов для выбора наименьшего значения времени
	int* arr;
	unsigned __int64 start;
	unsigned __int64 end;
	float straight = 0;
	float back = 0;
	float random = 0;
	
	for (int n = Nmin; n <= Nmax; n += 32 * (int)k) {
		k *= 1.7;
		arr = new int[n];
		
		for (int r = 0; r < R; r++) {

			// Заполняем массив для прямого обхода и "прогреваем" кэш
			for (int i = 0; i < n - 1; i++) { arr[i] = i + 1; }
			arr[n - 1] = 0;
			for (int k = 0, i = 0; i < n * 1; i++) { k = arr[k]; }

			// Выполняем прямой обход массива k раз
			start = __rdtsc();
			for (int k = 0, i = 0; i < n * K; i++) { k = arr[k]; }
			end = __rdtsc();
			if (r == 0 || straight > (end - start) / n / K) straight = 1.0 * (end - start) / n / K;

			// Заполняем массив для обратного обхода и "прогреваем" кэш
			for (int i = 1; i < n; i++) { arr[i] = i - 1; }
			arr[0] = n - 1;
			for (int k = 0, i = 0; i < n * 1; i++) { k = arr[k]; }

			// Выполняем обратный обход массива k раз
			start = __rdtsc();
			for (int k = 0, i = 0; i < n * K; i++) { k = arr[k]; }
			end = __rdtsc();
			if (r == 0 || back >(end - start) / n / K) back = 1.0 * (end - start) / n / K;

			// Заполняем массив для случайного обхода и "прогреваем" кэш
			for (int i = 0; i < n; i++) {
				arr[i] = i;
			}
			for (int it = 0; it < n; it++) {
				int i = rand() % n;
				int j = rand() % n;
				int tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			for (int k = 0, i = 0; i < n * 1; i++) { k = arr[k]; }

			// Выполняем случайный обход массива k раз
			start = __rdtsc();
			for (int k = 0, i = 0; i < n * K; i++) { k = arr[k]; }
			end = __rdtsc();
			if (r == 0 || random < (end - start) / n / K) random = 1.0 * (end - start) / n / K;

		}

		std::cout << n << ", " << straight << ", " << back << ", "
			<< random << std::endl;

		delete[] arr;
	}
	std::cout << "end";
}