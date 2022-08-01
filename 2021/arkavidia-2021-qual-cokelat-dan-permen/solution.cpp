#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n;
ll upper_b = 4e18 + 7;
ll max_pair = 0;
ll res, ans;

ll binser(ll l, ll r, pair<ll, ll> arr[], ll x)
{
	ll f;
	bool isValid;
	if (r >= l)
	{
		ll m = l + (r - l) / 2;
		f = 0;
		isValid = true;
		for (int i = 0; i < n; i++)
		{
			if (f >= m - arr[i].second)
			{
				isValid = false;
				break;
			}
			f = max(arr[i].first, f + 1);
		}
		if (isValid == true)
		{
			x = m;
			return binser(l, m - 1, arr, x);
		}
		else
		{
			return binser(m + 1, r, arr, x);
		}
	}
	return x;
}

int main()
{
	cin >> n;
	pair<ll, ll> arr[n];
	ll tot[n], x;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i].first;
	}
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i].second;
		tot[i] = arr[i].first + arr[i].second;
		max_pair = max(tot[i], max_pair);
	}
	sort(arr, arr + n, [](const pair<ll, ll> &p1, const pair<ll, ll> &p2) {
		if (p1.second == p2.second)
		{
			return p1.first < p2.first;
		}
		return -1 * p1.second < -1 * p2.second;
	});
	res = binser(max_pair, upper_b, arr, x);
	ans = 0;
	for (int i = 0; i < n; i++)
	{
		ans += (res - tot[i]);
	}
	cout << ans << endl;
}