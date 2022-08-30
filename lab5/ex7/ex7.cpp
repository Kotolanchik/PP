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
	vector<long long> m1(n * n);
	vector<long long> m2(n * n);
	vector<long long> res(n * n);
	generate(execution::par_unseq, m1.begin(), m1.end(), []() { return rand() % 100 + 1; });
	generate(execution::par_unseq, m2.begin(), m2.end(), []() { return rand() % 100 + 1; });
	auto start = chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(8)
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				res[i * n + j] += m1[i * n + k] * m2[k * n + j];
	auto end = chrono::high_resolution_clock::now();
	cout << "Time: " << (chrono::duration<double>(end - start)).count() << endl;
	return 0;
}
