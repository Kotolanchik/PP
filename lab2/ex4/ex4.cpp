#include <iostream>
#include <conio.h>
#include <algorithm>
#include <iterator>
#include <functional>
#include <random>
#include <chrono>
#include <ctime>
#include <vector>
#include <execution>
using namespace std;

int main()
{
    int n;
    cout << "n=";
    cin >> n;
    //создание динамического двумерного массива
    vector<long long> a(n * n);
    vector<long long> b(n * n);
    vector<long long> c(n * n, 0);
    //заполнение
    for (int i = 0; i < n * n; i++) {
        a[i] = rand() % 10 + 1;
        b[i] = rand() % 10 + 1;
    }
    vector<int> range(n);
    iota(range.begin(), range.end(), 0);
    //измерение времени
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end; start = std::chrono::high_resolution_clock::now();
    //умножение
    for_each(execution::par_unseq, range.begin(), range.end(),
        [&a, &b, &c, &n](int i)
        {
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    c[i * n + j] += a[i * n + k] * b[k * n + j];
        });
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start; std::cout << "time to sum = " << diff.count() << "s\n";
    return 0;
}
