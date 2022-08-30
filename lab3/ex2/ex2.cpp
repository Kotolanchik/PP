#include <iostream>
#include <thread>

using namespace std;

void foo(void)
{
    cout << "Thread start..." << endl;
    for (int i = 0; i < 100; ++i)
    {
        cout << "Thread id = " << this_thread::get_id() << endl;
        this_thread::sleep_for(chrono::milliseconds(rand() % 1001 + 1000));
    }
    cout << "Thread finish!" << std::endl;
    return;
}


int main()
{
    int p;
    cout << "Input p: ";
    cin >> p;
    for (int i = 0; i < p; ++i)
    {
        thread myTh1(foo);
        myTh1.join();
    }
}
