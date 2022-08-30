// pp7.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <mpi.h>
#include <cmath>

using namespace std;

int main(int argc, char** argv)
{
	srand(time(0));
	const int N = 100;
	int proc_rank, proc_num;
	int b = 0;
	int bf = 0;
	MPI_Status status;
	int* Arr = new int[N];
	for (int i = 0; i < N; i++)
		Arr[i] = rand() % 10;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
	double start, end, diff;
	MPI_Bcast(&b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	for (int k = (proc_rank + 1); k < N; k += proc_num)
		if (Arr[k] > Arr[k + 1])
			b++;
	if (proc_rank == 0)
	{
		bf = b;
		start = MPI_Wtime();
		for (int j = 1; j < proc_num; j++)
		{
			MPI_Recv(&b, 1, MPI_DOUBLE, j, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			bf += b;
		}
	}
	else
		MPI_Send(&b, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	if (proc_rank == 0)
	{
		end = MPI_Wtime();
		diff = end - start;
		cout << "time: " << diff << endl;
	}
	MPI_Finalize();
	return 0;
}