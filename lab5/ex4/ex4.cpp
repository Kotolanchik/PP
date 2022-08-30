#include <iostream>
#include <algorithm>
#include <execution>
#include <omp.h>
#include <vector>

using namespace std;

int main()
{
	srand(time(0));
	int n;
	cout << "Input n: ";
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++)
		v[i] = rand() % 1000 + 1;
	int max = 0;
	//#pragma omp parallel reduction(max: max)
	//{
	// #pragma omp parallel for schedule(dynamic)
	// for (int i = 0; i < n; i++)
	// max += (max < arr[i] ? -max + arr[i] : 0);
	//}
	//#pragma omp parallel for schedule(dynamic)
	//for (int i = 0; i < n; i++)
	//#pragma omp critical
	// if (max < arr[i])
	// max = arr[i];
#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < n; i++)
#pragma omp atomic
		max += (max < v[i] ? -max + v[i] : 0);
	cout << max << endl;
	return 0;
}
