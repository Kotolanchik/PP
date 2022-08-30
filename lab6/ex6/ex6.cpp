#include <iostream>
#include <mpi.h>
#include <ctime>
using namespace std;
int main(int argc, char* argv[])
{
    srand(time(0));
    int N = 1000000, M = 100;
    int proc_rank, proc_num;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);

    int* Arr = new int[proc_num];
    for (int i = 0; i < proc_num; i++) {
        Arr[i] = proc_rank * proc_num + i + 1;
    }

    for (int i = 0; i < proc_num; i++) {
        if (i < proc_rank)
        {
            int a = Arr[i];
            MPI_Recv(&Arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            MPI_Send(&a, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        else if (i > proc_rank)
        {
            MPI_Send(&Arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Recv(&Arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
        }
    }
    int a = 0;
    if (proc_rank == 0) {

        for (int i = 0; i < proc_num; i++) {
            cout << Arr[i] << ' ';
        }
        cout << endl;
        MPI_Send(&a, 1, MPI_INT, proc_rank + 1, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&a, 1, MPI_INT, proc_rank - 1, 0, MPI_COMM_WORLD, &status);
        for (int i = 0; i < proc_num; i++) {
            cout << Arr[i] << ' ';
        }
        cout << endl;
        if (proc_rank + 1 != proc_num) {
            MPI_Send(&a, 1, MPI_INT, proc_rank + 1, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
}
