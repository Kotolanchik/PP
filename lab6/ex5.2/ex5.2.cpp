#include <iostream>
#include <mpi.h>
#include <ctime>
using namespace std;
int main(int argc, char* argv[])
{
    srand(time(0));
    int N = 100, M = 1000000;
    int proc_rank, proc_num;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);

    if (proc_rank == 0)
    {
        long long int SumMatrix = 0, LocalSum;
        long long int** Matrix = new long long int* [N];
        for (int i = 0; i < N; i++) {
            Matrix[i] = new long long int[M];
            for (int j = 0; j < M; j++) {
                //Matrix[i][j] = rand() % 1000;
                Matrix[i][j] = 1;
            }
        }

        double start, end;
        int send_tag;
        start = MPI_Wtime();
        MPI_Request* requests = new MPI_Request[proc_num - 1];
        MPI_Status* statuses = new MPI_Status[proc_num - 1];
        for (int i = 0; i <= N / (proc_num - 1); i++) {
            for (int j = 1; j < proc_num; j++) {
                if (i * (proc_num - 1) + (j - 1) < N) {
                    ((i + 1) * (proc_num - 1) + (j - 1) < N) ? send_tag = 1 : send_tag = 0;//проверка, последняя ли для потока отправка 
                    MPI_Isend(Matrix[i * (proc_num - 1) + j - 1], M, MPI_LONG_LONG_INT,
                        j, send_tag, MPI_COMM_WORLD, &requests[j - 1]);
                }
            }
            for (int j = 1; j < proc_num; j++) {
                if (i * (proc_num - 1) + (j - 1) < N) {
                    MPI_Wait(&requests[j - 1], &statuses[j - 1]);
                    MPI_Irecv(&LocalSum, 1, MPI_LONG_LONG_INT,
                        j, MPI_ANY_TAG, MPI_COMM_WORLD, &requests[j - 1]);
                    MPI_Wait(&requests[j - 1], &statuses[j - 1]);
                    SumMatrix += LocalSum;
                }
            }
            MPI_Waitall(proc_num - 1, requests, statuses);
        }
        end = MPI_Wtime();
        cout << "Sum element of matrix: " << SumMatrix << endl;
        cout << "Time to work: " << end - start << endl;
    }
    else
    {
        MPI_Status status;
        MPI_Request request;
        long long int* Arr = new long long int[M], LocalSum = 0;
        MPI_Probe(0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        do {
            LocalSum = 0;
            MPI_Irecv(Arr, M, MPI_LONG_LONG_INT,
                0, MPI_ANY_TAG, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);
            for (int i = 0; i < M; i++) {
                LocalSum += Arr[i];
            }
            MPI_Isend(&LocalSum, 1, MPI_LONG_LONG_INT,
                0, 0, MPI_COMM_WORLD, &request);
        } while (status.MPI_TAG);
    }
    MPI_Finalize();
}
