#include <iostream>
#include <thread>

void foo(const int init)
{
    std::cout << "Thread start " << std::endl;
    for (int i = init; i <= 100;)
    {
        std::cout << i << std::endl;
        i = i + 2;
    }
    std::cout << "Thread finish!" << std::endl;
    return;
}


int main()
{
    std::thread myTh1(foo, 0);
    std::thread myTh2(foo, 1);
    myTh1.join();
    myTh2.join();
}
