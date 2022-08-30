#include <iostream>
#include <math.h>
#include <mpi.h>
using namespace std;
int main(int argc, char* argv[])
{
    int proc_rank, proc_num;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
    if (proc_rank == 0)
    {
        cout << proc_num << " processes.\n";
    }
    else if (proc_rank % 2 == 0)
    {
        cout << proc_rank << ": FIRST!\n";
    }
    else
    {
        cout << proc_rank << ": SECOND!\n";
    }

    MPI_Finalize();
}
