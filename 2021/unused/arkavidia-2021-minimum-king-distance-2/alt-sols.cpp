/* Author-Solutions: Marcello Faria
 * Solution arkavidia-2021-minimum-king-distance-2
 */
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll arr1[100001];
ll arr2[100001];
const ll INF = 1e15 + 7;
int main()
{
	ll M, N;
	cin >> M >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> arr1[i];
	}
	for (int i = 0; i < N; i++)
	{
		cin >> arr2[i];
	}
	sort(arr1, arr1 + N);
	sort(arr2, arr2 + N);
	ll idx1 = 0;
	ll idx2 = 0;
	ll minim1 = INF;
	ll minim2 = INF;
	for (int i = 0; i < N - 1; i++)
	{
		int a, b;
		a = abs(arr1[i + 1] - arr1[i]);
		if (minim1 > a)
		{
			minim1 = a;
			idx1 = i;
		}
		b = abs(arr2[i + 1] - arr2[i]);
		if (minim2 > b)
		{
			minim2 = b;
			idx2 = i;
		}
	}
	cout << max(abs(arr2[idx2 + 1] - arr2[idx2]), abs(arr1[idx1 + 1] - arr1[idx1])) << endl;
}
