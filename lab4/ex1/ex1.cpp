#include <iostream>
#include <chrono>
#include <semaphore>
#include <thread>
#include <queue>

using namespace std;

int n = 3;
counting_semaphore access{ 1 };
counting_semaphore queueFull{ n };
counting_semaphore queueEmpty{ 0 };
queue<int> q;

void Producer()
{
	int num = -1;
	while (true) {
		if (queueFull.try_acquire()) {// Доступ только при наличии пустых мест в хранилище
			num = rand() % 1000 + 1;
			printf("Application %d received\n", num);
			access.acquire();//Блокировка доступа к хранилищу
			q.push(num);
			printf("Application %d has been queued\n", num);
			access.release();// Снятие блокировки доступа к хранилищу
			queueEmpty.release();// Отметка наличия сообщений в хранилище
		}
		else
			printf("Application %d denied\n", num);
		this_thread::sleep_for(chrono::milliseconds(50));
	}
}

void Consumer()
{
	while (true) {
		queueEmpty.acquire(); // Доступ только при наличии сообщений в хранилищу
		access.acquire();// Блокировка доступа к хранилищу
		int num = q.front();
		q.pop();
		printf("Application %d has been accepted\n", num);
		access.release();; // Снятие блокировки доступа к хранилищу
		queueFull.release();// Отметка наличия пустых мест в хранилище
		this_thread::sleep_for(chrono::milliseconds(100));
		printf("Application %d processed\n", num);
	}
}

int main()
{
	srand(time(0));
	thread t1(Producer);
	thread t2(Consumer);
	t1.join();
	t2.join();
	return 0;
}
