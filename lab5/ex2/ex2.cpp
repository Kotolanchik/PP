#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
	int n;
	cout << "Input n: ";
	cin >> n;
	omp_set_num_threads(2);
#pragma omp parallel firstprivate(n)
	{
		if (omp_get_thread_num() == 0)
			for (int i = 1; i <= n; i++) printf("i = %d\n", i);
		else
			for (int i = 1; i <= n; i++) printf("HELLO\n");
	}
	return 0;
}
