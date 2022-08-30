#include <iostream>
#include <omp.h>

int main() {
	int nthreads, tid;
	// Создание параллельной области
#pragma omp parallel private(tid)
	{
		// печать номера потока
		tid = omp_get_thread_num();
		printf("Hello World from thread = %d\n", tid);
		// Печать количества потоков – только master
		if (tid == 0) {
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}
	} // Завершение параллельной области
}
