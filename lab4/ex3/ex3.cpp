#include <iostream>
#include <chrono>
#include <semaphore>
#include <thread>
#include <vector>

using namespace std;
int n = 2, m = 2;
binary_semaphore read{ 1 };
binary_semaphore access{ 1 };
int readCount = 0;
int shared = 0;

void writer(int threadNum)
{
	while (true) {
		access.acquire();// Блокировка доступа к хранилищу
		shared = rand() % 1000 + 1;
		printf("Thread W%d: %d\n", threadNum, shared);
		access.release();// Снятие блокировки доступа к хранилищу
		this_thread::sleep_for(chrono::milliseconds(rand() % 100 + 1));
	}
}

void reader(int threadNum)
{
	while (true) {
		read.acquire();// Блокировка доступа к переменной ReadCount 
		readCount++;// Изменение счетчика активных потоков-читателей
		if (readCount == 1)
			access.acquire(); // Блокировка доступа к хранилищу (если поток-читатель первый) 
		read.release();// Снятие блокировки доступа к переменной ReadCount 
		printf("Thread R%d: %d\n", threadNum, shared);
		read.acquire();// Блокировка доступа к переменной ReadCount
		readCount--;// Изменение счетчика активных потоков-читателей
		if (readCount == 0) // Снятие блокировка доступа к хранилищу
			access.release();// (если завершается последний поток-читатель) 
		read.release();// Снятие блокировки доступа к переменной ReadCount 
		this_thread::sleep_for(chrono::milliseconds(rand() % 100 + 1));
	}
}

int main()
{
	srand(time(0));
	vector<thread> writers(n);
	vector<thread> readers(m);
	for (int i = 0; i < n; i++, this_thread::sleep_for(chrono::milliseconds(100)))
		writers[i] = thread(writer, i);
	for (int i = 0; i < m; i++)
		readers[i] = thread(reader, i);
	for (thread& w : writers)
		w.join();
	for (thread& r : readers)
		r.join();
	return 0;
}
