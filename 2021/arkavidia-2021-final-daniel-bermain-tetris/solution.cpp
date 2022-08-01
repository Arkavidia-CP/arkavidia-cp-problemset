#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll n;
    int q;
    cin >> n;
    cin >> q;
    while (q--) {
        ll k;
        cin >> k;
        ll ans = (3 * k) / n;
        cout << ans << '\n';
    }
    return 0;
}