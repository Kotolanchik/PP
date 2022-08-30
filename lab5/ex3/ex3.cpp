#include <iostream>
#include <algorithm>
#include <execution>
#include <omp.h>
#include <vector>

using namespace std;

int main()
{
	srand(time(NULL));
	int n;
	printf("Input N:");
	scanf_s("%d", &n);
	vector<int> v1(n), v2(n), res(n);
	for (int i = 0; i < n; i++)
	{
		v1[i] = rand() % 1000 + 1;
		v2[i] = rand() % 1000 + 1;
	}
#pragma omp for schedule(static)
	for (int i = 0; i < n; i++)
		res[i] = v1[i] * v2[i];
	for (int i = 0; i < n; i++) {
		printf("%d. %d\n", i, res[i]);

	}
	return 0;
}
