#include <bits/stdc++.h>
using namespace std;
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) "[" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

const int NMAX = 1e5 + 5;
const int BLOCK = 350;
const int NUM_BLOCK = NMAX / BLOCK + 5;

int n, tc;
int num_block;
int a[NMAX], val[NUM_BLOCK][BLOCK + 5];

struct BIT {
    vector<long long> bit;
    BIT() {
        bit.assign(NMAX, 0LL);
    }

    void add(int x, int val) {
        for ( ; x < NMAX; x += x & -x)
            bit[x] += val;
    }

    long long get(int x) {
        long long ret = 0;
        for ( ; x > 0; x -= x & -x) {
            ret += bit[x];
        }
        return ret;
    }
} sum[NUM_BLOCK];

void build() {
    for (int i = 1; i <= n; i += BLOCK) {
        ++num_block;
        for (int j = i, k = 1; j <= min(n, i + BLOCK - 1); j++, k++) {
            val[num_block][k] = a[j];
            sum[num_block].add(a[j], a[j]);
        }
    }
}

void replace(int x, int v) {
    int block = (x + BLOCK - 1) / BLOCK;
    int pos = x - (block - 1) * BLOCK;
    sum[block].add(a[x], -a[x]);
    a[x] = v;
    sum[block].add(a[x], a[x]);
    val[block][pos] = a[x];
}

long long query(int x, int p, int q) {
    long long ret = 0;
    int block = (x + BLOCK - 1) / BLOCK;
    for (int i = 1; i < block; i++) {
        ret += sum[i].get(q) - sum[i].get(p - 1);
    }
    int pos = x - (block - 1) * BLOCK;
    for (int i = 1; i <= pos; i++) {
        int cur = val[block][i];
        if (cur < p || cur > q) continue;
        ret += cur;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build();
    cin >> tc;
    while (tc--) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int l, r, p, q;
            cin >> l >> r >> p >> q;
            long long ans = query(r, p, q);
            if (l > 1) ans -= query(l - 1, p, q);
            cout << ans << '\n';
        } else if (tp == 2) {
            int x, v;
            cin >> x >> v;
            replace(x, v);
        }
    }
    
    return 0;
}