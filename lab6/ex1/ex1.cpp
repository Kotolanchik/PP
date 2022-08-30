#include <iostream>
#include <math.h>
#include <mpi.h>
using namespace std;
int main(int argc, char* argv[]) {
    int proc_rank, proc_num;


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_num);

    cout << "I am " << proc_rank
        << " process from " << proc_num << " processes!\n";

    MPI_Finalize();
}
