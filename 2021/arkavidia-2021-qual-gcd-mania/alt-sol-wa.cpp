#include<bits/stdc++.h>
using namespace std;

int N, Q;
long long a[100005], L, R;

long long GCD(long long a, long long b)
{
	if(a == 0) return b;
	
	return GCD(b % a, a);
}

int main()
{
	cin >> N;
	
	for(int i = 1; i <= N; i++)
	{
		cin >> a[i];
	}
	sort(a + 1, a + 1 + N);
	
	int minimum = a[1];
	for(int i = 1; i <= N; i++)
	{
		a[i] -= minimum;
	}
	
	long long gcd = 0;
	for(int i = 2; i <= N; i++)
	{
		gcd = GCD(gcd, a[i]);
	}
	
	long long res = 0;
	cin >> Q;
	while(Q--)
	{
		cin >> L >> R;
		res = GCD(gcd, minimum + L);
		res = max(res, GCD(gcd, minimum + R));
		res = max(res, GCD(gcd, minimum + R - 1));
		
		cout << res << endl;
		
		/* 
		for(int i = L; i <= R; i++)
		{
			if(i == L) res = GCD(gcd, minimum + i);
			else res = max(res, GCD(gcd, minimum + i));
			
		//	cout << i << " " << GCD(gcd, minimum + i) << endl;
		}
		cout << res << endl;
		*/
	}
	
	
}
