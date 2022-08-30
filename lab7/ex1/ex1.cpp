#include <iostream>
#include <mpi.h>
#include <cmath>

using namespace std;

int main(int argc, char** argv)
{
	srand(time(0));
	const int N = 10000;
	int proc_rank, proc_num;
	double Localln = 0.0;
	double sum;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
	/*if (proc_rank == 0)
	{
		double sum = 0.0;
		int send_tag;
		double start, end, diff;
		start = MPI_Wtime();
		for (int j = 1; j < proc_num; j++)
		{
			for (int k = j; k < N; k += (proc_num - 1)) {
				if ((k + j - 1) < N)
				{
					((k + j) < N) ? send_tag = 1 : send_tag = 0;
					MPI_Send(&k, 1, MPI_DOUBLE, j, send_tag, MPI_COMM_WORLD);
					MPI_Recv(&Localln, 1, MPI_DOUBLE, j, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
					sum += Localln;
				}
			}
		}
		end = MPI_Wtime();
		diff = end - start;
		cout << "LN2 = " << sum << endl;
		cout << "time: " << diff << endl;
	}
	else
	{
		MPI_Status status;
		double Localln = 0;
		int k;
		MPI_Probe(0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		do {
			Localln = 0;
			MPI_Recv(&k, 1, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			Localln = pow(-1, k - 1) / k;
			MPI_Send(&Localln, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
		} while (status.MPI_TAG);
	}
	MPI_Finalize();
	return 0;*/
	////////2
	int k = 1;
	double start, end, diff;
	MPI_Bcast(&Localln, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	for (int k = (proc_rank + 1); k < N; k += proc_num)
		Localln += pow(-1, k - 1) / k;
	if (proc_rank == 0)
	{
		sum = Localln;
		start = MPI_Wtime();
		for (int j = 1; j < proc_num; j++)
		{
			MPI_Recv(&Localln, 1, MPI_DOUBLE, j, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			sum += Localln;
		}
	}
	else
		MPI_Send(&Localln, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	if (proc_rank == 0)
	{
		end = MPI_Wtime();
		diff = end - start;
		cout << "LN2 = " << sum << endl;
		cout << "time: " << diff << endl;
	}
	MPI_Finalize();
	return 0;
}