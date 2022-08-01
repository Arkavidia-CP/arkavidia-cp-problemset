#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    ll ar[n];
    for (int i = 0; i < n; i++) {
        cin >> ar[i];
    }
    sort(ar, ar + n);
    ll pc[n];
    pc[0] = ar[0];
    for (int i = 1; i < n; i++) {
        pc[i] = pc[i - 1]+ ar[i];
    }
    for (int i = 0; i < n; i++) {
        pc[i] = (((i + 1) * 1ll) * ar[i]) - pc[i];
    }

    int q;
    cin >> q;
    while (q--) {
        ll k;
        cin >> k;
        int l = 0, r = n - 1, m, best = -1;
        while (l <= r) {
            m = (l + r) / 2;
            if (k >= pc[m]) {
                best = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        ll ans = ar[best];
        ans += (k - pc[best]) / (best + 1);
        cout << ans << '\n';
    }
    return 0;
}