#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;
int cnt = 0;

void foo(int i, mutex& mx)
{
    while (cnt <= 100)
    {
        this_thread::sleep_for(chrono::milliseconds(rand() % 10));
        std::lock_guard<std::mutex> lgmx(mx);
        cnt += i;
        cout << cnt << endl;
    }
}


int main()
{
    int p;
    cout << "Input p: ";
    cin >> p;
    vector <thread> myTh(p);
    mutex mx;
    for (int i = 0; i < p; ++i)
    {
        myTh[i] = thread(foo, i, ref(mx));
    }
    std::unique_lock<std::mutex> ulmx(mx);
    ulmx.unlock();
    for (int i = 0; i < p; ++i)
    {
        myTh[i].join();
    }
}
