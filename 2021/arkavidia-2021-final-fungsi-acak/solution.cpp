#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

const int MOD = 1e9 + 7;

int fpow(int a, int b, int m) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1LL * ret * a % m;
        a = 1LL * a * a % m;
        b >>= 1;
    }
    return ret;
}

struct Segtree {
    vector<int> t;
    vector<pair<int, int>> lz;
    
    Segtree(int n) {
        t.resize(4 * n + 5);
        lz.assign(4 * n + 5, make_pair(1, 0));
    }

    void update (int v, int s, int e, int l, int r, int a, int b) {
        // change x to ax+b for every x with index in range [l,r]
        if (l > e || r < s || l > r) return;
        if (s == l && e == r) {
            t[v] = (1LL * a * t[v] + 1LL * b * (e - s + 1)) % MOD;
            lz[v] = make_pair((1LL * lz[v].first * a) % MOD, (1LL * lz[v].second * a + b) % MOD);
            return;
        }
        push (v, s, e);
        int mid = (s + e) >> 1;
        update (v << 1, s, mid, l, min(mid, r), a, b);
        update (v << 1 | 1, mid + 1, e, max(l, mid + 1), r, a, b);
        t[v] = (t[v << 1] + t[v << 1 | 1]) % MOD;
    }

    int get (int v, int s, int e, int l, int r) {
        if (l > e || r < s || l > r) return 0;
        if (s == l && e == r) {
            return t[v];
        }
        push (v, s, e);
        int mid = (s + e) >> 1;
        return (get (v << 1, s, mid, l, min(mid, r)) + get (v << 1 | 1, mid + 1, e, max(l, mid + 1), r)) % MOD;
    }

    void push (int v, int s, int e) {
        if (lz[v] == make_pair(1, 0)) return;
        int a = lz[v].first;
        int b = lz[v].second;
        lz[v << 1] = make_pair((1LL * lz[v << 1].first * a) % MOD, (1LL * lz[v << 1].second * a + b) % MOD);
        lz[v << 1 | 1] = make_pair((1LL * lz[v << 1 | 1].first * a) % MOD, (1LL * lz[v << 1 | 1].second * a + b) % MOD);
        int mid = (s + e) >> 1;
        t[v << 1] = (1LL * a * t[v << 1] + 1LL * b * (mid - s + 1)) % MOD;
        t[v << 1 | 1] = (1LL * a * t[v << 1 | 1] + 1LL * b * (e - mid)) % MOD;
        lz[v] = make_pair(1, 0);
    }

};

const int M = 1e5;
int n;
vector<pair<int, int>> intervals;

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        intervals.emplace_back(l, r);
    }
    Segtree st(M);
    sort (intervals.begin(), intervals.end());
    st.update(1, 1, M, intervals[0].first, intervals[0].second, 1, 1);

    int kanan = intervals[0].second;
    int prod = (intervals[0].second - intervals[0].first + 1);
    for (int i = 1; i < n; i++) {
        if (intervals[i].first > kanan) {
            st.update(1, 1, M, intervals[i].first, intervals[i].second, 1, prod);
            st.update(1, 1, M, 1, kanan, intervals[i].second - intervals[i].first + 1, 0);
        } else {
            st.update(1, 1, M, kanan + 1, intervals[i].second, 1, prod);
            st.update(1, 1, M, intervals[i].first, min(kanan, intervals[i].second), intervals[i].second - intervals[i].first, prod);
            st.update(1, 1, M, 1, intervals[i].first - 1, intervals[i].second - intervals[i].first + 1, 0);
            st.update(1, 1, M, intervals[i].second + 1, kanan, intervals[i].second - intervals[i].first + 1, 0);
        }
        prod = (1LL * prod * (intervals[i].second - intervals[i].first + 1)) % MOD;
        kanan = max (kanan, intervals[i].second);
    }

    int ans = st.get(1, 1, M, 1, M) % MOD;
    ans = (1LL * ans * fpow (prod, MOD - 2, MOD)) % MOD;
    if (ans < 0) ans += MOD;
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int TC = 1;
    for(int i = 1; i <= TC; i++) {
        solve();
    }
  
    return 0;
}