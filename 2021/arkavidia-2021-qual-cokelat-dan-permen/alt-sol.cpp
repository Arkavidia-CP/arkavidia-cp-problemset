#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
using ll = long long;
using pll = pair<ll, ll>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    pll ab[n];
    for (int i = 0; i < n; i++) {
        cin >> ab[i].fi;
    }
    for (int i = 0; i < n; i++ ) {
        cin >> ab[i].se;
    }

    ll mx = 0;
    for (int i = 0; i < n; i++) {
        mx = max(mx, ab[i].fi + ab[i].se);
    }
    sort(ab, ab + n, [mx](pll a, pll b) {
        if (mx - a.se == mx - b.se) {
            return a.fi < b.fi;
        }
        return mx - a.se < mx - b.se;
    });
    
    ll l = mx, r = 2e18, m, best;
    while (l <= r) {
        m = (l + r) / 2;
        ll last = 0;
        bool can = true;
        for (int i = 0; i < n; i++) {
            if (m - ab[i].se <= last) {
                can = false;
                break;
            }
            last = max(last + 1, ab[i].fi);
        }
        if (can) {
            best = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += best - ab[i].fi - ab[i].se;
    }
    cout << ans << '\n';
    return 0;
}