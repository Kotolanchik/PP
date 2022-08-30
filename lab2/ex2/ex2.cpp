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
    long long int n;
    cout << "Input n:";
    cin >> n;
    vector<int> v(n);
    srand(time(NULL));
    generate(execution::par_unseq, v.begin(), v.end(), []() { return rand() % 1000000 + 100000; });
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end; start = std::chrono::high_resolution_clock::now();
    long long s = reduce(execution::par_unseq, v.begin(), v.end());
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start; std::cout << "time to sum = " << diff.count() << "s\n";
    cout << "\n" << s;
    return 0;
}
