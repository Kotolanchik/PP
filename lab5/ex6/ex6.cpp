#include <iostream>
#include <algorithm>
#include <execution>
#include <omp.h>
#include <vector>

using namespace std;

int maxPrimeDivider(int n)
{
	int div = 2;
	while (div * div <= n) {
		if (n % div == 0)
			n /= div;
		else div++;
	}
	if (n != 1)
		div = n;
	return div;
}

int main()
{
	int n;
	cout << "Input n: ";
	cin >> n;
	vector<long long> arr(n);
	generate(execution::par_unseq, arr.begin(), arr.end(), []() {
		return rand() % 1000000 + 100001; });
	auto start = chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(1)
	for (int i = 0; i < n; i++)
		arr[i] = maxPrimeDivider(arr[i]);
	auto end = chrono::high_resolution_clock::now();
	cout << "Time: " << (chrono::duration<double>(end - start)).count() << endl;
	return 0;
}
