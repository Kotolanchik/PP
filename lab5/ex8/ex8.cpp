#include <iostream>
#include <algorithm>
#include <execution>
#include <omp.h>
#include <vector>

using namespace std;

int minInRow(vector<int> row)
{
	int min = INT32_MAX;
	for (auto x : row)
		if (min > x)
			min = x;
	return min;
}

int main()
{
	srand(time(0));
	long long n;
	cout << "Input n: ";
	cin >> n;
	n *= n;
	vector<long long> v(n);
	generate(execution::par_unseq, v.begin(), v.end(), [n]() {
		return rand() % 10000000 + 1000000; });
	long long max = 0;
	auto start = chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(2)
	for (long long i = 0; i < n; i++) {
		if (max < v[i])
			max = v[i];
	}
	auto end = chrono::high_resolution_clock::now();
	cout << "Time: " << (chrono::duration<double>(end - start)).count() << endl;
	return 0;
}
