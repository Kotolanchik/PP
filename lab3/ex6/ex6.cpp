#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

long long s = 0;

void f(int k, long long n, int p, mutex& mx)
{
    long long s1 = 0;
    while (k <= n) {
        s1 += k;
        k += p;
    }
    lock_guard<mutex> lock(mx);
    s += s1;
}

int main()
{
    srand(time(0));
    long long n;
    int p;
    cout << "Input n: ";
    cin >> n;
    cout << "Input p(threads): ";
    cin >> p;
    vector <thread> myTh(p);
    mutex mx;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < p; i++) myTh[i] = thread(f, i + 1, n, p, ref(mx));
    for (int i = 0; i < p; i++) myTh[i].join();
    auto end = chrono::high_resolution_clock::now();
    cout << "Time1: " << (chrono::duration<double>(end - start)).count() << endl;
    cout << "\nsum: " << s;
    return 0;
}
