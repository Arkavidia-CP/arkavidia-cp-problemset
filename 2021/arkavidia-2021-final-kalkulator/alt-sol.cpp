/**
* Author    : Farras Faddila (donbasta)
* Problem   : Kalkulator Wibi
**/

#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using Polynom = vector<int>;

int fpow (int a, int b, int mod) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1LL * ret * a % mod;
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return ret;
}

int inverse (int a, int mod) {
    // mod must be a prime number
    return fpow (a, mod - 2, mod);
}

const int mod = 998244353;
const int root = 15311432;
const int root_1 = inverse (root, mod);
const int root_pw = 1 << 23;

void fft(Polynom & a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i+j], v = (int)(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }
    if (invert) {
        int n_1 = inverse(n, mod);
        for (int & x : a)
            x = (int)(1LL * x * n_1 % mod);
    }
}

Polynom mul(Polynom a, Polynom b, int deg) {
  //TODO: multiplication with NTT, degree modulo deg
    Polynom fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while(n < (int)a.size() + b.size()) {
        n <<= 1;
    }
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for(int i = 0; i < n; i++) {
        fa[i] = 1LL * fa[i] * fb[i] % mod;
    }
    fft(fa, true);
    if ((int)fa.size() > deg) {
        for (int i = deg; i < (int)fa.size(); i++) {
            fa[i - deg] = (1LL * fa[i - deg] + fa[i]) % mod;
        }
        fa.resize(deg);
    }
    return fa;
}

Polynom fpow(Polynom P, ll exp, int deg) {
    //TODO: fast exponentiation P to the power of exp
    Polynom ret = {1};
    while (exp) {
        if (exp & 1) 
            ret = mul (ret, P, deg);
        P = mul (P, P, deg);
        exp >>= 1;
    }
    return ret;
}

int n, m;
ll r;
Polynom koef;

void solve() {
  cin >> n >> m >> r;

  koef.resize(n);
  for (int i = 0; i < m; i++) {
      int x;
      cin >> x;
      x %= n;
      koef[x]++;
  }

  koef = fpow(koef, r, n);
  koef.resize(n);

  for (int i = 0; i < n; i++) {
    cout << koef[i] << (i < n - 1 ? ' ' : '\n');
  }
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