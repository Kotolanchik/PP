#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

int** a;
int* b;

int* f(int n)
{
    int* c;
    c = new int[n];
    for (int i = 0; i < n; i++) {
        c[i] = 0;
        for (int j = 0; j < n; j++) {
            c[i] += a[i][j] * b[j];
        }
    }
    return c;
}

void MultPar(int n, int i, int* c)
{
    for (int j = i; j < n; j += 10) {
        int s = 0;
        for (int k = 0; k < n; k++) {
            s += a[j][k] * b[k];
        }
        c[j] = s;
    }
}

int main()
{
    srand(time(0));
    int n;
    int* c;
    cout << "Input n: ";
    cin >> n;
    a = new int* [n];
    for (int i = 0; i < n; i++)
        a[i] = new int[n];
    b = new int[n];
    c = new int[n];
    for (int i = 0; i < n; i++)
    {
        b[i] = rand() % 10 + 1;
        c[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = rand() % 11 + 1;
        }
    }
    auto start = chrono::high_resolution_clock::now();
    c = f(n);
    auto end = chrono::high_resolution_clock::now();
    cout << "Time1: " << (chrono::duration<double>(end - start)).count() << endl;
    for (int i = 0; i < n; i++)
        c[i] = 0;
    auto start2 = chrono::high_resolution_clock::now();
    vector <thread> myTh(10);
    for (int i = 0; i < 10; i++) myTh[i] = thread(MultPar, n, i, c);
    for (int i = 0; i < 10; i++) myTh[i].join();
    auto end2 = chrono::high_resolution_clock::now();
    cout << "Time2: " << (chrono::duration<double>(end2 - start2)).count() << endl;
    return 0;
}
