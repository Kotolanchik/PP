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
    long long** a = new long long* [n];
    long long** b = new long long* [n];
    long long** c = new long long* [n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new long long[n];
        b[i] = new long long[n];
        c[i] = new long long[n];
    }
    //заполнение
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = rand() % 10 + 1;
            b[i][j] = rand() % 10 + 1;
            c[i][j] = 0;
        }

    }
    cout << "\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << b[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    //измерение времени
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end; start = std::chrono::high_resolution_clock::now();
    //умножение
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int r = 0; r < n; r++)
            {
                c[i][j] += a[i][r] * b[r][j];
            }
        }
    }
    end = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << c[i][j] << " ";
        }
        cout << "\n";
    }
    std::chrono::duration<double> diff = end - start; std::cout << "time to sum = " << diff.count() << "s\n";
    //очищение памяти
    for (int i = 0; i < n; i++)
    {
        delete[] a[i];
        delete[] b[i];
        delete[] c[i];
    }
    delete[] a;
    delete[] b;
    delete[] c;
    return 0;
}
