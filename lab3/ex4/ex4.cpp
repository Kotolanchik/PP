#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

int Simp(int n)
{
    int i = 2;
    while (i * i <= n)
    {
        if (n % i == 0) n /= i;
        else i++;
    }
    return n;
}

void foo(int* v, int i, int n, int p)
{
    for (int j = i; j < n; j += p) v[j] = Simp(v[j]);
}


int main()
{
    srand(time(0));
    int n, p;
    cout << "Input n: ";
    cin >> n;
    cout << "Input p(threads): ";
    cin >> p;
    int* v;
    v = new int[n];
    for (int i = 0; i < n; i++) v[i] = rand() % 900001 + 100000;
    vector <thread> myTh(p);
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < p; ++i) myTh[i] = thread(foo, v, i, n, p);
    for (int i = 0; i < p; ++i) myTh[i].join();
    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << (chrono::duration<double>(end - start)).count() << endl;
    return 0;
}
