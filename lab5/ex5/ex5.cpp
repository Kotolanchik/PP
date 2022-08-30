#include <iostream>
#include <algorithm>
#include <execution>
#include <omp.h>
#include <cmath>
#include <vector>

using namespace std;

int main()
{
	int m = 4, n, k = omp_get_max_threads() - m;
	cout << "Input n: ";
	cin >> n;
	vector<int> v(n);
	generate(execution::par_unseq, v.begin(), v.end(), []() {
		return rand() % 1000 + 1; });
	omp_set_nested(1);
	int sum = 0, length = 0;
#pragma omp parallel num_threads(2)
	{
#pragma omp sections
		{
#pragma omp section
			{
#pragma omp parallel for schedule(dynamic) num_threads(m)
				for (int i = 1; i <= n; i++)
					sum += i;
			}
#pragma omp section
			{
#pragma omp parallel for schedule(dynamic) num_threads(k)
				for (int i = 0; i < n; i++)
					length += v[i] * v[i];
				length = sqrt(length);
			}
		}
	}
	cout << "sum = " << sum << ", length = " << length << endl;
	return 0;
}
