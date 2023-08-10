#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long
#define ll long long
#define fi first
#define se second
#define pb(a) push_back(a)
#define mp(a, b) make_pair(a, b)
#define el '\n'

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll n, ans = 0; cin >> n;

    vector<ll> m(n), c(n);
    for(ll i=0;i<n;i++) cin >> m[i] >> c[i];
    sort(m.begin(), m.end());

    ans = n * (n-1) / 2;

    ll cnt = 0, cur = -1e9;
    for(ll i=0; i<n; i++) {
        if (m[i] != cur) {
            ans -= cnt * (cnt-1) / 2;
            cnt = 1;
            cur = m[i];
        } else {
            cnt++;
        }
    }

    ans -= cnt * (cnt-1) / 2;

    cout << ans << el;
}