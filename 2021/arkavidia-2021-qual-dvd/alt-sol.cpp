#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

const ll INF = 1e18;

ll n, m;
ll x, y;
ll n1, m1;
ll ninv, minv;
ll fpb;
pll p[2];

inline void mod (ll& a, ll m) {
    a %= m;
    if (a < 0) a += m;
}

ll euclid (ll a, ll b, ll& x, ll& y) {
    if (b) {
        ll d = euclid (b, a % b, y, x);
        return y -= a/b * x, d;
    }
    return x = 1, y = 0, a;
}

ll inv (ll a, ll b) {
    // a and b are coprime
    ll x, y;
    ll fpb = euclid (a, b, x, y);
    assert (fpb == 1);
    x %= b;
    if (x < 0) x += b;
    return x;
}

bool cocok (ll k, ll u, ll v) {
    bool ok = true;
    if ((k / n) % 2 == 0) {
        ok &= (u == k % n);
    } else {
        ok &= (u == (n - (k % n)));
    }
    if ((k / m) % 2 == 0) {
        ok &= (v == k % m);
    } else {
        ok &= (v == (m - (k % m)));
    }
    return ok;
}

void solve() {
    cin >> n >> m >> x >> y;
    ll fpb = __gcd(n, m);
    n1 = n / fpb;
    m1 = m / fpb;
    ninv = inv (n1, m1);
    minv = inv (m1, n1);
    if ((x + y) % 2 == 0) {
        p[0] = make_pair(x - 1, y - 1);
        p[1] = make_pair(x, y);
    } else {
        p[0] = make_pair(x, y - 1);
        p[1] = make_pair(x - 1, y);
    }

    ll pos = INF;
    for (int i = 0; i < 2; i++) {
        ll u = p[i].first, v = p[i].second;
        ll uu = p[1-i].first, vv = p[1-i].second;
        ll a, b, r, k;
        {
            r = (v - u) / 2;
            if (r % fpb == 0) {
                r /= fpb;
                ll rr = r;
                mod (rr, m1);
                a = (rr * ninv) % m1;
                b = (a * n1 - r) / m1;
                k = a*2*n + u;
                if (a*2 < m1 && b*2 < n1 && cocok (k+1, uu, vv)) {
                    pos = min (pos, k);
                }
            }
        }
        {
            r = (v + u - 2*n) / 2;
            if (r % fpb == 0) {
                r /= fpb;
                ll rr = r;
                mod (rr, m1);
                a = (rr * ninv) % m1;
                b = (a * n1 - r) / m1;
                k = (a*2 + 1)*n + (n - u);
                if (a*2 + 1 < m1 && b*2 < n1 && cocok (k+1, uu, vv)) {
                    pos = min (pos, k);
                }
            }
        }
        {   
            r = (2*m - v - u) / 2;
            if (r % fpb == 0) {
                r /= fpb;
                ll rr = r;
                mod (rr, m1);
                a = (rr * ninv) % m1;
                b = (a * n1 - r) / m1;
                k = a*2*n + u;
                if (a*2 < m1 && b*2 + 1 < n1 && cocok (k+1, uu, vv)) {
                    pos = min (pos, k);
                }
            }
        }
        {
            r = (2*m - v + u - 2*n) / 2;
            if (r % fpb == 0) {
                r /= fpb;
                ll rr = r;
                mod (rr, m1);
                a = (rr * ninv) % m1;
                b = (a * n1 - r) / m1;
                k = (a*2 + 1)*n + (n - u);
                if (a*2 + 1 < m1 && b*2 + 1 < n1 && cocok (k+1, uu, vv)) {
                    pos = min (pos, k);
                }
            }
        }
    }
    if (pos == INF) {
        cout << 0;
    } else {
        ll ans = 1 + (pos / m) + (pos / n);
        ans = (ans % 9 == 0 ? 9 : ans % 9);
        cout << ans;
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int TC = 1;
    cin >> TC;
    for(int i = 1; i <= TC; i++) {
        solve();
    }
  
    return 0;
}