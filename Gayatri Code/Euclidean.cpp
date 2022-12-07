#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

// function to find gcd of two integer numbers
ll gcd(ll a, ll b)
{
	if (!a)
		return b;
	return gcd(b % a, a);
}

ll reduceB(ll a, char b[])
{
	// Initialize result
	ll mod = 0;

	// calculating mod of b with a to make
	// b like 0 <= b < a
	for (int i = 0; i < strlen(b); i++)
		mod = (mod * 10 + b[i] - '0') % a;

	return mod; // return modulo
}

ll gcdLarge(ll a, char b[])
{
	// Reduce 'b' (second number) after modulo with a
	ll num = reduceB(a, b);

	// gcd of two numbers
	return gcd(a, num);
}

int main()
{
	// first number which is integer
	ll a = 1221;

	char b[] = "1234567891011121314151617181920212223242526272829";
	
	cout<<"Smaller Number: ";
	cin>>a;
	
	cout<<"Large Number: ";
	cin>>b;
	
	cout<<"\nGCD is: ";
	
	if (a == 0)
		cout << b << endl;
	else
		cout << gcdLarge(a, b) << endl;

	return 0;
}
