#include <bits/stdc++.h>
using namespace std;

#define rep(i, n, N) for (int i = (n); i <= (N); i++)
#define For(i, n, N) for (int i = (n); i < (N); i++)
#define rap(i, n, N) for (int i = (n); i >= (N); i--)
#define rip(i, n, N, V) for (int i = (n); i <= (N); i += V)

using vi = vector<int>;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using lll = __int128;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pld = pair<ld, ld>;
using plll = pair<lll, lll>;

#define fi first
#define se second
#define ff fi.fi
#define fs fi.se
#define sf se.fi
#define ss se.se
#define mp make_pair
#define pb push_back
#define pob pop_back
#define pf push_front
#define pof pop_front

#define endl '\n'
#define clz(x) (1 << (31 - __builtin_clz(x)))
#define all(x) x.begin(), x.end()
#define ari(x) array<int, x>
#define arll(x) array<ll, x>
#define debug(x) cout << #x << " = " << (x) << endl
#define debugV(v, x) cout << #v << "[" << (x) << "] = " << v[x] << endl
#define out(x, y) cout << ">> " << (x) << " " << (y) << endl

#ifdef LOCAL
#define DEBUG(...) __VA_ARGS__;
#else
#define DEBUG(...)
#endif

namespace FFT {

#define I int
#define LL long long

const int LN = 23;
const int N = 1 << LN;
const int MOD = 998244353;
const int PRIMITIVE_ROOT = 3;

I root[N];

inline I power(I x, I y) {
    I ret = 1;
    for (; y; y >>= 1, x = (LL)x * x % MOD)
        if (y & 1) ret = (LL)ret * x % MOD;
    return ret;
}

inline void init_fft() {
    const I UNITY = power(PRIMITIVE_ROOT, (MOD-1) >> LN);
    root[0] = 1;
    for (int i = 1; i < N; i++)
        root[i] = (LL)UNITY * root[i-1] % MOD;
    return;
}

inline void fft(I n, vector<I> &a, bool invert) {
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        I wlen = (invert ? root[N - N/len] : root[N/len]);
        for (int i = 0; i < n; i += len) {
            I w = 1;
            for (int j = 0; j < (len >> 1); j++) {
                unsigned I u = a[i+j];
                unsigned I v = (LL)a[i+j + len/2] * w % MOD;
                a[i+j] = (u + v) % MOD;
                a[i+j + len/2] = (u - v + MOD) % MOD;
                w = (LL) w * wlen % MOD;
            }
        }
    }
    if (invert) {
        I inv = power(n, MOD-2);
        for (int i = 0; i < n; i++) a[i] = (LL)a[i] * inv % MOD;
    }
    return;
}

inline vector<I> multiply(vector<I> a, vector<I> b) {
    int n = 1, as = a.size(), bs = b.size();
    while (n < as + bs) n <<= 1;

    vector<I> c;
    a.resize(n, 0); b.resize(n, 0); c.resize(n);

    fft(n, a, false); fft(n, b, false);
    for (int i = 0; i < n; i++)
        c[i] = (LL)a[i] * b[i] % MOD;
    fft(n, c, true);
    return c;
}

#undef I
#undef LL

}

const int maxM  = 105;
const int maxR  = 1e5 + 5;
const int maxRr = 1e5;
const int MOD   = 998244353;

int N, M, X[maxM], W[maxM], fact[maxR], invfact[maxR];
vector<int> P[maxM], adj[maxM];

ll madd(ll x, ll y) {return (x + y) % MOD;}
ll msub(ll x, ll y) {return (x - y + MOD) % MOD;}
ll mmul(ll x, ll y) {return (x * y) % MOD;}
ll modexp(ll x, ll y) {
    ll ret = 1;
    for (; y; y /= 2, x = mmul(x, x)) if (y % 2) ret = mmul(ret, x);
    return ret;
}
ll inv(ll x) {return modexp(x, MOD-2);}

vector<int> combine(vector<int> x, vector<int> y) {
    vector<int> u = x, v = y;
    for (int i = 0; i < (int)x.size(); i++) u[i] = mmul(u[i], invfact[i]);
    for (int i = 0; i < (int)y.size(); i++) v[i] = mmul(v[i], invfact[i]);
    u = FFT::multiply(u, v);
    for (int i = 0; i < (int)u.size(); i++) u[i] = mmul(u[i], fact[i]);
    return u;
}

void calc(int cur, int par) {
    for (auto &nxt : adj[cur]) {
        if (nxt == par) continue;
        calc(nxt, cur);
        P[cur] = combine(P[cur], P[nxt]);
        while ((int)P[cur].size() > X[cur]+1) P[cur].pop_back();
    }

    // debug(cur);
    // for (auto &i : P[cur]) cout << i << ' ';
    // cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    FFT::init_fft();
    fact[0] = 1;
    rep(i, 1, maxRr) fact[i] = mmul(fact[i-1], i);
    invfact[maxRr] = modexp(fact[maxRr], MOD-2);
    for (int i = maxRr-1; i >= 0; i--) invfact[i] = mmul(invfact[i+1], i+1);

    cin >> N >> M;
    rep(i, 1, M) cin >> X[i];
    rep(i, 1, M) cin >> W[i];
    for (int u, v, i = 1; i < M; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    rep(i, 1, M) {
        int runW = 1;
        for (int j = 0; j <= X[i]; j++) {
            P[i].push_back(runW);
            runW = mmul(runW, W[i]);
        }
    }
    calc(1, -1);

    if ((int)P[1].size() < N+1) {
        cout << "0\n";
    } else {
        cout << P[1][N] << '\n';
    }


    return 0;
}