#include <iostream>
#include <mpi.h>
#include <cmath>

using namespace std;

int main(int argc, char** argv)
{
    srand(time(0));
    int rank, size;
    int i, j, n = 10000;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int n_partial = n / size;
    double* a_partial = new double[n_partial * n];//блоки строк исходной матрицы на каждом процессе
    double* x = new double[n]; //исходный вектор
    double* y_partial = new double[n_partial];//блоки результирующего вектора на каждом процессе
    double* y_total = new double[n];// вектор-результат
    double* a = new double[n * n];//исходная матрица
    if (rank == 0)
    {
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                a[i * n + j] = rand() % 10;
        for (i = 0; i < n; i++)
            x[i] = rand() % 10;
    }
    double t = MPI_Wtime();
    MPI_Bcast(x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(a, n_partial * n, MPI_DOUBLE, a_partial, n_partial * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    for (i = 0; i < n_partial; i++)
    {
        y_partial[i] = 0.0;
        for (j = 0; j < n; j++)
            y_partial[i] += a_partial[i * n + j] * x[j];
    }
    MPI_Gather(y_partial, n_partial, MPI_DOUBLE, y_total, n_partial, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    t = MPI_Wtime() - t;
    if (rank == 0)
    {
        cout << "time = " << t;
    }
    delete[] a_partial;
    delete[] a;
    delete[] x;
    delete[] y_partial;
    delete[] y_total;

    MPI_Finalize();
    return 0;
}