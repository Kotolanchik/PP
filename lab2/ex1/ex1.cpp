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

int f(int x)
{
    int k = 0;
    int d = 2;
    while (d <= x / d)
    {
        if (x % d == 0) k++;
        d++;
    }
    return 2 * k;
}

int main()
{
    long long int n;
    cout << "Input n:";
    cin >> n;
    vector<long long int> v;
    vector<long long int> res;
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        v.push_back(rand() % 1000000 + 100000);
        res.push_back(0);
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end; start = std::chrono::high_resolution_clock::now();
    transform(std::execution::par, v.begin(), v.end(), res.begin(), f);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start; std::cout << "time to sum = " << diff.count() << "s\n";
    return 0;
}
