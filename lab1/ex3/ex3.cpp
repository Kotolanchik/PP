#include <iostream>
#include <random>
#include <chrono>
using namespace std;

int main()
{
    int n;
    cout << "n=";
    cin >> n;
    //создание динамического двумерного массива
    long long* a = new long long[n * n];
    long long* b = new long long[n * n];
    long long* c = new long long[n * n];
    //заполнение
    for (int i = 0; i < n * n; i++)
    {
        a[i] = rand() % 10 + 1;
        b[i] = rand() % 10 + 1;
        c[i] = 0;

    }
    //измерение времени
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end; start = std::chrono::high_resolution_clock::now();
    //умножение
    for (int k = 0; k < n; k++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int i = 0; i < n; i++)
            {
                c[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start; std::cout << "time to sum = " << diff.count() << "s\n";
    //очищение памяти
    delete[] a;
    delete[] b;
    delete[] c;
    return 0;
}
