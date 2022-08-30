#include <iostream>
#include <mpi.h>
#include <ctime>

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(0));
    int message1, message2;
    int rank, size, dest, source, send_tag, recv_tag;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        send_tag = 0;
        dest = 1;
        MPI_Comm_size(MPI_COMM_WORLD, &recv_tag);
        recv_tag--;
        message1 = rand() % 100000;
        MPI_Send(&message1, 1, MPI_INT, dest, send_tag, MPI_COMM_WORLD);
        MPI_Recv(&message2, 1, MPI_INT, MPI_ANY_SOURCE, recv_tag, MPI_COMM_WORLD, &status);
        if (message2 - message1 == recv_tag)
        {
            cout << "Correct!\n";
        }
        else
        {
            cout << "Error!\n";
            cout << "first: " << message1 << endl;
            cout << "second: " << message2 << endl;
        }
    }
    else
    {
        MPI_Recv(&message1, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        cout << rank << " receive number " << message1 << endl;
        message2 = message1 + 1;
        send_tag = status.MPI_TAG + 1;
        dest = (rank + 1) % size;
        MPI_Send(&message2, 1, MPI_INT, dest, send_tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
