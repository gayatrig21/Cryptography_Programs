// C++ implementation of the approach
#include <bits/stdc++.h>
using namespace std;


vector<int> createSemiPrimeSieve(int n)
{
	int v[n + 1];


	for (int i = 1; i <= n; i++)
		v[i] = i;

	int countDivision[n + 1];

	for (int i = 0; i < n + 1; i++)
		countDivision[i] = 2;

	for (int i = 2; i <= n; i++) {

		
		if (v[i] == i && countDivision[i] == 2) {

			// j goes for each factor of i
			for (int j = 2 * i; j <= n; j += i) {
				if (countDivision[j] > 0) {

					v[j] = v[j] / i;

				
					countDivision[j]--;
				}
			}
		}
	}

	// A new vector to store all Semi Primes
	vector<int> res;

	for (int i = 2; i <= n; i++) {

	
		if (v[i] == 1 && countDivision[i] == 0)
			res.push_back(i);
	}

	return res;
}

// Driver code
int main()
{
	int n = 37975227936943673922808872755445627854565536638199;
	vector<int> semiPrime = createSemiPrimeSieve(n);

	// Print all semi-primes
	for (int i = 0; i < semiPrime.size(); i++)
		cout << semiPrime[i] << " ";

	return 0;
}

